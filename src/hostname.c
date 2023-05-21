#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

#define DEFAULT_HOSTNAME "localhost"

char *get_hostname(void) {
	char *hostname = malloc(sizeof(char) * 256);
	hostname[0] = '\0';

	FILE *fp = fopen("/etc/hostname", "r");
	if (fp == NULL) {
		strcat(hostname, DEFAULT_HOSTNAME);
		return hostname;
	}

	char buffer[256];

	while (fgets(buffer, sizeof(buffer), fp) != NULL)
		strcat(hostname, buffer);

	int n = strlen(hostname);
	if (n > 0 && hostname[n - 1] == '\n')
		hostname[n - 1] = '\0';

	return hostname;
}

void hostname(void) {
	char *hostname = get_hostname();
	printf(" %shs%s  %s\n", CYAN, RESET, hostname);
	free(hostname);
}
