#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "macro_utils.h"
#include "banner.h"
#include "colors.h"

/* modules */
#include "hostname.h"
#include "distro.h"

static void printxtimes(size_t, char);
static void hmodprint(size_t, void (*)(void));
static void modprint(int*, size_t, size_t, void (*)(void));

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
	char fmtted[2];

	fmtted[0] = chr;
	fmtted[1] = '\0';

	for (i = 0; i < times; ++i)
		fputs(fmtted, stdout);
}

/**
 * Prints a given module without printing its current banner iteration.
 *
 * size_t offsethint: The length of hugest row in the banner.
 * void (*modfn)(void): Module function.
 */
void hmodprint(size_t offsethint, void (*modfn)(void))
{
	printxtimes(offsethint + 1, ' ');
	modfn();
}

/**
 * Prints a given module by maintaining the alignment between outputs.
 *
 * int *idxptr: Pointer to the current module index integer value.
 * size_t maxrows: Maximum number of rows that the banner can provide.
 * size_t offsethint: The length of the hugest row in the banner.
 * void (*modfn)(void): Module function.
 */
void modprint(int *idxptr, size_t maxrows, size_t offsethint, void (*modfn)(void))
{
	int idx, i;
	char row[offsethint + 1];

	idx = *idxptr;
	strncpy(row, idx > maxrows ? "" : banner[idx], offsethint + 1);
	*idxptr = idx + 1;

	/* printing char by char so we can color it a little bit */
	for (i = 0; row[i] != '\0'; ++i)
		switch (row[i]) {
			case '=':
				printf("%s%c%s", YELLOW, row[i], RESET);
				break;
			case '"':
				printf("%s%c%s", RED, row[i], RESET);
				break;
			default:
				printf("%c", row[i]);
				break;
		}

	/* printing needed spaces to align modules outputs. */
	printxtimes(offsethint - strlen(row) + 1, ' ');

	modfn();
}


int main()
{
	int i;
	size_t bannerlen, banneroffset;

	bannerlen = sizeof(banner) / sizeof(banner[1]);

	for (i = 0, banneroffset = 0; i < bannerlen; ++i)
		banneroffset = MAX(banneroffset, strlen(banner[i]));

	i = 0;

	hmodprint(banneroffset, module_hostname_init);
	modprint(&i, bannerlen, banneroffset, module_distro_init);

	return 0;
}
