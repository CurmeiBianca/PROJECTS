#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "problem_manager.h"

typedef struct
{
    char client_name[50]; 
    int tests_passed; 
    double execution_time; 
    double upload_speed; 
    int total_score; 
} ClientScore;

int compile_solution (const char *source_file, const char *output_file);

int run_tests (const char* exec_file, int problem_id, const char *solution_dir, double *out_avg_execution_time);

#endif
