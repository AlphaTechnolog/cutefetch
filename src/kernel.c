#include <stdio.h>
#include <sys/utsname.h>

#include "kernel.h"
#include "colors.h"
#include "utils.h"

/**
 * Entry point for the kernel module. This prints the
 * ker: <version> part.
 *
 * void *prm: The already filled utsname structure.
 */
void module_kernel_init(void *prm)
{
	struct utsname *sutsname_buf;

	if (!(sutsname_buf = (struct utsname*)prm))
		fatal("Unable to obtain utsname buffer");

	printf("%sker%s  %s\n", BLUE, RESET, sutsname_buf->release);
}
