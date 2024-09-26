#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ram.h"
#include "utils.h"
#include "colors.h"

/**
 * Entry point for the ram module. This function prints the
 * ram: <used>/<total> part.
 *
 * void *prm: Unused parameter.
 */
void module_ram_init(void *prm)
{
	FILE *fp;
	unsigned long totalram = 0, usedram = 0, freeram = 0;
	char *ftotalram, *fusedram, *line, linebuf[256];

	if (!(fp = fopen("/proc/meminfo", "r")))
		die("fopen");

	while ((line = fgets(linebuf, sizeof(linebuf), fp))) {
		if (sscanf(line, "MemAvailable: %ld kB", &freeram)) {
			freeram *= 1024;
		} else if (sscanf(line, "MemTotal: %ld kB", &totalram)) {
			totalram *= 1024;
		}
	}

	usedram = totalram - freeram;

	ftotalram = format_bytes(totalram);
	fusedram = format_bytes(usedram);

	printf("%sram%s  %s / %s\n", RED, RESET, fusedram, ftotalram);

	free(ftotalram);
	free(fusedram);
}
