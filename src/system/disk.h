#pragma once

struct DiskUsage {
    const char *mnt;
    char *total;
    char *used;
};

struct Mounts {
    char **mounts;
    unsigned int capacity;
    unsigned int length;
};

void disk(size_t offset);