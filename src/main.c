#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/utsname.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#include <mach/mach.h>
#include <mach/vm_statistics.h>
#else
#include <sys/sysinfo.h>
#endif

#include "utils.h"
#include "macro_utils.h"
#include "banner.h"
#include "colors.h"

/* modules */
#include "hostname.h"
#include "distro.h"
#include "kernel.h"
#include "arch.h"
#include "ram.h"
#include "uptime.h"
#include "mnts.h"
#include "palette.h"

static void hmodprint(size_t, void (*)(void*), void *prm);
static void modprint(int*, size_t, size_t, void (*)(void*), void *prm);

/**
 * Prints a given module without printing its current banner iteration.
 *
 * size_t offsethint: The length of hugest row in the banner.
 * void (*modfn)(void*): Module function.
 * void *prm: The parameter to pass to the module function.
 */
void hmodprint(size_t offsethint, void (*modfn)(void*), void *prm)
{
	printxtimes(offsethint + 1, ' ');
	modfn(prm);
}

/**
 * Prints a given module by maintaining the alignment between outputs.
 *
 * int *idxptr: Pointer to the current module index integer value.
 * size_t maxrows: Maximum number of rows that the banner can provide.
 * size_t offsethint: The length of the hugest row in the banner.
 * void (*modfn)(void*): Module function.
 * void *prm: The parameter to pass to the module function.
 */
void modprint(int *idxptr, size_t maxrows, size_t offsethint, void (*modfn)(void*), void *prm)
{
	int idx, i;
	char row[offsethint + 1];

	idx = *idxptr;
	strncpy(row, idx > maxrows ? "" : banner[idx], offsethint + 1);
	*idxptr = idx + 1;

	/* printing char by char so we can color it a little bit */
	for (i = 0; row[i] != '\0'; ++i)
		switch (row[i]) {
			case '=':
				printf("%s%c%s", YELLOW, row[i], RESET);
				break;
			case '"':
				printf("%s%c%s", RED, row[i], RESET);
				break;
			default:
				printf("%c", row[i]);
				break;
		}

	/* printing needed spaces to align modules outputs. */
	printxtimes(offsethint - strlen(row) + 1, ' ');

	modfn(prm);
}


int main()
{
	int i;
	size_t bannerlen, banneroffset;
	struct utsname sutsname_buf;
#ifdef __APPLE__
	struct timespec boottime;
#else
	struct sysinfo sinfo_buf;
#endif

	/* populate shared utsname buffer structure */
	if (uname(&sutsname_buf) != 0)
		die("uname");

#ifdef __APPLE__
	if (sysctlbyname("kern.boottime", &boottime, &(size_t){sizeof(boottime)}, NULL, 0) != 0)
		die("sysctlbyname");
#else
	if (sysinfo(&sinfo_buf) != 0)
		die("sysinfo");
#endif

	bannerlen = sizeof(banner) / sizeof(banner[1]);

	for (i = 0, banneroffset = 0; i < bannerlen; ++i)
		banneroffset = MAX(banneroffset, strlen(banner[i]));

	i = 0;

	hmodprint(banneroffset, module_hostname_init, NULL);

	modprint(&i, bannerlen, banneroffset, module_distro_init, NULL);
	modprint(&i, bannerlen, banneroffset, module_kernel_init, (void*)&sutsname_buf);
	modprint(&i, bannerlen, banneroffset, module_arch_init, (void*)&sutsname_buf);
	modprint(&i, bannerlen, banneroffset, module_simple_hostname_init, NULL);
	modprint(&i, bannerlen, banneroffset, module_ram_init, NULL);
#ifdef __APPLE__
	modprint(&i, bannerlen, banneroffset, module_uptime_init, (void*)&boottime);
#else
	modprint(&i, bannerlen, banneroffset, module_uptime_init, (void*)&sinfo_buf);
#endif
	modprint(&i, bannerlen, banneroffset, module_mnts_init, (void*)&banneroffset);
	modprint(&i, bannerlen, banneroffset, module_palette_init, NULL);

	return 0;
}
