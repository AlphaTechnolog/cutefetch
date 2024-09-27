#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstab.h>
#include <sys/statvfs.h>

#include "mnts.h"
#include "utils.h"
#include "colors.h"

/**
 * Calculates the usage information about a given mntpoint by returning
 * a mnt_usage_t data structure which contains all the needed fields.
 * NOTE: Caller is responsible for calling mnt_usage_deinit() for the result.
 *
 * char *mntpoint: The mountpoint to inspect.
 */
static mnt_usage_t *mnt_usage_init(char *mntpoint)
{
	mnt_usage_t *m;
	struct statvfs fs_info;

	if (!(m = malloc(sizeof(mnt_usage_t))))
		die("malloc");

	if (statvfs(mntpoint, &fs_info) != 0)
		die("statvfs");

	m->_block_size = fs_info.f_frsize;

	m->total_blocks = fs_info.f_blocks;
	m->free_blocks = fs_info.f_bfree;
	m->used_blocks = m->total_blocks - m->free_blocks;

	m->total_space = m->total_blocks * m->_block_size;
	m->free_space = m->free_blocks * m->_block_size;
	m->used_space = m->used_blocks * m->_block_size;

	return m;
}

/**
 * Deinitialises allocated memory by mnt_usage_init(). Should be called after
 * being done with the information provided.
 *
 * mnt_usage_t *m: The allocated ptr.
 */
static void mnt_usage_deinit(mnt_usage_t *m)
{
	free(m);
}

/**
 * Prints in stdout information about the given fstab entry.
 *
 * struct fstab *entry: The entry to print info about.
 */
static void display_mnt(struct fstab *entry)
{
	mnt_usage_t *m;
	char fused_space[60], ftotal_space[60];

	m = mnt_usage_init(entry->fs_file);

	format_bytes(m->used_space, fused_space);
	format_bytes(m->total_space, ftotal_space);

	mnt_usage_deinit(m);

	printf("%s / %s (%s%s%s::%s%s%s)\n",
		fused_space, ftotal_space,
		BLUE, entry->fs_file, CYAN,
		GREEN, entry->fs_vfstype, RESET);
}

/**
 * Entry point for the mnts module, this module is the responsible for printing
 * the fstab mountpoints part.
 *
 * void *prm: The offset to leave in the left.
 */
void module_mnts_init(void *prm)
{
	struct fstab *cursor;
	size_t *banneroffset;
	int i = 0;
	const char *prefix = "dsk";

	banneroffset = (size_t*)prm;

	if (setfsent() != 1)
		die("setfsent");

	printf("%s%s%s  ", RED, prefix, RESET);

	while ((cursor = getfsent()) != NULL) {
		if (strcmp(cursor->fs_vfstype, "swap") == 0) continue;
		if (i > 0) printxtimes(*banneroffset + strlen(prefix) + 3, ' ');
		display_mnt(cursor);
		i++;
	}

	endfsent();
}
