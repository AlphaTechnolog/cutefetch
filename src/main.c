#include <stdio.h>
#include <string.h>

void prbannerrow(int row);
char (*get_banner())[50];

void header(void);
void os(void);
void kernel(void);
void ram(void);
void hostname(void);
void disk(void);

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
	void (*aligneds[3])() = {os, kernel, ram};
	for (int i = 0; i < 3; i++) {
		prbannerrow(i);
		aligneds[i]();
	}

	// rendering the missaligneds ones
	#define MISSALIGNED_SIZE 2

	void (*missaligneds[MISSALIGNED_SIZE])() = {hostname, disk};
	for (int i = 0; i < MISSALIGNED_SIZE; i++) {
		for (size_t j = 0; j < max_len; j++)
			printf(" ");
		missaligneds[i]();
	}

	return 0;
}
