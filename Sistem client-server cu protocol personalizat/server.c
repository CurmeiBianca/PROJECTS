#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <unistd.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>

#include <utmp.h>
#include <time.h> 

#define FIFO_IN "fifo_i"
#define FIFO_OUT "fifo_o"
#define LMAX_COM 256
#define LMAX_RASP 2048

int logged_in = 0;
char user_curent[64];

int validare_utilizator (const char* utilizator)
{
    FILE* fis = fopen ("fis_config", "r");
    if (!fis)
        return 0;

    char linie[64];
    while (fgets (linie, sizeof(linie), fis))
    {
        linie[strcspn(linie, "\n")] = 0;

        if (strcmp (linie, utilizator) == 0)
        {
            fclose (fis);
            return 1;
        }
    }

    fclose (fis); 
    return 0;
}

void trim_raspuns (int fd, const char* mesaj)
{
    int lung = strlen (mesaj);
    write (fd, &lung, sizeof (int));
    write (fd, mesaj, lung);
}

void procesare_login (const char* comanda, int fd_out)
{
    const char* utilizator = strchr (comanda, ':');
    if (!utilizator)
    {
        trim_raspuns (fd_out, "Format invalid pentru conectare\n");
        return;
    }

    utilizator = utilizator + 2;

    if (validare_utilizator (utilizator))
    {
        logged_in = 1;
        strcpy (user_curent, utilizator);
        trim_raspuns (fd_out, "Conectat cu succes\n");
    }
    else
    {
        trim_raspuns (fd_out, "Utilizator invalid\n");
    }
}

void procesare_get_logged_users (int fd_out)
{
    if (!logged_in)
    {
        trim_raspuns (fd_out, "Niciun utilizator conectat\n");
        return;
    }

    int sv[2];

    if (socketpair (AF_UNIX, SOCK_STREAM, 0, sv) == -1)
    {
        trim_raspuns (fd_out, "Eroare socketpair\n");
        return;
    }

    pid_t pid = fork();

    if (pid < 0)
    {
        close (sv[0]);

        close (sv[1]);
        trim_raspuns (fd_out, "Eroare fork\n");
        return;
    }
    if (pid == 0)
    {
        close (sv[0]);

        setutent();
        struct utmp *u;
     
        char rezultat[LMAX_RASP] = "";

        while ((u = getutent()) != NULL)
        {
            if (u->ut_type == USER_PROCESS)
            {
                const char* username = u->ut_user;
                const char* host = u->ut_host;
                time_t login_time = u->ut_tv.tv_sec;

                char* time_string = ctime (&login_time);

                if (time_string)
                    time_string[strcspn (time_string, "\n")] = 0;

                char linie[512];

                snprintf (linie, sizeof(linie),
                         "user: %s | host: %s | time: %s\n",
                         username[0] ? username : "necunoscut",
                         host[0] ? host : "local",
                         time_string ? time_string : "unknown");

                if (strlen(rezultat) + strlen(linie) < sizeof(rezultat))
                    strcat(rezultat, linie);
            }
        }

        endutent();

        if (strlen(rezultat) == 0)
            strcpy (rezultat, "Nu s-a gasit niciun utilizator conectat\n");

        write(sv[1], rezultat, strlen(rezultat));

        close(sv[1]);
        exit(0);
    }
    else
    {
        close (sv[1]);

        char buf[LMAX_RASP] = {0};
        int total_citiri = 0;
        int cit;

        while ((cit = read (sv[0], buf + total_citiri, sizeof (buf) - total_citiri)) > 0)
        {
            total_citiri = total_citiri + cit;
            if (total_citiri >= sizeof (buf) - 1)
                break;
        }

        buf[total_citiri] = '\0';

        trim_raspuns (fd_out, buf);

        close (sv[0]);
        wait (NULL);
    }
}

void procesare_get_proc_info (const char* comanda, int fd_out)
{
    if (!logged_in)
    {
        trim_raspuns (fd_out, "Niciun utilizator conectat\n");
        return;
    }

    const char* pid_str = strchr (comanda, ':');
    if (!pid_str)
    {
        trim_raspuns (fd_out, "Format invalid\n");
        return;
    }

    pid_str = pid_str + 2;
    int pid = atoi (pid_str);

    int pipefd[2];
    pipe (pipefd);

    pid_t copil = fork();
    if (copil == 0)
    {
        close (pipefd[0]);

        char path[64];
        snprintf(path, sizeof(path), "/proc/%d/status", pid);

        FILE* f = fopen(path, "r");
        if (!f)
        {
            write (pipefd[1], "Procesul nu a fost gasit\n", 26);
            exit (1);
        }

        char linie[256], rezultat[LMAX_RASP] = "";
        while (fgets(linie, sizeof (linie), f))
        {
            if (strncmp (linie, "Name:", 5) == 0 || 
            strncmp (linie, "State:", 6) == 0 || 
            strncmp (linie, "PPid:", 5) == 0 || 
            strncmp (linie, "Uid:", 4) == 0 || 
            strncmp (linie, "VmSize:", 7) == 0)
                strcat(rezultat, linie);
        }

        write (pipefd[1], rezultat, strlen (rezultat));
        fclose (f);
        close (pipefd[1]);
        exit (0);
    }
    else
    {
        close (pipefd[1]);
        char buf[LMAX_RASP] = {0};

        read (pipefd[0], buf, sizeof (buf));
        wait (NULL);
        trim_raspuns (fd_out, buf);
        close (pipefd[0]);
    }
}

int main ()
{
    mkfifo (FIFO_IN, 0666);
    mkfifo (FIFO_OUT, 0666);

    int fd_in = open (FIFO_IN, O_RDONLY);
    int fd_out = open (FIFO_OUT, O_WRONLY);

    char comanda[LMAX_COM];

    while (1)
    {
        int lungime = 0;
        int bytes_read = read (fd_in, &lungime, sizeof (int));
        if (bytes_read <= 0)
            break;

        if (lungime > LMAX_COM - 1)
            lungime = LMAX_COM - 1;

        memset (comanda, 0, sizeof (comanda));
        bytes_read = read (fd_in, comanda, lungime);
        if (bytes_read <= 0)
            break;

        comanda[lungime] = '\0';

        if (strncmp (comanda, "login", 5) == 0)
        {
            procesare_login (comanda, fd_out);
        }
        else if (strncmp (comanda, "get-logged-users", 16) == 0)
        {
            procesare_get_logged_users (fd_out);
        }
        else if (strncmp (comanda, "get-proc-info", 13) == 0)
        {
            procesare_get_proc_info (comanda, fd_out);
        }
        else if (strncmp (comanda, "logout", 6) == 0)
        {
            logged_in = 0;
            trim_raspuns (fd_out, "Deconectat\n");
        }
        else if (strncmp (comanda, "quit", 4) == 0)
        {
            trim_raspuns (fd_out, "Serverul se inchide...\n");
            break;
        }
        else
        {
            trim_raspuns (fd_out, "Comanda necunoscuta\n");
        }
    }

    close (fd_in);
    close (fd_out);

    unlink (FIFO_IN);
    unlink (FIFO_OUT);

    return 0;
}
