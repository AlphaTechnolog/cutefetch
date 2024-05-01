#include <stdio.h>
#include <stdlib.h>
#include <mntent.h>
#include <string.h>
#include <stdbool.h>
#include <sys/statvfs.h>

#include "ram.h"
#include "disk.h"

#include "../colors.h"
#include "../utils.h"

static struct DiskUsage *get_disk_usage(const char *mnt) {
	struct statvfs fs_info;
	if (statvfs(mnt, &fs_info) != 0) {
		fprintf(stderr, "Failed to get file system info\n");
		exit(1);
	}

	long long block_size = fs_info.f_frsize;

	long long total_blocks = fs_info.f_blocks;
	long long free_blocks = fs_info.f_bfree;
	long long used_blocks = total_blocks - free_blocks;

	long long total_space = total_blocks * block_size;
	long long used_space = used_blocks * block_size;

	char *strtotal = malloc(sizeof(char) * 120);
	char *strused = malloc(sizeof(char) * 120);

	sprintf(strtotal, "%s", format_bytes(total_space));
	sprintf(strused, "%s", format_bytes(used_space));

	struct DiskUsage *usage = malloc(sizeof(struct DiskUsage));
	
	usage->mnt = mnt;
	usage->total = strtotal;
	usage->used = strused;

	return usage;
}

static inline void display_disk_usage(struct DiskUsage *usage, size_t offset) {
	for (size_t i = 0; i < offset; ++i)
		printf(" ");

	printf("%s / %s (%s%s%s)\n", usage->used, usage->total,
		CYAN, usage->mnt, RESET);
}

static inline void free_disk_usage(struct DiskUsage *usage) {
	free(usage->total);
	free(usage->used);
	free(usage);
}

static inline bool startswith(const char *pre, const char *str) {
    return strncmp(pre, str, strlen(pre)) == 0;
}

#define EXCEPTIONS_LENGTH 5
static inline bool in_exception_mountpoint(const char *mountpoint) {
	const char *exceptions_queries[] = {
		"/bedrock",
		"/home",
		"/root",
		"/tmp",
		"/usr"
	};

	bool result = false;

	for (int i = 0; i < EXCEPTIONS_LENGTH; ++i) {
		const char *query = exceptions_queries[i];
		if (startswith(query, mountpoint)) {
			result = true;
			break;
		}
	}

	return result;
}

static struct Mounts *get_mnts(void) {
	FILE *mounts_file = setmntent("/etc/mtab", "r");
	if (mounts_file == NULL) {
		perror("setmntent");
		exit(EXIT_FAILURE);
	}

	struct mntent *mount_entry;
	struct Mounts *mounts = malloc(sizeof(struct Mounts));

	malloc_check(mounts);

	mounts->capacity = 10;
	mounts->length = 0;

	char **mounts_strings = malloc(sizeof(char*) * mounts->capacity + 1);

	malloc_check(mounts_strings);

	while ((mount_entry = getmntent(mounts_file)) != NULL) {
		if (strcmp(mount_entry->mnt_type, "ext4") != 0 &&
            strcmp(mount_entry->mnt_type, "ext3") != 0 &&
            strcmp(mount_entry->mnt_type, "ext2") != 0 &&
            strcmp(mount_entry->mnt_type, "xfs") != 0 &&
            strcmp(mount_entry->mnt_type, "btrfs") != 0 &&
            strcmp(mount_entry->mnt_type, "ntfs") != 0 &&
            strcmp(mount_entry->mnt_type, "vfat") != 0) {
            continue;
        }

		if (in_exception_mountpoint(mount_entry->mnt_dir)) {
			continue;
		}

		if (mounts->length + 1 >= mounts->capacity) {
			mounts->capacity *= 2;
			mounts_strings = realloc(mounts_strings, sizeof(char*) * mounts->capacity + 1);
			realloc_check(mounts);
		}

		mounts_strings[mounts->length] = malloc(sizeof(char) * strlen(mount_entry->mnt_dir) + 1);
		malloc_check(mounts_strings[mounts->length]);
		sprintf(mounts_strings[mounts->length], "%s", mount_entry->mnt_dir);

		mounts->length++;
	}

	mounts->mounts = mounts_strings;

	return mounts;
}

static inline void free_mounts(struct Mounts *mounts) {
	for (size_t i = 0; i < mounts->length; ++i)
		free(mounts->mounts[i]);
	free(mounts);
}

void disk(size_t offset) {
	printf(" %sdsk%s ", RED, RESET);

	struct Mounts *mnts = get_mnts();

	for (size_t i = 0; i < mnts->length; ++i) {
		struct DiskUsage *mnt_usage = get_disk_usage((const char*) mnts->mounts[i]);
		display_disk_usage(mnt_usage, i == 0 ? 0 : offset + 5);
		free_disk_usage(mnt_usage);
	}

	free_mounts(mnts);
}
