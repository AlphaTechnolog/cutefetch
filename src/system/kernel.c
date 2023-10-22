#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <sys/utsname.h>

#include "kernel.h"
#include "../colors.h"

static inline char *catch_kerver(void) {
    struct utsname buffer;

    errno = 0;
    if (uname(&buffer) != 0) {
        perror("uname");
        exit(EXIT_FAILURE);
    }

    char *release = malloc(sizeof(char) * strlen(buffer.release));
    sprintf(release, "%s", buffer.release);

    return release;
}

void kernel(void) {
	char *kernel_version = catch_kerver();
	printf(" %sker%s %s\n", BLUE, RESET, kernel_version);
	free(kernel_version);
}
