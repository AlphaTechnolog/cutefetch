#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "colors.h"

char *catch_kerver(void) {
	char buffer[1024];

	FILE *fp = popen("uname -r", "r");
	if (fp == NULL) {
		fprintf(stderr, "Cannot get the kernel version, do you have uname installed??\n");
		exit(1);
	}

	char *kernel_version = malloc(sizeof(char) * 1024);
	kernel_version[0] = '\0';

	while (fgets(buffer, sizeof(buffer), fp) != NULL)
		strcat(kernel_version, buffer);

	pclose(fp);

	int n = strlen(kernel_version);
	if (n > 0 && kernel_version[n - 1] == '\n')
		kernel_version[n - 1] = '\0';

	return kernel_version;
}

void kernel(void) {
	char *kernel_version = catch_kerver();
	printf(" %sker%s %s\n", BLUE, RESET, kernel_version);
	free(kernel_version);
}
