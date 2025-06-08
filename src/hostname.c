#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pwd.h>
#include <unistd.h>
#include <string.h>

#include "strlcpy.h"
#include "hostname.h"
#include "colors.h"

/**
 * Entry point for the hostname module, this prints
 * the <user>@<hostname> part.
 *
 * void *prm: Unused parameter
 */
void module_hostname_init(void *prm)
{
	char hostname[100], username[100];
	uid_t uid;
	struct passwd *pw;

	uid = geteuid();

	if (!(pw = getpwuid(uid)))
		username[0] = '\0';
	else
		strlcpy(username, pw->pw_name, 100);

	gethostname(hostname, 100);

	printf("%s%s%s@%s%s%s\n", CYAN, username, BLUE,
		MAGENTA, hostname, RESET);
}

/**
 * Entry point for the hostname module, this prints
 * the hs: <hostname> part.
 *
 * void *prm: Unused parameter
 */
void module_simple_hostname_init(void *prm)
{
	char hostname[100];
	gethostname(hostname, 100);
	printf("%shs%s   %s\n", CYAN, RESET, hostname);
}
