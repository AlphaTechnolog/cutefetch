#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "os.h"

#include "../bedrock.h"
#include "../colors.h"

static char *get_pretty_name(void) {
	char buffer[2024];

	if (is_bedrock()) {
		const char *pretty = "Bedrock";
		char *tmp = malloc(strlen(pretty) + 1);
		strcpy(tmp, pretty);
		return tmp;
	}

	FILE *fp = fopen("/etc/os-release", "r");
	if (fp == NULL) {
		fprintf(stderr, "Error opening /etc/os-release\n");
		exit(1);
	}

	char *osname = malloc(sizeof(char*) * 300);
	char prefix[] = "PRETTY_NAME";

	while (fgets(buffer, sizeof(buffer), fp) != NULL) {
		if (strncmp(buffer, prefix, strlen(prefix)) == 0) {
			int n = strlen("PRETTY_NAME=");
			char *ptr = strstr(buffer, "PRETTY_NAME=");
			if (ptr != NULL) {
				ptr += n;
				char processed[1024];
				strcpy(processed, strtok(ptr, "\"\n"));
				sprintf(osname, "%s", processed);
			} else {
				sprintf(osname, "Cannot get os.");
			}
		}
	}

	return osname;
}

void os(void) {
	char *osname = get_pretty_name();
	printf("  %sos%s  %s\n", GREEN, RESET, osname);
	free(osname);
}
