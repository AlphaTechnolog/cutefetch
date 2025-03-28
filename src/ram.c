#include <stdio.h>
#include <string.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/vm_statistics.h>
#endif

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
	unsigned long totalram = 0, usedram = 0;
	char ftotalram[60], fusedram[60];

#ifdef __APPLE__
	uint64_t memsize;
	size_t len = sizeof(memsize);
	vm_size_t page_size;
	vm_statistics64_data_t vm_stats;

	if (sysctlbyname("hw.memsize", &memsize, &len, NULL, 0) != 0)
		die("sysctlbyname");
	totalram = memsize;

	if (host_page_size(mach_host_self(), &page_size) != KERN_SUCCESS)
		die("host_page_size");

	if (host_statistics64(mach_host_self(), HOST_VM_INFO64, (host_info64_t)&vm_stats, &(mach_msg_type_number_t){HOST_VM_INFO64_COUNT}) != KERN_SUCCESS)
		die("host_statistics64");

	usedram = ((unsigned long)vm_stats.active_count + 
		(unsigned long)vm_stats.inactive_count + 
		(unsigned long)vm_stats.wire_count) * page_size;
#else
	FILE *fp;
	unsigned long freeram = 0;
	char *line, linebuf[256];

	if (!(fp = fopen("/proc/meminfo", "r")))
		die("fopen");

	while ((line = fgets(linebuf, sizeof(linebuf), fp))) {
		if (sscanf(line, "MemAvailable: %ld kB", &freeram)) {
			freeram *= 1024;
		} else if (sscanf(line, "MemTotal: %ld kB", &totalram)) {
			totalram *= 1024;
		}
	}

	fclose(fp);

	usedram = totalram - freeram;
#endif

	format_bytes(totalram, ftotalram);
	format_bytes(usedram, fusedram);

	printf("%sram%s  %s / %s\n", MAGENTA, RESET, fusedram, ftotalram);
}
