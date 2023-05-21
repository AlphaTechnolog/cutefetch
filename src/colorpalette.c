#include <stdio.h>
#include <stdlib.h>

#include "colors.h"

#define CHARACTER ""

void display_colorpalette(void) {
	char *colors[8] = {
		BLACK, RED, GREEN,
		YELLOW, BLUE, MAGENTA,
		CYAN, WHITE
	};

	for (int i = 0; i < 8; i++)
		printf("%s%s ", colors[i], CHARACTER);

	printf("%s\n", RESET);
}
