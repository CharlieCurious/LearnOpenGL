#include <assert.h>
#include <lib.h>
#include <string.h>
#include <unity.h>

// Test variable
FILE *test_file = NULL;
const char *test_data = "Some shader code";

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
    char *result = load_shaders(test_file);

    // Assert
    TEST_ASSERT_NOT_NULL(result);
    TEST_ASSERT_EQUAL_STRING(expected_result, result);
}

void tearDown() {
    if (test_file) {
        fclose(test_file);
        test_file = NULL;
    }
}

int main(int argc, char **argv){
    UNITY_BEGIN();
    RUN_TEST(should_load_shaders_correctly);
    return UNITY_END();
}