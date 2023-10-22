#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "banner.h"
#include "colors.h"

#define BANNER_MAX_ROWS 3

char (*get_banner(void))[50] {
	static char banner[BANNER_MAX_ROWS][50] = {
		"(\\__/)",
		"(='.'=)",
		"(\")_(\")"
	};

	return banner;
}

static char *get_banner_row(int row) {
	if (row > BANNER_MAX_ROWS) {
		fprintf(stderr, "Invalid given row\n");
		exit(1);
	}

	char (*banner)[50] = get_banner();

	return banner[row];
}

void prbannerrow(int r) {
	char *str = get_banner_row(r);
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] == '"') {
			printf("%s%c%s", RED, str[i], RESET);
		} else if (str[i] == '=') {
			printf("%s%c%s", YELLOW, str[i], RESET);
		} else {
			printf("%c", str[i]);
		}
	}
}
