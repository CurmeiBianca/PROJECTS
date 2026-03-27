#ifndef PROBLEM_MANAGER_H 
#define PROBLEM_MANAGER_H

#define MAX_PROBLEMS 5 
#define MAX_TESTS 3 
#define MAX_PATH 1024 
#define MAX_NAME 256 
#define MAX_STATEMENT 2048

typedef struct
{
    char name[MAX_NAME]; 
    char statement[MAX_STATEMENT]; 
    char test_in[MAX_TESTS][MAX_PATH]; 
    char test_out[MAX_TESTS][MAX_PATH]; 
    int num_tests; 
} Problem;

void load_problems (Problem problems[], int *num_problems);

int choose_random_problem (int num_problems);

#endif
