#include "engine.h"
#include "window.h"
#include "graphics/graphics.h"

// Parameters:
static engine_parameters __parameters;
void engine_set_parameters(const engine_parameters* parameters)
{
    __parameters = *parameters;
}

// View callbacks:
static void on_engine_initialize(engine* engine)
{
    for(u64 i = 0; i < engine->context.viewHolder.currentView; ++i)
    {
        view* view = view_holder_get(&engine->context.viewHolder, i);
        
        if(view->engineInitCallback)
            view->engineInitCallback(view);
    }
}

static void on_engine_update(engine* engine, u64 frameDeltaTime)
{
    for(u64 i = 0; i < engine->context.viewHolder.currentView; ++i)
    {
        view* view = view_holder_get(&engine->context.viewHolder, i);
        
        if(view->engineUpdateCallback)
            view->engineUpdateCallback(view, frameDeltaTime);

        ecs_progress(view->scene.ecs, 0);
    }
}

// Engine:
u64 engine_initialize(engine* engine)
{
    assert(engine);

    // Timing:
    engine->minimumFrameTime = __parameters.minimumFrameTime;

    // Windowing & Graphics:
    u64 windowingResult = windowing_system_initialize();
    u64 graphicsResult = graphics_system_initialize();
    {
        if(windowingResult)
            return windowingResult;

        if(graphicsResult)
            return graphicsResult;
        
        u64 windowResult = window_create(
            &engine->context.window,
            __parameters.windowWidth,
            __parameters.windowHeight,
            __parameters.windowTitle
        );
        if(windowResult)
            return windowResult;
    }

    graphics_system_late_initialize();

    // Quad Renderer:
    u64 quadRendererResult = quad_renderer_initialize(&engine->context.quadRenderer, 32000);
    if(quadRendererResult)
        return quadRendererResult;

    // Views (TODO: set config for max views):
    view_holder_initialize(&engine->context.viewHolder, 16);

    return SUCCESS;
}

void engine_set_initialize_callback(engine* engine, engine_callback callback)
{
    assert(engine);
    engine->initializeCallback = callback;
}
void engine_set_update_callback(engine* engine, engine_update_callback callback)
{
    assert(engine);
    engine->updateCallback = callback;
}

view *engine_add_view(engine *engine)
{
    view_handle handle = view_holder_add(&engine->context.viewHolder);
    view* view = view_holder_get(&engine->context.viewHolder, handle);

    scene_initialize(&view->scene, &engine->context);
    view->context = &engine->context;

    return view;
}

void engine_run(engine* engine)
{
    assert(engine);

    if(engine->initializeCallback)
        engine->initializeCallback(engine);

    on_engine_initialize(engine);

    f64 previousTime = glfwGetTime();
    f64 currentTime = previousTime;
    f64 previousFrameTime = previousTime;
    f64 accumulatedTime = 0, deltaTime = 0;
    while (!glfwWindowShouldClose(engine->context.window))
    {
        currentTime = glfwGetTime();
        deltaTime = currentTime - previousTime;
        previousTime = currentTime;
        accumulatedTime += deltaTime;

        if(accumulatedTime >= engine->minimumFrameTime)
        {
            f64 frameDeltaTime = currentTime - previousFrameTime;
            previousFrameTime = currentTime;
            accumulatedTime = 0;

            glfwPollEvents();

            {
                if(engine->updateCallback)
                    engine->updateCallback(engine, frameDeltaTime);

                on_engine_update(engine, frameDeltaTime);
            }

            graphics_present(engine->context.window);
        }
    }
}
