#ifndef MNTS_H_
#define MNTS_H_

typedef struct
{
	long long total_blocks;
	long long free_blocks;
	long long used_blocks;
	long long total_space;
	long long free_space;
	long long used_space;
	long long _block_size;
} mnt_usage_t;

void module_mnts_init(void *prm);

#endif
