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
    char folderPath[] = "shaders/";
    char *fileName = "vertex.glsl";

    // Act
    pathParsingResult result = getSourceFilePath(resultBuffer, 128, folderPath, fileName);

    // Assert
    TEST_ASSERT_EQUAL_STRING("shaders/vertex.glsl", resultBuffer);
    TEST_ASSERT_EQUAL_UINT64(PATH_PARSING_SUCCESS, result);
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

void shouldReturnErrorIfParametersAreNull(void) {
    // Arrange
    char buffer[128];
    char folderPath[] = "shaders/";
    char *fileName = "vertex.glsl";

    // Act
    pathParsingResult resultWithBufferNull = getSourceFilePath(NULL, 128, folderPath, fileName);
    pathParsingResult resultWithFolderPathNull = getSourceFilePath(buffer, 128, NULL, fileName);
    pathParsingResult resultWithFileNameNull = getSourceFilePath(buffer, 128, folderPath, NULL);

    // Assert
    TEST_ASSERT_EQUAL_UINT64(PATH_PARSING_ERROR, resultWithBufferNull);
    TEST_ASSERT_EQUAL_UINT64(PATH_PARSING_ERROR, resultWithFolderPathNull);
    TEST_ASSERT_EQUAL_UINT64(PATH_PARSING_ERROR, resultWithFileNameNull);
}

void shouldReturnErrorIfBufferIsTooSmall(void) {
    // Arrange
    char buffer[1];
    char folderPath[] = "shaders/";
    char *fileName = "vertex.glsl";

    // Act
    pathParsingResult result = getSourceFilePath(buffer, 1, folderPath, fileName);

    // Assert
    TEST_ASSERT_EQUAL_UINT64(PATH_PARSING_ERROR, result);
}

void shouldReturnNullIfShadersFileIsNull(void) {
    // Act
    loadFileContentResult = loadFileContentToString(NULL);

    // Assert
    TEST_ASSERT_NULL(loadFileContentResult);
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
    RUN_TEST(shouldReturnErrorIfParametersAreNull);
    RUN_TEST(shouldReturnErrorIfBufferIsTooSmall);
    RUN_TEST(shouldReturnNullIfShadersFileIsNull);
    return UNITY_END();
}