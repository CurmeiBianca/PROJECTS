#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <time.h> 
#include "problem_manager.h"

#define PROBLEMS_DIR "problems/" 

void read_file (const char *filepath, char *buffer, size_t max_size)
{
    FILE *f = fopen (filepath, "r");
    if (!f)
    {
        buffer[0] = '\0';
        return;
    }
    size_t len = fread(buffer, 1, max_size - 1, f);

    buffer[len] = '\0';

    fclose(f);
}

void load_problems (Problem problems[], int *num_problems) 
{
    *num_problems = MAX_PROBLEMS;

    for (int i = 0; i < MAX_PROBLEMS; i ++)
    {
        snprintf (
            problems[i].name, 
            sizeof(problems[i].name), 
            "problem%d", 
            i + 1
        );

        problems[i].num_tests = MAX_TESTS;

        char statement_path[512];
        snprintf (
            statement_path, 
            sizeof(statement_path), 
            "%s%s/statement.txt", 
            PROBLEMS_DIR, 
            problems[i].name
        );

        read_file (
            statement_path, 
            problems[i].statement, 
            MAX_STATEMENT
        );

        for (int j = 0; j < MAX_TESTS; j ++)
        {
            snprintf (
                problems[i].test_in[j], 
                512, 
                "%s%s/tests/test%d.in", 
                PROBLEMS_DIR, 
                problems[i].name, 
                j + 1
            );
            snprintf (
                problems[i].test_out[j], 
                512, 
                "%s%s/tests/test%d.out", 
                PROBLEMS_DIR, 
                problems[i].name, 
                j + 1
            );
        }
    }
}

int choose_random_problem (int num_problems)
{
    if (num_problems <= 0)
        return -1;

    return rand() % num_problems;
}