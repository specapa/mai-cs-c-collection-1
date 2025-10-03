#include "file_process.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

u_status_t process_flag_d(FILE *in, FILE *out) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (!isdigit((unsigned char)c)) {
            fputc(c, out);
        }
    }
    return U_OK;
}

char *read_line(FILE *in) {
    size_t size = 128;
    size_t len = 0;
    char *buf = malloc(size);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(in)) != EOF) {
        if (len + 1 >= size) {
            size *= 2;
            char *tmp = realloc(buf, size);
            if (!tmp) { free(buf); return NULL; }
            buf = tmp;
        }
        buf[len++] = (char)c;
        if (c == '\n') break;
    }

    if (len == 0 && c == EOF) {
        free(buf);
        return NULL;
    }

    buf[len] = '\0';
    return buf;
}

u_status_t process_flag_i(FILE *in, FILE *out) {
    char *line;
    while ((line = read_line(in)) != NULL) {
        int count = 0;
        for (char *p = line; *p; p++) {
            if (isalpha((unsigned char)*p)) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
        free(line);
    }
    return U_OK;
}

u_status_t process_flag_s(FILE *in, FILE *out) {
    char *line;
    while ((line = read_line(in)) != NULL) {
        int count = 0;
        for (char *p = line; *p; p++) {
            if (!isalpha((unsigned char)*p) &&
                !isdigit((unsigned char)*p) &&
                !isspace((unsigned char)*p)) {
                count++;
            }
        }
        fprintf(out, "%d\n", count);
        free(line);
    }
    return U_OK;
}

u_status_t process_flag_a(FILE *in, FILE *out) {
    int c;
    while ((c = fgetc(in)) != EOF) {
        if (isdigit((unsigned char)c)) {
            fputc(c, out);
        } else {
            fprintf(out, "%02X", (unsigned char)c);
        }
    }
    return U_OK;
}

u_status_t process_file(const char *input_file, const char *output_file, flag_t flag) {
    FILE *in = fopen(input_file, "r");
    if (!in) {
        fprintf(stderr, "At input file %s opening: ", input_file);
        return U_INVALID_FORMAT;
    }

    FILE *out = fopen(output_file, "w");
    if (!out) {
        fprintf(stderr, "At output file %s opening: ", output_file);
        fclose(in);
        return U_INVALID_FORMAT;
    }

    int res = 0;
    switch (flag) {
        case FLAG_D: case FLAG_ND: res = process_flag_d(in, out); break;
        case FLAG_I: case FLAG_NI: res = process_flag_i(in, out); break;
        case FLAG_S: case FLAG_NS: res = process_flag_s(in, out); break;
        case FLAG_A: case FLAG_NA: res = process_flag_a(in, out); break;
        default:
            break;
    }

    fclose(in);
    fclose(out);
    return res;
}
