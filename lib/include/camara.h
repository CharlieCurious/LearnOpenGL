#include <cglm/cglm.h>
#include <glad/glad.h>

// Default camara values
#define YAW -90.0f
#define PITCH 0.0f
#define SPEED 2.5f
#define SENSITIVITY 0.1f
#define ZOOM 45.0f

typedef enum {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} CamaraMovement;

typedef struct {
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;
    float Yaw;
    float Pitch;
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
} Camara;

Camara *initCamara(vec3 position, vec3 up, float yaw, float pitch);

void getViewMatrix(Camara *camara, mat4 dstView);

void processKeyboard(Camara *camara, CamaraMovement direction, float deltaTime);

void processMouseMovement(Camara *camara, float xoffset, float yoffset, GLboolean constrainPitch); 

void processMouseScroll(Camara *camara, float yoffset);


