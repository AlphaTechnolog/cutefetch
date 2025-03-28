#ifndef MACRO_UTILS_H_
#define MACRO_UTILS_H_

#ifndef MAX
#define MAX(a, b) a > b ? a : b
#endif

#ifndef MIN
#define MIN(a, b) a < b ? a : b
#endif

#define STR_STARTSWITH(str, prefix) strncmp(str, prefix, strlen(prefix)) == 0

#endif
