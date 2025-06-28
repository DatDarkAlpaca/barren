#include <barren.h>
#include <stdio.h>

typedef struct scene
{
    quad_renderer_data quad0;
} scene;

static scene mainScene;

static void initialize(engine* engine)
{
    vec4 position;
    vec3 scale;
    {
        scale[0] = 100.f;
        scale[1] = 100.f;
        scale[2] = 1.f;    
    }
    
    glm_mat4_identity(mainScene.quad0.transform.data);
    glm_translate(mainScene.quad0.transform.data, position);
    glm_scale(mainScene.quad0.transform.data, scale);

    quad_renderer_add_data(&engine->context.quadRenderer, &mainScene.quad0);
}

static void update(engine* engine, f64 deltaTime)
{    
    quad_renderer_begin_render(&engine->context.quadRenderer, 0);
    graphics_set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);

    quad_renderer_end_render(&engine->context.quadRenderer);
}

int main()
{
    engine engine = { 0 };
    {
        engine_parameters parameters = { 
            .windowWidth = 640,
            .windowHeight = 480,
            .windowTitle = "Barren v0.1",
            .minimumFrameTime = 1.0 / 60.0
        };
        engine_set_parameters(&parameters);

        engine_set_initialize_callback(&engine, initialize);
        engine_set_update_callback(&engine, update);

        u64 result = engine_initialize(&engine);
        if(result)
            return result;
    }
    
    engine_run(&engine);
    return 0;
}