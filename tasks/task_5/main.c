#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include "args.h"
#include "string_concatenate.h"
#include "file_process.h"

void fprint_usage(FILE * f, char * run_file_name) {
    fprintf(f, "Usage: %s <-nd>|</nd>|<-ni>|</ni>|<-ns>|</ns>|<-na>|</na> <filepath> <with -n : file out pathname>\n", run_file_name);
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        fprint_usage(stderr, argv[0]);
        return 1;
    }
    flag_t flag;
    u_status_t stat;
    stat = parse_flag(argv[1], &flag);
    if (stat != U_OK) {
        fprintf(stderr, "At parse flag: ");
        u_status_print(stderr, stat, u_status_to_string);
        fprint_usage(stderr, argv[0]);
        return stat;
    }

    char *input_file_name = argv[2];
    char *output_file_name = NULL;

    if (!is_n_flag(flag)) {
        if (argc != 4) {
            fprintf(stderr, "Wrong format for n-started flag: ");
            fprint_usage(stderr, argv[0]);
            return U_INVALID_FORMAT;
        }
        output_file_name = argv[3];
    } else {
        if (argc != 3) {
            fprintf(stderr, "Wrong format for non n-started flag: ");
            fprint_usage(stderr, argv[0]);
            return U_INVALID_FORMAT;
        }
        stat = add_out_prefix("out_", input_file_name, &output_file_name);
        if (stat != U_OK) {
            fprintf(stderr, "At generate output filename: ");
            u_status_print(stderr, stat, u_status_to_string);
            fprint_usage(stderr, argv[0]);
            return stat;
        }
    }
    stat = process_file(input_file_name, output_file_name, flag);
    if (stat != U_OK) {
        fprintf(stderr, "At file processing: ");
        u_status_print(stderr, stat, u_status_to_string);
        return stat;
    }   
    if (argc == 3) free(output_file_name);
    return U_OK;
}
