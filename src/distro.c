#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	FILE *fp;
	char *line, line_buf[100], pretty_name[40];

	strlcpy(pretty_name, "Unavailable", sizeof(pretty_name));

	if (!(fp = fopen("/etc/os-release", "r")))
		die("fopen");

	while ((line = fgets(line_buf, sizeof(line_buf), fp))) {
		if (sscanf(line, "PRETTY_NAME=\"%[^\"]\"", pretty_name)) {
			break;
		}
	}

	fclose(fp);

	printf("%sos   %s%s\n", GREEN, RESET, pretty_name);
}
