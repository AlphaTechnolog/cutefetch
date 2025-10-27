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
	unsigned long long total_seconds = milliseconds / 1000ULL;
	unsigned int days, hours, minutes, seconds;

	days = (unsigned int)(total_seconds / 86400ULL);
	hours = (unsigned int)((total_seconds % 86400ULL) / 3600ULL);
	minutes = (unsigned int)((total_seconds % 3600ULL) / 60ULL);
	seconds = (unsigned int)(total_seconds % 60ULL);

	if (days > 0)
		sprintf(buf, "%u day(s), %u hour(s), %u minute(s), %u second(s)", days, hours, minutes, seconds);
	else if (hours > 0)
		sprintf(buf, "%u hour(s), %u minute(s), %u second(s)", hours, minutes, seconds);
	else if (minutes > 0)
		sprintf(buf, "%u minute(s), %u second(s)", minutes, seconds);
	else
		sprintf(buf, "%u second(s)", seconds);
}

/**
 * Prints a given character x times.
 *
 * NOTE: Doesn't appends \n in stdout.
 *
 * size_t times: Times to print `chr`.
 * char chr: Character to print.
 */
void printxtimes(size_t times, char chr)
{
	int i;
	char fmtted[] = { chr, 0 };

	for (i = 0; i < times; ++i)
		fputs(fmtted, stdout);
}
