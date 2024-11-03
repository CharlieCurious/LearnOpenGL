#pragma once

#define PATH_PARSING_ERROR 0
#define PATH_PARSING_SUCCESS 1

typedef unsigned int pathParsingResult;

#include <stdio.h>
#include <stdlib.h>

pathParsingResult getSourceFilePath(
    char *outputBuffer, 
    size_t bufferSize,
    char *folderPath,
    const char *fileName
    );

char *loadFileContentToString(FILE *file);