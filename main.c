#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "error_handling.h"
#include "file_utils.h"

// TODO: Add getting a random quote, add gettting specific quotes

int delete_quote(char* label) {
	char *home_env = getenv("HOME");
	char f_path[1024];
	sprintf(f_path, "%s%s", home_env, "/.config/ques.txt");
	result_lines_t res_read_lines = read_lines(f_path);
	if (res_read_lines.is_err == true) {
		exit_from_err(res_read_lines.data.error);
	}
	printf("%s\n", "Hielo");
	for (int i = 0; i < res_read_lines.data.value.count; i++) {
		printf("%s\n", res_read_lines.data.value.lines[i]);
	}
	free(res_read_lines.data.value.lines);
	free(res_read_lines.data.value.buffer);

	return 0;
}

int add_quote(const char *quote, char* label) {
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
	fprintf(f, "%i; %s; %s\n", count_lines_res.data.value++, label, quote);
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
		if (strncmp(argv[1], "rm-q", 4) == 0) {
			delete_quote("ass");
			exit(EXIT_SUCCESS);
		}
		break;
	case 4:
		if (strncmp(argv[1], "add-q", 5) == 0) {
			add_quote(argv[3], argv[2]);
			exit(EXIT_SUCCESS);
		}

		break;
	}

}
