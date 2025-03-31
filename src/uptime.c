#include <stdio.h>
#ifdef __APPLE__
#include <time.h>
#else
#include <sys/sysinfo.h>
#endif

#include "uptime.h"
#include "utils.h"
#include "colors.h"

/**
 * Entry point for the uptime module. This is responsible for
 * printing the upt: <uptime> part.
 *
 * void *prm: The shared boottime/sysinfo structure ptr.
 */
void module_uptime_init(void *prm)
{
	char fuptime[256];
	long unsigned uptime_ms;

#ifdef __APPLE__
	struct timespec *boottime;
	struct timespec now;

	if (!(boottime = (struct timespec*)prm))
		fatal("Unable to obtain boottime shared buffer");

	if (clock_gettime(CLOCK_REALTIME, &now) != 0)
		die("clock_gettime");

	uptime_ms = (now.tv_sec - boottime->tv_sec) * 1000;
	uptime_ms += (now.tv_nsec - boottime->tv_nsec) / 1000000;
#else
	struct sysinfo *info;

	if (!(info = (struct sysinfo*)prm))
		fatal("Unable to obtain sysinfo shared buffer");

	uptime_ms = info->uptime * 1000;
#endif

	format_time(uptime_ms, fuptime);

	printf("%supt%s  %s\n", BLUE, RESET, fuptime);
}
