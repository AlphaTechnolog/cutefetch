#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>

#include "uptime.h"
#include "utils.h"
#include "colors.h"

/**
 * Entry point for the uptime module. This is responsible for
 * printing the upt: <uptime> part.
 *
 * void *prm: The shared sysinfo ds ptr.
 */
void module_uptime_init(void *prm)
{
	struct sysinfo *info;
	char fuptime[256];

	if (!(info = (struct sysinfo*)prm))
		fatal("Unable to obtain sysinfo shared buffer");

	format_time(info->uptime * 1000, fuptime);

	printf("%supt%s  %s\n", BLUE, RESET, fuptime);
}
