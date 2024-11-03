#include <file_handling.h>
#include <stdio.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // 1 MB

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

char *loadFileContentToString(FILE *file) {
    if (!file) {
        return NULL;
    }

    if(fseek(file, 0L, SEEK_END) != 0) {
        perror("Failed to determine file size.");
        return NULL;
    }
    
    long length = ftell(file);
    if (length < 0 || length > MAX_FILE_SIZE) {
        perror("File size error of file too large.");
        return NULL;
    }

    rewind(file);

    char *content = (char *)malloc(length + 2); // +2 for /n and /0.
    if (!content) {
        perror("Memory allocation failed.");
        return NULL;
    }

    size_t read_size = fread(content, 1, length, file);

    // Handle incomplete reads
    if (read_size != length) {
        perror("Failed to read the entire file.");
        free(content);
        return NULL;
    }

    memcpy(content + length, "\n\0", 2);

    return content;
}

void sanitizePath(char *path) {
    size_t len = strlen(path);
    if ((strcmp(path, "./") == 0) || (strcmp(path, "/") == 0 )) {
        path[0] = '\0';
        return;
    }

    if (len > 0 && path[len - 1] == '/') {
        path[len - 1] = '\0';
    }
}

