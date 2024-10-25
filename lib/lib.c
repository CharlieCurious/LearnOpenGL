#include <lib.h>
#include <stdlib.h>
#include <string.h>

char *load_shaders(FILE *shaders_file) {
    if (!shaders_file) {
        return NULL;
    }

    if(fseek(shaders_file, 0L, SEEK_END) != 0) {
        perror("Failed to determine shader source size.");
        return NULL;
    }
    
    long length = ftell(shaders_file);
    if (length < 0 || length > MAX_FILE_SIZE) {
        perror("File size error of file too large.");
        return NULL;
    }

    rewind(shaders_file);

    char *content = (char *)malloc(length + 2); // +2 for /n and /0.
    if (!content) {
        perror("Memory allocation failed.");
        return NULL;
    }

    size_t read_size = fread(content, 1, length, shaders_file);

    // Handle incomplete reads
    if (read_size != length) {
        perror("Failed to read the entire file.");
        free(content);
        return NULL;
    }

    memcpy(content + length, "\n\0", 2);

    return content;
}