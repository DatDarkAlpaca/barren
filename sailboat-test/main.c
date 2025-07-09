#include <sailboat.h>
#include "main_view.h"

static void initialize_global(engine* engine)
{
    // Window:
    {
        window_set_title(&engine->context.windowingSystem, "Sailboat Test");
    }

    // Graphics & Renderer:
    {
        camera camera;
        camera_initialize(&camera);
        camera_set_orthographic(&camera, 0.0f, 640.0f, 480.0f, 0.f, -1.0f, 1.0f);
        
        quad_renderer_set_camera(&engine->context.quadRenderer, camera);
        graphics_set_clear_color(0.2f, 0.2f, 0.2f, 1.0f);
    }
}

static bool on_window_close_clbk(event _, void* args)
{
    engine* e = (engine*)args;
    printf("Window closing. Last delta time: %f\n", e->context.frameDeltaTime);
    return false;
}

static bool on_window_resize(event event, void* args)
{
    engine* e = (engine*)args;
    int* sizes = (int*)event.data;
    printf("Window resize: %d, %d\n", sizes[0], sizes[1]);
    return true;
}

static void on_event(engine* engine, event event)
{
    notifier notifier = { .event = &event };
    notifier_notify(&notifier, EVT_WINDOW_CLOSE, on_window_close_clbk, engine);
    notifier_notify(&notifier, EVT_WINDOW_RESIZE, on_window_resize, engine);
}

int main()
{
    engine engine = { 0 };
    {
        // Manual parameter setting:
        {
            engine_parameters parameters = { 
                .windowWidth = 640,
                .windowHeight = 480,
                .windowTitle = "Sailboat v0.1",
                .minimumFrameTime = 1.0 / 60.0
            };
            // engine_set_parameters(&parameters);  
        }
        
        engine_set_initialize_callback(&engine, initialize_global);
        // engine_set_update_callback(&engine, update_global);
        engine_set_event_callback(&engine, on_event);

        engine_initialize(&engine);
    }

    view* mainView = engine_add_view(&engine);
    mainView->engineInitCallback = main_view_initialize;
    
    engine_run(&engine);
    return 0;
}