#include <stdio.h>

#include "palette.h"
#include "colors.h"

#define CHARACTER ""

/**
 * This module prints the colored circles in the output.
 *
 * void *prm: Unused parameter.
 */
void module_palette_init(void *prm) {
	int i = 0;

        char *colors[8] = {
                BLACK, RED, GREEN,
                YELLOW, BLUE, MAGENTA,
                CYAN, WHITE
        };

        for (; i < 8; i++)
                printf("%s%s ", colors[i], CHARACTER);

        printf("%s\n", RESET);
}
