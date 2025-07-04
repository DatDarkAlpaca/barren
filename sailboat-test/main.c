#include <sailboat.h>
#include <stdio.h>

typedef struct scene
{
    quad_renderer_data quad0;
} scene;

static scene mainScene;

static void initialize(engine* engine)
{
    // Graphics:
    graphics_set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);

    // Quad:
    transform transform;
    {
        transform_initialize(&mainScene.quad0.transform);
        
        vec3 scale = { 150.f, 150.f, 1.f};
        transform_set_position(&mainScene.quad0.transform, scale);
        transform_set_scale(&mainScene.quad0.transform, scale);
       
        quad_renderer_add_data(&engine->context.quadRenderer, &mainScene.quad0); 
    }

    camera_set_orthographic(&engine->context.quadRenderer.camera, 0.0f, 640.0f, 480.0f, 0.f, -1.0f, 1.0f);
}

static void update(engine* engine, f64 deltaTime)
{    
    quad_renderer_begin_render(&engine->context.quadRenderer, 0);

    quad_renderer_render(&engine->context.quadRenderer);

    quad_renderer_end_render(&engine->context.quadRenderer);
}

int main()
{
    engine engine = { 0 };
    {
        engine_parameters parameters = { 
            .windowWidth = 640,
            .windowHeight = 480,
            .windowTitle = "Sailboat v0.1",
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