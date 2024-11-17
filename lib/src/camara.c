#include <camara.h>
#include <stdlib.h>

static void updateCamaraVectors(Camara *camara);

Camara *initCamara(vec3 position, vec3 up, float yaw, float pitch) {
    Camara *camara = (Camara *)malloc(sizeof(Camara));
    if (camara == NULL) return NULL;

    glm_vec3_copy(position, camara->Position);
    glm_vec3_copy(up, camara->Up);

    camara->Yaw = YAW;
    camara->Pitch = PITCH;
    camara->MovementSpeed = SPEED;
    camara->MouseSensitivity = SENSITIVITY;
    camara->Zoom = ZOOM;

    vec3 front = {0.0f, 0.0f, -1.0f};
}

void getViewMatrix(Camara *camara, mat4 dstView) {
    vec3 target;
    glm_vec3_add(camara->Position, camara->Front, target);
    glm_lookat(camara->Position, target, camara->Up, dstView);
}

void processKeyboard(Camara *camara, CamaraMovement direction, float deltaTime) {
    float velocity = camara->MovementSpeed * deltaTime;
    vec3 newPos;
    if (direction == FORWARD) {
        glm_vec3_scale(camara->Front, velocity, newPos);
        glm_vec3_add(camara->Position, newPos, camara->Position);
    }
    if (direction == BACKWARD) {
        glm_vec3_scale(camara->Front, velocity, newPos);
        glm_vec3_sub(camara->Position, newPos, camara->Position);
    }
    if (direction == LEFT) {
        glm_vec3_crossn(camara->Front, camara->Up, newPos);
        glm_vec3_scale(newPos, velocity, newPos);
        glm_vec3_sub(camara->Position, newPos, camara->Position);
    }
    if (direction == RIGHT) {
        glm_vec3_crossn(camara->Front, camara->Up, newPos);
        glm_vec3_scale(newPos, velocity, newPos);
        glm_vec3_add(camara->Position, newPos, camara->Position);
    }
}

void processMouseMovement(Camara *camara, float xoffset, float yoffset, GLboolean constrainPitch) {
    xoffset *= camara->MouseSensitivity;
    yoffset *= camara->MouseSensitivity;

    camara->Yaw += xoffset;
    camara->Pitch += yoffset;

    if (constrainPitch) {
        if (camara->Pitch > 89.0f)
            camara->Pitch = 89.0f;
        if (camara->Pitch < -89.0f)
            camara->Pitch -89.0f;
    }

    updateCamaraVectors(camara);
}

void processMouseScroll(Camara *camara, float yoffset) {
    camara->Zoom -= yoffset;
    if (camara->Zoom < 1.0f)
        camara->Zoom = 1.0f;
    if (camara->Zoom > 45.0f)
        camara->Zoom = 45.0f;
}

static void updateCamaraVectors(Camara *camara) {
    // calculate the new Front vector
    vec3 front;
    front[0] = cosf(glm_rad(camara->Yaw)) * cosf(glm_rad(camara->Pitch));
    front[1] = sinf(glm_rad(camara->Pitch));
    front[2] = sinf(glm_rad(camara->Yaw)) * cosf(glm_rad(camara->Pitch));
    glm_vec3_normalize_to(front, camara->Front);

    // also re-calculate the Right and Up vector
    glm_vec3_crossn(camara->Front, camara->WorldUp, camara->Right);
    glm_vec3_crossn(camara->Right, camara->Front, camara->Up);
}
