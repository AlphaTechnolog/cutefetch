#include <dirent.h>
#include <errno.h>
#include <stdbool.h>

#include "bedrock.h"

bool is_bedrock(void) {
    DIR *bedrock = opendir("/bedrock");

    if (ENOENT == errno || !bedrock) {
        return false;
    }

    closedir(bedrock);

    return true;
}