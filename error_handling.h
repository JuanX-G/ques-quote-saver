#pragma once 
#define SIZE_OF_ERR_MSG 128
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef struct {
	const char* err_message;
	int code;
} error_t;

typedef struct {
	bool is_err;
	union {
		int value;
		error_t error;
	} data;
} result_int_t;

typedef struct {
	bool is_err;
	union {
		char* value;
		error_t error;
	} data;
} result_char_p_t;

typedef struct {
	size_t count;
	char **lines;
	char *buffer;

} lines_t;

typedef struct {
	bool is_err;
	union {
		lines_t value;
		error_t error;
	} data;
} result_lines_t;

void exit_fail(char* msg);
void exit_from_err(error_t);

result_int_t err_int(const char* msg, int code);
result_int_t ok_int(int i);

result_char_p_t err_char_p(const char* msg, int code);
result_char_p_t ok_char_p(char* value);

result_lines_t err_lines(const char* msg, int code);
result_lines_t ok_lines(lines_t value);
