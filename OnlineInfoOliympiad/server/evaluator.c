#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
#include <sys/stat.h> 
#include "evaluator.h" 
#include "protocol.h" 
#include <sys/time.h> 

int compile_solution (const char *source_file, const char *output_file)
{ 
    if (access ("scripts/compile_solution.sh", X_OK) != 0)
    {
        perror ("[ERROR] Scriptul compile_solution.sh nu exista sau nu e executabil");
        return -1;
    }

    char cmd[1024];
    snprintf (
        cmd, 
        sizeof(cmd), 
        "bash scripts/compile_solution.sh \"%s\" \"%s\"", 
        source_file, 
        output_file
    );

    printf ("[DEBUG] Comanda compilare: %s\n", cmd);

    int status = system(cmd); 

    if (status == -1)
    {
        perror ("[ERROR] System() a esuat");
        return -1;
    }

    if (status == 0)
    {
        printf ("[DEBUG] Compilare reusita pentru %s\n", source_file);
        return 0;
    }
    else
    {
        printf (
            "[DEBUG] Compilare esuata pentru %s (cod iesire: %d)\n", 
            source_file, 
            status
        );
        return -1;
    }
}

int run_tests (
    const char *exec_file, 
    int problem_id, 
    const char *solution_dir, 
    double *out_avg_time
)
{
    int passed = 0; 
    double total_time = 0.0; 

    char temp_out[512], cmd[2048];

    snprintf (
        temp_out, 
        sizeof(temp_out), 
        "%s/temp_output.txt", 
        solution_dir
    );

    for (int i = 1; i <= MAX_TESTS; i ++)
    {
        char in[512], ref[512];

        snprintf (
            in, 
            sizeof(in), 
            "problems/problem%d/tests/test%d.in", 
            problem_id + 1, 
            i
        );
        snprintf (
            ref, 
            sizeof(ref), 
            "problems/problem%d/tests/test%d.out", 
            problem_id + 1, 
            i
        );

        if (access (in, F_OK) != 0)
            continue;

        struct timeval start, end;

        gettimeofday (&start, NULL);

        snprintf (
            cmd, 
            sizeof(cmd), 
            "bash scripts/run_tests.sh \"%s\" \"%s\" \"%s\"", 
            exec_file, 
            in, 
            temp_out
        );
        int res = system(cmd);

        gettimeofday (&end, NULL);

        if (res == 0) 
        {
            total_time = 
                total_time + 
                (end.tv_sec - start.tv_sec) + 
                (end.tv_usec - start.tv_usec) / 1000000.0;

            char diff_cmd[2048];

            snprintf (
                diff_cmd, 
                sizeof(diff_cmd), 
                "diff -q -w \"%s\" \"%s\" >/dev/null", 
                temp_out, 
                ref
            );

            if (system(diff_cmd) == 0)
                passed ++;
        }
    }

    if (passed > 0)
        *out_avg_time = total_time / passed;
    else        
        *out_avg_time = 0.0;

    unlink(temp_out);

    return passed; 
}