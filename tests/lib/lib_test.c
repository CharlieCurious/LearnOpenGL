#include <assert.h>
#include <lib.h>
#include <stdlib.h>
#include <string.h>
#include <unity.h>

// Test variable
FILE *test_file = NULL;
const char *test_data = "Some shader code";
char *load_shaders_result = NULL;

FILE *create_tmp_file(const char *data) {
    FILE *file = tmpfile();
    assert(file != NULL);
    fwrite(data, sizeof(char), strlen(data), file);
    rewind(file);
    return file;
}

void setUp() {
}

void should_load_shaders_correctly(void) {
    // Arrange
    test_file = create_tmp_file(test_data);
    char *expected_result = "Some shader code\n";

    // Act
    load_shaders_result = load_shaders(test_file);

    // Assert
    TEST_ASSERT_NOT_NULL(load_shaders_result);
    TEST_ASSERT_EQUAL_STRING(expected_result, load_shaders_result);
}

void should_not_load_file_too_large(void) {
    // Arrange
    test_file = tmpfile();
    fseek(test_file, MAX_FILE_SIZE + 1, SEEK_SET);
    fputc('\0', test_file);
    rewind(test_file);

    // Act
    load_shaders_result = load_shaders(test_file);

    // Assert
    TEST_ASSERT_NULL(load_shaders_result);
}

void should_return_null_if_shaders_file_is_null(void) {
    // Act
    load_shaders_result = load_shaders(NULL);

    // Assert
    TEST_ASSERT_NULL(load_shaders_result);
}

void tearDown() {
    if (test_file) {
        fclose(test_file);
        test_file = NULL;
    }
    if (load_shaders_result) {
        free(load_shaders_result);
        load_shaders_result = NULL;
    }
}

int main(int argc, char **argv){
    UNITY_BEGIN();
    RUN_TEST(should_load_shaders_correctly);
    RUN_TEST(should_not_load_file_too_large);
    RUN_TEST(should_return_null_if_shaders_file_is_null);
    return UNITY_END();
}