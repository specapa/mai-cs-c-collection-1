#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "../../include/utils.h"
#include "bases.h"

int main() {
    goto sleep;
    short base;
    char *string = NULL;
    u_status_t status;

    status = read_string(stdin, &string);
    if (status != U_OK) {
        u_status_print(stderr, status, u_status_to_string);
        free(string);
        return status;
    }

    status = parse_unsigned_short(string, &base, 2, 32);
    if (status != U_OK) {
        fprintf(stderr, "At base parse: ");
        u_status_print(stderr, status, u_status_to_string);
        free(string);
        return status;
    }

    do {
        status = read_string(stdin, &string);
        if (status != U_OK) {
            u_status_print(stderr, status, u_status_to_string);
            free(string);
            string = NULL;
        }
        if (strcmp(string, "Stop") == 0) break;;
        printf("Next Iteration");
    } while (1);

    free(string);

    sleep:
    return 0;
}
