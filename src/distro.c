#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

#include "distro.h"
#include "colors.h"
#include "utils.h"
#include "macro_utils.h"

/**
 * The entry point for the distro module. This prints
 * the os: <distro> part.
 *
 * void *prm: Unused parameter
 */
void module_distro_init(void *prm)
{
	char pretty_name[40];
#ifdef __APPLE__
	char os_version[40];
	size_t len = sizeof(os_version);

	strlcpy(pretty_name, "macOS", sizeof(pretty_name));

	if (sysctlbyname("kern.osproductversion", os_version, &len, NULL, 0) != 0)
		die("sysctlbyname");

	strlcat(pretty_name, " ", sizeof(pretty_name));
	strlcat(pretty_name, os_version, sizeof(pretty_name));
#else
	FILE *fp;
	char *line, line_buf[100];

	strlcpy(pretty_name, "Unavailable", sizeof(pretty_name));

	if (!(fp = fopen("/etc/os-release", "r")))
		die("fopen");

	while ((line = fgets(line_buf, sizeof(line_buf), fp)))
		if (sscanf(line, "PRETTY_NAME=\"%[^\"]\"", pretty_name))
			break;

	fclose(fp);
#endif

	printf("%sos   %s%s\n", GREEN, RESET, pretty_name);
}
