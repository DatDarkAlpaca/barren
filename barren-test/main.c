#include <barren.h>
#include <stdio.h>

static void initialize(engine* engine)
{
    
}

static void update(engine* engine, f64 deltaTime)
{    
    quad_renderer_begin_render(&engine->context.quadRenderer, 0);

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