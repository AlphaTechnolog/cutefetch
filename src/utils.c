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
 * long unsigned bytes: The bytes to format.
 * char *buf: The buffer to fill with the string.
 */
void format_bytes(long unsigned bytes, char *buf)
{
        const char* units[] = {"B", "KB", "MB", "GB", "TB", "PB", "EB", "ZB", "YB"};
        size_t i = 0;
        double val = (double) bytes;

        while (val >= 1024.0 && i < sizeof(units) / sizeof(units[0])) {
                val /= 1024.0;
                i++;
        }

        sprintf(buf, "%.2f %s", val, units[i]);
}

/**
 * Given a milliseconds amount, this function will return a string with the formatted output
 * by using a proper long format.
 *
 * long unsigned milliseconds: The milliseconds amount to format.
 * char *buf: The string buffer to fill in.
 */
void format_time(long unsigned milliseconds, char *buf)
{
	int seconds, minutes, hours;

	seconds = (milliseconds / 1000) % 60;
	minutes = (milliseconds / (1000 * 60)) % 60;
	hours = (milliseconds / (1000 * 60 * 60)) % 24;

	if (hours > 0)
		sprintf(buf, "%d hour(s), %d minute(s), %d second(s)", hours, minutes, seconds);
	else if (minutes > 0)
		sprintf(buf, "%d minute(s), %d second(s)", minutes, seconds);
	else
		sprintf(buf, "%d second(s)", seconds);
}
