#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

void malloc_check(void *res) {
    if (res == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
}