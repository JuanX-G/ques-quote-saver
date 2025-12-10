#include "error_handling.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


void exit_fail(char *msg) {
	// TODO: null check here!!
	printf("Error: %s occured, exiting...\n", msg);
	exit(EXIT_FAILURE);
}

void exit_from_err(error_t error) {
	if (error.err_message == NULL) {
		printf("Error: (ne message) occured, exiting...\n");
		exit(error.code);
	}
	printf("Error: %s occured, exiting...\n", error.err_message);
	exit(error.code);
}

result_int_t err_int(const char* msg, int code) {
	result_int_t ret_res;
	ret_res.is_err = true;
	ret_res.data.error.err_message = msg;
	ret_res.data.error.code = code;
	return ret_res;
}

result_int_t ok_int(int i) {
	result_int_t ret_res;
	ret_res.is_err = false;
	ret_res.data.value = i;
	return ret_res;
}

result_char_p_t err_char_p(const char* msg, int code) {
	result_char_p_t ret_res = {
		.is_err = true,
		.data.error.err_message = msg,
		.data.error.code = code,
	};
	return ret_res;
}

result_char_p_t ok_char_p(char* value) {
	result_char_p_t ret_res = {
		.is_err = false,
		.data.value = value,
	};
	return ret_res;
}

result_lines_t err_lines(const char* msg, int code) {
	result_lines_t ret_res = {
		.is_err = true,
		.data.error.err_message = msg,
		.data.error.code = code,
	};
	return ret_res;
}

result_lines_t ok_lines(lines_t value) {
	result_lines_t ret_res = {
		.is_err = false,
		.data.value = value,
	};
	return ret_res;
}
