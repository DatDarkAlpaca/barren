#pragma once
#include <cglm/cglm.h>

typedef struct camera
{
    mat4 projection;
    mat4 view;
    vec3 position;
    vec3 target;
    vec3 up;
} camera;

void camera_initialize(camera* camera);
void camera_initialize_non_default(camera* camera, vec3 position, vec3 target, vec3 up);

void camera_set_position(camera* camera, vec3 position);
void camera_set_target(camera* camera, vec3 target);
void camera_update_view(camera* camera);

void camera_set_orthographic(camera* camera, float left, float right, float bottom, float top, float nearVal, float farVal);
void camera_set_perspective(camera* camera, float fovy, float aspect, float nearVal, float farVal);