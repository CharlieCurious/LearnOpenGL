#pragma once
#include <stdio.h>

#define MAX_FILE_SIZE 1048576 // 1 MB

char *load_shaders(FILE *shaders_file);
FILE *open_shaders_file(char *file_path);