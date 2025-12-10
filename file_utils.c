#include "file_utils.h"
#include "error_handling.h"

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



result_lines_t read_lines(const char *filename) {
    lines_t result = {0, NULL};
    FILE *fp = fopen(filename, "rb");
    if (!fp) return err_lines("Error opening the quote file", 2);

    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size + 1);
    result_char_p_t res_read_file = read_file(fp);
    if (res_read_file.is_err == true) {
	return err_lines(res_read_file.data.error.err_message, res_read_file.data.error.code);
    }
    memcpy(buffer, res_read_file.data.value, size + 1);
    fclose(fp);

    buffer[size] = '\0';

    size_t count = 0;
    for (long i = 0; i < size; i++)
        if (buffer[i] == '\n') count++;

    result.lines = malloc((count + 1) * sizeof(char*));

    size_t idx = 0;
    char *line = buffer;

    for (long i = 0; i < size; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            result.lines[idx++] = line;
            line = &buffer[i + 1];
        }
    }

    if (*line) {
        result.lines[idx++] = line;
    }

    result.count = idx;
    result.buffer = buffer;
    result_lines_t final_ret_res = {
		.is_err = false,
		.data.value = result,
    };

    return final_ret_res;
}

