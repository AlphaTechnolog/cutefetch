#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "colors.h"
#include "hostname.h"

#define DEFAULT_HOSTNAME "localhost"

char *get_hostname(void) {
    char *hostname = malloc(sizeof(char) * 1024);
    gethostname(hostname, 1023);
    return hostname;
}

void hostname(void) {
	char *hostname = get_hostname();
	printf(" %shs%s  %s\n", CYAN, RESET, hostname);
	free(hostname);
}
