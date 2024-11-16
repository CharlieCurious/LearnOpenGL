#include <shader.h>
#include <file_handling.h>
#include <cglm/cglm.h>
#include <lib.h>
#include <stb_image.h>
#include <stdbool.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float yaw = -90.0f;
float pitch = 0.0f;
float lastX = 400;
float lastY = 300;
float fov = 45.0f;
bool isFirstMouse = true;

void processCamaraInput(GLFWwindow *window);
void mouseCallback(GLFWwindow *window, double xpos, double ypos);
void scrollCallback(GLFWwindow *window, double xoffset, double yoffset);

// Camara
vec3 camaraPos = (vec3){0.0f, 0.0f, 3.0f};
vec3 camaraFront = (vec3){0.0f, 0.0f, -1.0f};
vec3 camaraUp = (vec3){0.0f, 1.0f, 0.0f};

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <shader-folder-path> <texture-folder-path>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char vertexShaderPath[256];
    getSourceFilePath(vertexShaderPath, 256, argv[1], "7.1.camara.vs");
    
    char fragmentShaderPath[256];
    getSourceFilePath(fragmentShaderPath, 256, argv[1], "7.1.camara.fs");

    char containerTexturePath[256];
    getSourceFilePath(containerTexturePath, 256, argv[2], "container.jpg");

    char awesomefaceTextureFilePath[256];
    getSourceFilePath(awesomefaceTextureFilePath, 256, argv[2], "awesomeface.png");

    initializeGLFW();
    GLFWwindow *window = createGLFWwindowOrExit(SCR_WIDTH, SCR_HEIGHT);
    glfwMakeContextCurrent(window);
    loadOpenGLFunctionPointersOrExit();
    glEnable(GL_DEPTH_TEST);

    Shader *shader = createShader(vertexShaderPath, fragmentShaderPath);
    
    float vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    vec3 positions[] = {
        { 0.0f,  0.0f,  0.0f},
        { 2.0f,  5.0f, -15.0f},
        {-1.5f, -2.2f, -2.5f},
        {-3.8f, -2.0f, -12.3f},
        { 2.4f, -0.4f, -3.5f},
        {-1.7f,  3.0f, -7.5f},
        { 1.3f, -2.0f, -2.5f},
        { 1.5f,  2.0f, -2.5f},
        { 1.5f,  0.2f, -1.5f},
        {-1.3f,  1.0f, -1.5f}
    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // load and create a texture
    // -------------------------
    unsigned int texture1, texture2;

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);  // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // load image, create texture and generate mipmaps
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load(containerTexturePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        perror("Failed to load texture.");
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    stbi_set_flip_vertically_on_load(true);
    data = stbi_load(awesomefaceTextureFilePath, &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        perror("Failed to load texture.");
        exit(EXIT_FAILURE);
    }
    stbi_image_free(data);

    shader->use();
    shader->setUniformInt("texture1", 0);
    shader->setUniformInt("texture2", 1);

    mat4 projection;
    glm_mat4_identity(projection);
    unsigned int projectionLoc = glGetUniformLocation(shader->id, "projection");

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouseCallback);
    glfwSetScrollCallback(window, scrollCallback);

    while (!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processCamaraInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // bind textures on corresponding texture units
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        shader->use();

        // create transformations
        mat4 view;
        glm_mat4_identity(view);
        unsigned int viewLoc = glGetUniformLocation(shader->id, "view");
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)projection);

        // camara/view
        float radius = 10.0f;
        vec3 center;
        glm_vec3_add(camaraPos, camaraFront, center);
        glm_lookat(camaraPos, center, camaraUp, view);
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, (float *)view);
        glm_perspective(glm_rad(fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f, projection);
        glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, (float *)projection);

        // render container
        glBindVertexArray(VAO);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        for (unsigned int i = 0; i < 10; i++) {
            // calculate the model matrix for each object and pass it to the shader before drawing
            mat4 model;
            glm_mat4_identity(model);
            glm_translate(model, positions[i]);
            float angle = (float)glfwGetTime() * 20.0f * (i + 1);
            glm_rotate(model, glm_rad(angle), (vec3){1.0f, 0.3f, 0.5f});
            unsigned int modelLoc = glGetUniformLocation(shader->id, "model");
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, (float *)model);

            glDrawArrays(GL_TRIANGLES, 0, 36);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);

    shader->delete();
    
    glfwTerminate();
    return 0;
}

void processCamaraInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    const float camaraSpeed = 2.5f * deltaTime;
    vec3 newPos;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        glm_vec3_scale(camaraFront, camaraSpeed, newPos);
        glm_vec3_add(camaraPos, newPos, camaraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        glm_vec3_scale(camaraFront, camaraSpeed, newPos);
        glm_vec3_sub(camaraPos, newPos, camaraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        glm_vec3_crossn(camaraFront, camaraUp, newPos);
        glm_vec3_scale(newPos, camaraSpeed, newPos);
        glm_vec3_sub(camaraPos, newPos, camaraPos);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        glm_vec3_crossn(camaraFront, camaraUp, newPos);
        glm_vec3_scale(newPos, camaraSpeed, newPos);
        glm_vec3_add(camaraPos, newPos, camaraPos);
    }
}

void mouseCallback(GLFWwindow *window, double xpos, double ypos) {
    if (isFirstMouse) {
        lastX = xpos;
        lastY = ypos;
        isFirstMouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    vec3 direction;
    direction[0] = cosf(glm_rad(yaw)) * cosf(glm_rad(pitch));   // x component
    direction[1] = sinf(glm_rad(pitch));    // y component
    direction[2] = sinf(glm_rad(yaw)) * cosf(glm_rad(pitch));   // z component

    glm_vec3_normalize_to(direction, camaraFront);
}


void scrollCallback(GLFWwindow *window, double xoffset, double yoffset) {
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}