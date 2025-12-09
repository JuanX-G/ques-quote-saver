#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error_handling.h"

// TODO: Add getting a random quote, add gettting specific quotes

#define CL_BUF_SIZE 65536
result_int_t count_lines(FILE* file) {
    char buf[CL_BUF_SIZE];
    int counter = 0;
    result_int_t ret_res; 
    for(;;) {
        size_t res = fread(buf, 1, CL_BUF_SIZE, file);
        if (ferror(file)) {
		ret_res.is_err = true;
		error_t err = {.err_message = "error reading from quote file", .code = 1};
		ret_res.data.error = err;
		return ret_res;
	}
        int i;
        for(i = 0; i < res; i++) {
            if (buf[i] == '\n') {
                counter++;
	    }
	}
        if (feof(file)) {
            break;
	}
    }
    ret_res.is_err = false;
    ret_res.data.value = counter;

    return ret_res;
}

result_char_p_t read_file(FILE* f) {
	result_char_p_t ret_res;
	fseek(f, 0L, SEEK_END);
	long f_size = ftell(f);
	fseek(f, 0, SEEK_SET);
	char* file_content_buf = malloc(f_size);
	if (file_content_buf == NULL) {
			ret_res.is_err = true;
			error_t err = {.err_message = "error obtaining memory for the file contents", .code = 1};
			ret_res.data.error = err;
			return ret_res;
	}
	for (;;) {
		fread(file_content_buf, 1, f_size, f);
		if (ferror(f)) {
			ret_res.is_err = true;
			error_t err = {.err_message = "error reading from quote file", .code = 1};
			ret_res.data.error = err;
			return ret_res;
		}
		if (feof(f)) {
			break;
		}
	}
	ret_res.is_err = false;
	ret_res.data.value = file_content_buf;
	return ret_res;
}

int add_quote(const char *quote) {
	FILE* f;
	char *home_env = getenv("HOME");
	char f_path[1024];
	sprintf(f_path, "%s%s", home_env, "/.config/ques.txt");
	f = fopen(f_path, "r+");
	if (f == NULL) {
		exit_fail("Could not open quote file");
	}
	result_int_t count_lines_res = count_lines(f);
	if (count_lines_res.is_err == true) {
		exit_from_err(count_lines_res.data.error);
	}
	
	fseek(f, 0, SEEK_END);
	fprintf(f, "%i, %s\n", count_lines_res.data.value++, quote);
	fclose(f);
	return 0;
}

int list_all_quotes() {
	FILE* f;
	char *home_env = getenv("HOME");
	char f_path[1024];
	sprintf(f_path, "%s%s", home_env, "/.config/ques.txt");
	f = fopen(f_path, "r");
	if (f == NULL) {
		exit_fail("Could not open quote file");
	}
	result_int_t count_lines_res = count_lines(f);
	if (count_lines_res.is_err == true) {
		exit_from_err(count_lines_res.data.error);
	}
	result_char_p_t f_read_res = read_file(f);
	if (f_read_res.is_err == true) {
		exit_from_err(f_read_res.data.error);
	}
	printf("%s\n", f_read_res.data.value);
	printf("quotes printed: %d\n", count_lines_res.data.value);
	
	free(f_read_res.data.value);
	fclose(f);
	return 0;
}

int main(int argc, char *argv[]) {
	switch (argc) {
	case 1:
		exit_fail("not enough arguments");
		break;
	case 2:
		if (strncmp(argv[1], "list", 5) == 0) {
			list_all_quotes();
		}
		break;
	case 3:
		if (strncmp(argv[1], "add-q", 5) == 0) {
			add_quote(argv[2]);
			exit(EXIT_SUCCESS);
		}
		break;
	}

}
