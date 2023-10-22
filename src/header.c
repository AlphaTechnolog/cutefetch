#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>

#include "colors.h"
#include "header.h"
#include "system/hostname.h"

static inline char *whoami(void) {
    struct passwd *passwd = getpwuid(getuid());
    return passwd->pw_name;
}

void header(void) {
	char *username = whoami();
	char *hostname = get_hostname();

	printf(" %s%s%s@%s%s%s\n", CYAN, username, BLUE, MAGENTA, hostname, RESET);

	free(username);
	free(hostname);
}
