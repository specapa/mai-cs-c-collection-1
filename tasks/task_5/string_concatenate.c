#include "string_concatenate.h"
#include <stdlib.h>
#include <string.h>

u_status_t concatenate(const char *str1, const char *str2, char **result) {
    *result = malloc(strlen(str1) + strlen(str2) + 1);
    if (result == NULL) {
        return U_MEMORY_ALLOCATE_ERROR;
    }
    strcpy(*result, str1);
    strcat(*result, str2);
    return U_OK;
}

u_status_t add_out_prefix(const char *file_prefix, const char *path, char **result) {
    if (!path || !result) {
        return U_INVALID_FORMAT;
    }

    const char *filename = strrchr(path, '/');
#ifdef _WIN32
    const char *filename_backslash = strrchr(path, '\\');
    if (!filename || (filename_backslash && filename_backslash > filename)) {
        filename = filename_backslash;
    }
#endif

    if (filename) {
        filename++;
    } else {
        filename = path;
    }

    size_t path_len = filename - path;
    size_t prefix_len = strlen(file_prefix);
    size_t file_len = strlen(filename);

    *result = malloc(path_len + prefix_len + file_len + 1);
    if (!*result) {
        return U_MEMORY_ALLOCATE_ERROR;
    }

    memcpy(*result, path, path_len);
    memcpy(*result + path_len, file_prefix, prefix_len);
    strcpy(*result + path_len + prefix_len, filename);

    return U_OK;
}
