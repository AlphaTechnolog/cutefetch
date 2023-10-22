#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"

#include "../colors.h"

const char *format_bytes(long long bytes) {
	const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
	int i = 0;
	double val = (double) bytes;
	while (val >= 1024.0 && i < sizeof(units) / sizeof(units[0])) {
		val /= 1024.0;
		i++;
	}

	static char buf[32];
	sprintf(buf, "%.2f %s", val, units[i]);
	return buf;
}

void ram(void) {
	printf(" %sram%s ", MAGENTA, RESET);

	FILE *fp = fopen("/proc/meminfo", "r");
	if (fp == NULL) {
		fprintf(stderr, "Failed to open /proc/meminfo\n");
		exit(1);
	}

	long long total_mem = 0,
		  free_mem = 0,
		  used_mem = 0;

	char line[256];
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "MemTotal: %lld kB", &total_mem) == 1) {
			total_mem *= 1024;
		} else if (sscanf(line, "MemAvailable: %lld kB", &free_mem) == 1) {
			free_mem *= 1024;
		}
	}

	used_mem = total_mem - free_mem;

	char *str_usedmem = malloc(sizeof(char) * strlen(format_bytes(used_mem)) + 1);
	char *str_totalmem = malloc(sizeof(char) * strlen(format_bytes(total_mem)) + 1);

	sprintf(str_usedmem, "%s", format_bytes(used_mem));
	sprintf(str_totalmem, "%s", format_bytes(total_mem));

	printf("%s / %s\n", str_usedmem, str_totalmem);

	free(str_usedmem);
	free(str_totalmem);
}
