#include "camera.h"

void camera_initialize(camera *camera)
{
    glm_vec3_zero(camera->position);
    glm_vec3_zero(camera->target);
    
    vec3 up = { 0.0f, 1.0f, 0.0f };
    glm_vec3_copy(up, camera->up);

    glm_mat4_identity(camera->projection);
    glm_mat4_identity(camera->view);
}
void camera_initialize_non_default(camera *camera, vec3 position, vec3 target, vec3 up)
{
    glm_vec3_copy(position, camera->position);
    glm_vec3_copy(target, camera->target);
    glm_vec3_copy(up, camera->up);

    glm_mat4_identity(camera->projection);
    glm_mat4_identity(camera->view);
}

void camera_set_position(camera *camera, vec3 position)
{
    glm_vec2_copy(position, camera->position);
}
void camera_set_target(camera *camera, vec3 target)
{
    glm_vec2_copy(target, camera->target);
}
void camera_update_view(camera *camera)
{
    glm_lookat(camera->position, camera->target, camera->up, camera->view);
}

void camera_set_orthographic(camera *camera, float left, float right, float bottom, float top, float nearVal, float farVal)
{
    glm_ortho(left, right, bottom, top, nearVal, farVal, camera->projection);
}
void camera_set_perspective(camera *camera, float fovy, float aspect, float nearVal, float farVal)
{
    glm_perspective(fovy, aspect, nearVal, farVal, camera->projection);
}
