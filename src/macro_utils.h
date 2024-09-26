#ifndef MACRO_UTILS_H_
#define MACRO_UTILS_H_

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define STR_STARTSWITH(str, prefix) strncmp(str, prefix, strlen(prefix)) == 0

#endif
