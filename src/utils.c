#include <stdio.h>
#include <stdlib.h>

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
