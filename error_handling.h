#pragma once 
#define SIZE_OF_ERR_MSG 128


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

void exit_fail(char* msg);
void exit_from_err(error_t);
