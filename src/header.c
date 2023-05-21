#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

char *get_hostname(void);

char *whoami(void) {
	char buffer[1024];

	FILE *fp = popen("whoami", "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot fetch the username\n");
		exit(1);
	}

	char *username = malloc(sizeof(char) * 1024);
	username[0] = '\0';

	while (fgets(buffer, sizeof(buffer), fp) != NULL)
		strcat(username, buffer);

	pclose(fp);

	int n = strlen(username);
	if (n > 0 && username[n - 1] == '\n')
		username[n - 1] = '\0';

	return username;
}

void header(void) {
	char *username = whoami();
	char *hostname = get_hostname();

	printf(" %s%s%s@%s%s%s\n", CYAN, username, BLUE, MAGENTA, hostname, RESET);

	free(username);
	free(hostname);
}
