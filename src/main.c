#include <stdio.h>
#include <string.h>

#include "banner.h"
#include "header.h"

#include "system/os.h"
#include "system/kernel.h"
#include "system/ram.h"
#include "system/hostname.h"

void disk(void);

void display_colorpalette(void);

int main() {
	char (*banner)[50] = get_banner();
	size_t max_len = 0;
	for (int i = 0; i < 3; i++)
		if (strlen(banner[i]) > max_len)
			max_len = strlen(banner[i]);

	for (size_t i = 0; i < max_len; i++)
		printf(" ");

	header();

	// rendering the aligneds functions relative to the banner size.
	void (*aligneds[3])() = {os, kernel, hostname};
	for (int i = 0; i < 3; i++) {
		prbannerrow(i);
		aligneds[i]();
	}

	// rendering the missaligneds ones
	#define MISSALIGNED_SIZE 2

	void (*missaligneds[MISSALIGNED_SIZE])() = {ram, disk};
	for (int i = 0; i < MISSALIGNED_SIZE; i++) {
		for (size_t j = 0; j < max_len; j++)
			printf(" ");
		missaligneds[i]();
	}

	for (size_t i = 0; i < max_len; i++)
		printf(" ");

	printf(" ");
	display_colorpalette();

	return 0;
}
