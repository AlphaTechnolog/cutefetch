#include <stdio.h>
#include <sys/utsname.h>

#include "arch.h"
#include "utils.h"
#include "colors.h"

/**
 * Entry point for the architecture module. This prints the
 * arch: <arch> part.
 *
 * void *prm: The already filled utsname structure.
 */
void module_arch_init(void *prm)
{
	struct utsname *sutsname_buf;

	if (!(sutsname_buf = (struct utsname*)prm))
		fatal("Unable to obtain utsname buffer");

	printf("%sarch%s %s\n", YELLOW, RESET, sutsname_buf->machine);
}
