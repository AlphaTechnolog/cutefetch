#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "hostname.h"

#include "../utils.h"
#include "../colors.h"

char *get_hostname(void) {
    char *hostname = malloc(sizeof(char) * 1024);
    malloc_check(hostname);
    gethostname(hostname, 1023);
    return hostname;
}

void hostname(void) {
	char *hostname = get_hostname();
	printf(" %shs%s  %s\n", CYAN, RESET, hostname);
	free(hostname);
}
