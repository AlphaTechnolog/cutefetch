#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

/**
 * Calls perror(reason) and then exits.
 *
 * const char *reason: Message to pass to perror();
 */
void die(const char *reason)
{
	perror(reason);
	exit(EXIT_FAILURE);
}

/**
 * Shows an error message, prolly internal error, and then exits.
 *
 * const char *reason: Message to print.
 */
void fatal(const char *reason)
{
	fprintf(stderr, "Internal error: Cannot continue: %s\n", reason);
	exit(EXIT_FAILURE);
}

/**
 * Given a bytes number, this function will return a string with the formatted output
 * by trying to guess wether it's more suitable to use either gb, tb, mb, kb, etc.
 * NOTE: The caller is responsible for free()ing the result.
 *
 * long unsigned bytes: The bytes to format
 */
char *format_bytes(long unsigned bytes)
{
        const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
	char *buf;
        size_t i = 0;
        double val = (double) bytes;

	if (!(buf = malloc(60)))
		die("malloc");

        while (val >= 1024.0 && i < sizeof(units) / sizeof(units[0])) {
                val /= 1024.0;
                i++;
        }

        sprintf(buf, "%.2f %s", val, units[i]);

        return buf;
}
