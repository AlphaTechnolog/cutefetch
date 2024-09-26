#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

/**
 * Calls perror(reason) and then exits.
 */
void die(const char *reason)
{
	perror(reason);
	exit(EXIT_FAILURE);
}
