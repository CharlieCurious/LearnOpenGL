#include <file_handling.h>
#include <stdio.h>
#include <string.h>

static void sanitizePath(char *path);

pathParsingResult getSourceFilePath(
    char *outputBuffer, 
    size_t bufferSize,
    const char *folderPath,
    const char *fileName
    ) {
        if (!outputBuffer || !folderPath || !fileName) {
            return PATH_PARSING_ERROR; 
        }

        size_t folderPathLen = strlen(folderPath);
        if (folderPathLen + 1 > bufferSize) {
            return PATH_PARSING_ERROR;
        }

        snprintf(outputBuffer, bufferSize, "%s/%s", folderPath, fileName);

        return PATH_PARSING_SUCCESS;
}

void sanitizePath(char *path) {
    size_t len = strlen(path);

    if ((strcmp(path, "./") == 0) || (strcmp(path, "/") == 0 )) {
        path[0] = '\0';
        return;
    }

    if (len > 2 && strncmp(path, "./", 2) == 0) {
        memmove(path, path + 2, len - 1);
    }
    else if (len > 1 && path[0] == '/') {
        memmove(path, path + 1, len);
    }

    len = strlen(path);
    if (len > 0 && path[len - 1] == '/') {
        path[len - 1] == '\0';
    }
}

