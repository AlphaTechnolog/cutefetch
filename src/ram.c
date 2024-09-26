#include <stdio.h>
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
	char ftotalram[60], fusedram[60], *line, linebuf[256];

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

	format_bytes(totalram, ftotalram);
	format_bytes(usedram, fusedram);

	printf("%sram%s  %s / %s\n", MAGENTA, RESET, fusedram, ftotalram);
}
