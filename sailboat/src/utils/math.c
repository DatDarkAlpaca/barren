#include <stdbool.h>
#include "math.h"

void transform_initialize(transform *transform)
{
    glm_vec3_one(transform->scale);
    glm_vec3_zero(transform->position);
    glm_vec3_zero(transform->rotation);
}
void transform_set_position(transform *transform, vec3 position)
{
    glm_vec3_copy(position, transform->position);
}
void transform_set_rotation(transform *transform, vec3 rotation)
{
    glm_vec3_copy(rotation, transform->rotation);
}
void transform_set_scale(transform *transform, vec3 scale)
{
    glm_vec3_copy(scale, transform->scale);
}
void update_transform_data(transform *transform)
{
    mat4 model;
    glm_mat4_identity(model);
    glm_translate(model, transform->position);

    {
        // TODO: test
        // versor quaternion;
        // glm_euler_xyz_quat(transform->rotation, quaternion);
        // glm_mat4_mul(model, quaternion, model);
    }

    glm_scale(model, transform->scale);
    glm_mat4_copy(model, transform->data);
}

bool is_square_number(u64 number)
{
    return (number & (number - 1)) == 0;
}

u64 get_next_square_number(u64 number)
{
    return (number - (number >> 1)) << 1;
}
