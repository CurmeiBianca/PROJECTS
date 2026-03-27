#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <time.h> 
#include <sys/time.h> 
#include <sys/stat.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <signal.h> 
#include <fcntl.h> 

#include "problem_manager.h" 
#include "evaluator.h" 
#include "utils.h" 
#include "protocol.h" 

#define SCORES_FILE "results/scores.txt" 
#define PATH_BUF 2048 

void handle_client (int client_sock)
{
    char buffer[BUFFER_SIZE], client_name[64];

    int problem_id = -1, is_sending = 0;

    double exec_time = 0.0, writing_time = 0.0, compilation_time = 0.0, final_score = 0.0;

    time_t start_problem_clock = 0;

    FILE *sol_f = NULL;

    snprintf (client_name, sizeof(client_name), "stud_%d", getpid());
    send_message (client_sock, "Bine ati venit la OnlineInfoOlympiad 2026!"); // mesaj de bun venit

    while (1)
    {
        memset (buffer, 0, BUFFER_SIZE);

        if (recv_message (client_sock, buffer) <= 0)
            break;

        char raw_line[BUFFER_SIZE]; 
        strcpy (raw_line, buffer);

        trim_whitespace (buffer);

        if (is_sending)
        {
            if (difftime (time(NULL), start_problem_clock) > PROBLEM_TIME_LIMIT)
            {
                is_sending = 0;
                if (sol_f)
                {
                    fclose(sol_f);
                    sol_f = NULL;
                }

                send_message (client_sock, 
                        "[EROARE] Timupl de scriere a solutiei a expirat!");
                continue;
            }

            if (strcmp (buffer, END_SOLUTION) == 0)
            {
                is_sending = 0;

                writing_time = difftime (time(NULL), start_problem_clock);

                if (sol_f)
                {
                    fflush(sol_f);
                    fsync(fileno(sol_f));
                    fclose(sol_f);
                    sol_f = NULL;
                }

                char dir[PATH_BUF], src[PATH_BUF], exe[PATH_BUF];
                int n;

                n = snprintf (dir, sizeof(dir), "submissions/%s", client_name);
                if (n >= sizeof(dir))
                    dir[sizeof(dir) - 1] = 0;

                n = snprintf (src, sizeof(src), "%s/solution.c", dir);
                if (n >= sizeof(src))
                    src[sizeof(src) - 1] = 0;

                n = snprintf (exe, sizeof(exe), "%s/solution.out", dir);
                if (n >= sizeof(exe))
                    exe[sizeof(exe) - 1] = 0;

                struct timeval c_start, c_end;
                gettimeofday (&c_start, NULL);
                int comp_status = compile_solution (src, exe);
                gettimeofday (&c_end, NULL);

                compilation_time = 
                    (double)(c_end.tv_sec - c_start.tv_sec) + 
                    (double)(c_end.tv_usec - c_start.tv_usec) / 1000000.0;

                if (comp_status == 0)
                {
                    int tests_passed = run_tests (exe, problem_id, dir, &exec_time);

                    if (tests_passed > 0)
                    {
                        double p_base = 
                            ((double)tests_passed / MAX_TESTS) * WEIGHT_TESTS;

                        double p_writing = 
                            WEIGHT_WRITTING * (1.0 - (writing_time / PROBLEM_TIME_LIMIT));
                        if (p_writing < 0)
                            p_writing = 0;

                        double p_exec;
                        if (exec_time < 1.0)
                            p_exec = WEIGHT_EXEC * (1.0 - exec_time);
                        else 
                            p_exec = 0;

                        final_score = p_base + p_writing + p_exec;
                    }
                    else
                        final_score = 0;

                    char res[BUFFER_SIZE + 256];
                    snprintf (res, sizeof(res), 
                        "[SERVER] Scor Final: %.2f/100 (Teste %d/%d, Scriere: %.1fs, Exec: %.3f)", 
                        final_score, tests_passed, MAX_TESTS, 
                        writing_time, exec_time);
                    send_message (client_sock, res);
                }
                else 
                {
                    send_message (client_sock, 
                        "[SERVER] Eroare la compilare! Verifica sintaxa.");
                    final_score = 0;
                    exec_time = 0;
                }

                FILE *f_r = fopen (SCORES_FILE, "a");
                if (f_r)
                {
                    fprintf (f_r,
                        "Nume: %s | Scor: %.2f | Scriere: %.2f | Compilare: %.3f | Exec: %.3f | Status: %s\n",
                        client_name, final_score, writing_time,
                        compilation_time, exec_time,
                        (comp_status == 0 ? "OK" : "ERR_COMP"));
                    fclose(f_r);
                }
                continue;
            }

            if (sol_f)
                fprintf (sol_f, "%s\n", raw_line);

            continue;
        }

        if (strcmp (buffer, "GET PROBLEM") == 0)
        {
            problem_id = choose_random_problem(MAX_PROBLEMS);
            start_problem_clock = time(NULL);

            char path[PATH_BUF], line[BUFFER_SIZE];
            int n = snprintf (path, sizeof(path),
                "problems/problem%d/statement.txt", problem_id + 1);
            if (n >= sizeof(path))
                path[sizeof(path) - 1] = 0;

            FILE *f = fopen(path, "r");
            if (f)
            {
                while (fgets (line, sizeof(line), f))
                {
                    line[strcspn(line, "\r\n")] = 0;
                    send_message (client_sock, line);
                }
                fclose(f);
            }

            char info[218];
            snprintf (info, sizeof(info),
                        "[INFO] Timp limita: %d secunde.", PROBLEM_TIME_LIMIT);
            send_message (client_sock, info);
            send_message (client_sock, END_PROBLEM);
        }
        else if (strcmp (buffer, "SEND SOLUTION") == 0)
        {
            if (problem_id == -1)
            {
                send_message (client_sock, 
                    "[EROARE] Trebuie sa ceri enuntul problemei intai!");
                continue;
            }

            if (difftime (time(NULL), start_problem_clock) > PROBLEM_TIME_LIMIT)
            {
                send_message (client_sock, 
                    "[EROARE] Timpul de scriere a expirat!");
                continue;
            }

            char dir[PATH_BUF], path_file[PATH_BUF];
            int n = snprintf (dir, sizeof(dir), "submissions/%s", client_name);
            if (n >= sizeof(dir))
                dir[sizeof(dir) - 1] = 0;
            mkdir ("submissions", 0755);
            mkdir (dir, 0755);

            n = snprintf (path_file, sizeof(path_file), "%s/solution.c", dir);
            if (n >= sizeof(path_file))
                path_file[sizeof(path_file) - 1] = 0;
            sol_f = fopen(path_file, "w");
            is_sending = 1;

            send_message (client_sock, "[SERVER] Trimite codul...");
        }
        else if (strcmp (buffer, "GET RESULTS") == 0)
        {
            char res[BUFFER_SIZE + 256];
            snprintf (res, sizeof(res),
                "[REZULTAT] %s -> Scor: %.2f/100", client_name, final_score);
            send_message (client_sock, res);
        }
        else if (strcmp (buffer, "GET RANKING") == 0)
        {
            FILE *f = fopen(SCORES_FILE, "r");
            if (f)
            {
                char l[BUFFER_SIZE];
                while (fgets (l, sizeof(l), f))
                {
                    l[strcspn(l, "\r\n")] = 0;
                    send_message (client_sock, l);
                }
                fclose(f);
            }
            send_message (client_sock, END_RANKING);
        }
        else if (strcmp (buffer, "QUIT") == 0)
            break;

        else 
        {
            char err_msg[BUFFER_SIZE];
            snprintf(err_msg, sizeof(err_msg), "[SERVER] Comanda necunoscuta: %s", buffer);
            send_message (client_sock, err_msg);
        }
    }

    close (client_sock);
}

int main ()
{
    srand (time(NULL));

    mkdir ("results", 0755);
    mkdir ("submissions", 0755);

    int s_sock = socket (AF_INET, SOCK_STREAM, 0);

    int opt = 1;
    setsockopt (s_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    struct sockaddr_in addr = 
    {
        .sin_family = AF_INET,
        .sin_port = htons(PORT),
        .sin_addr.s_addr = INADDR_ANY
    };

    if (bind (s_sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror ("Eroare  Bind");
        exit(1);
    }

    listen (s_sock, 10);
    printf ("[ONLINEINFOOLYMPIAD 2026] Server pornit pe portul 5151...\n");

    while (1)
    {
        int c_sock = accept(s_sock, NULL, NULL);
        if (c_sock < 0)
            continue;

        if (fork() == 0)
        {
            close (s_sock);
            handle_client (c_sock);
            exit (0);
        }

        close (c_sock);
    }

    return 0;
}