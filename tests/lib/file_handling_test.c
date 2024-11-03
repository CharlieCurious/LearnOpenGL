#include <assert.h>
#include <file_handling.h>
#include <string.h>
#include <unity.h>

FILE *testFile = NULL;
const char *test_data = "Some shader code";
char *loadFileContentResult = NULL;

FILE *createTmpFile(const char *data) {
    FILE *file = tmpfile();
    assert(file != NULL);
    fwrite(data, sizeof(char), strlen(data), file);
    rewind(file);
    return file;
}

void setUp() {
}

void shouldGetSourceFilePath(void) {
    // Arrange
    char resultBuffer[128];
    char *folderPath = "shaders";
    char *fileName = "vertex.glsl";

    // Act
    getSourceFilePath(resultBuffer, 128, folderPath, fileName);

    // Assert
    TEST_ASSERT_EQUAL_STRING("shaders/vertex.glsl", resultBuffer);
}

void shouldLoadFileContentIntoString(void) {
    // Arrange
    testFile = createTmpFile(test_data);
    char *expectedResult = "Some shader code\n";

    // Act
    loadFileContentResult = loadFileContentToString(testFile);

    // Assert
    TEST_ASSERT_NOT_NULL(loadFileContentResult);
    TEST_ASSERT_EQUAL_STRING(expectedResult, loadFileContentResult);
}

void shouldReturnNullIfShadersFileIsNull(void) {
    // Act
    loadFileContentResult = loadFileContentToString(NULL);

    // Assert
    TEST_ASSERT_NULL(loadFileContentResult);
}

void shouldSanitizeFolderPath(void) {
    // Arrange
    char pathWithLeasingSlash[] = "/shaders";
    char pathWithLeadingDotAndSlash[] = "./shaders";
    char pathWithTrailingSlash[] = "shaders/";
    char pathWithAllSlashes[] = "./shaders/";
    char pathWithMoreThanOneFolderDepth[] = "./build/src/shaders/";

    // Act
    sanitizePath(pathWithLeasingSlash);
    sanitizePath(pathWithLeadingDotAndSlash);
    sanitizePath(pathWithTrailingSlash);
    sanitizePath(pathWithAllSlashes);
    sanitizePath(pathWithMoreThanOneFolderDepth);

    // Assert
    TEST_ASSERT_EQUAL_STRING("/shaders", pathWithLeasingSlash);
    TEST_ASSERT_EQUAL_STRING("./shaders", pathWithLeadingDotAndSlash);
    TEST_ASSERT_EQUAL_STRING("shaders", pathWithTrailingSlash);
    TEST_ASSERT_EQUAL_STRING("./shaders", pathWithAllSlashes);
    TEST_ASSERT_EQUAL_STRING("./build/src/shaders", pathWithMoreThanOneFolderDepth);
}

void tearDown() {
    if (testFile) {
        fclose(testFile);
        testFile = NULL;
    }
    if (loadFileContentResult) {
        free(loadFileContentResult);
        loadFileContentResult = NULL;
    }
}

int main() {
    UNITY_BEGIN();
    RUN_TEST(shouldGetSourceFilePath);
    RUN_TEST(shouldLoadFileContentIntoString);
    RUN_TEST(shouldReturnNullIfShadersFileIsNull);
    RUN_TEST(shouldSanitizeFolderPath);
    return UNITY_END();
}