#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "file_process.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Use with one arg: {input file name} {output file name}\n");
        return 1;
    }

    u_status_t st;

    char *input_file_name = argv[1];
    char *output_file_name = argv[2];

    st = process_file(input_file_name, output_file_name);
    if (st != U_OK) {
        u_status_print(stderr, st, u_status_to_string);
    }

    return 0;
}
