#include "error_handling.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define CL_BUF_SIZE 65536

result_int_t count_lines(FILE* file);

result_char_p_t read_file(FILE* f);

result_lines_t read_lines(const char *filename);
