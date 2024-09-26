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
 */
void module_distro_init(void)
{
	FILE *fp;
	char *line, line_buf[100], pretty_name[20];

	strlcpy(pretty_name, "Unavailable", sizeof(pretty_name));

	if (!(fp = fopen("/etc/os-release", "r")))
		die("fopen");

	while ((line = fgets(line_buf, sizeof(line_buf), fp))) {
		if (STR_STARTSWITH(line, "PRETTY_NAME")) {
			char *cur;

			/* if can't be found, we're just gonna leave it as Unavailable */
			if (!(cur = strchr(line, '"')))
				break;

			/* copy the cursor without the leading " in the start and the end */
			if (cur[0] == '"') cur++;
			strlcpy(pretty_name, cur, strlen(cur) - 1);

			break;
		}
	}

	fclose(fp);

	printf("%sos  %s%s\n", GREEN, RESET, pretty_name);
}
