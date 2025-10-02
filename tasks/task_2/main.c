#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../../include/utils.h"
#include "prime_at_n.h"

int main() {
    uint64_t T;
    uint64_t n;
    uint64_t result;
    status_t status;
    u_status_t u_status;
    char *string = NULL;

    u_status = read_string(stdin, &string);
    if (u_status != U_OK) {
        u_status_print(stderr, u_status, u_status_to_string);
        free(string);
        return 1;
    }
    u_status = parse_unsigned_ll(string, (long long unsigned int*) &T, 0, ULLONG_MAX);
    if (u_status != U_OK) {
        u_status_print(stderr, u_status, u_status_to_string);
        free(string);
        return 1;
    }
    free(string);
    string = NULL;
    
    for (uint64_t i = 0; i < T; ++i) {
        u_status = read_string(stdin, &string);
        if (u_status != U_OK) {
            u_status_print(stderr, u_status, u_status_to_string);
            free(string);
            string = NULL;
            continue;
        }
        u_status = parse_unsigned_ll(string, (long long unsigned int*) &n, 0, ULLONG_MAX);
        if (u_status != U_OK) {
            u_status_print(stderr, u_status, u_status_to_string);
            free(string);
            string = NULL;
            continue;
        }
        
        status = find_prime_number_by_number(n, &result);
        if (status == STATUS_OK) {
            printf("Success: %" PRIu64 "\n", result);
        } else {
            printf("Failed to find prime #%" PRIu64 "\n", n);
            u_status_print(stderr, status, status_to_string);
        }

        free(string);
        string = NULL;
    }
    return 0;
}