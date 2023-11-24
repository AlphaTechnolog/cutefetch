#pragma once

#define FUN_CHECK(fn) \
    inline void fn##_check(void *res) { \
        if (!res) { \
            perror(#fn); \
            exit(EXIT_FAILURE); \
        } \
    }


void malloc_check(void *res);
void realloc_check(void *res);