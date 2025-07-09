#include <stdbool.h>

#include "engine.h"
#include "window.h"
#include "platform.h"
#include "graphics/texture.h"
#include "graphics/graphics.h"

// Parameters:
static engine_parameters __parameters;
static bool s_ArgumentsSet = false;
engine_parameters sail_DefaultParameters = {
    .windowWidth = 640,
    .windowHeight = 480,
    .windowTitle = "Sailboat v0.1",
    .minimumFrameTime = 1.0 / 60.0
};

void engine_set_parameters(const engine_parameters* parameters)
{
    s_ArgumentsSet = true;
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
void engine_initialize(engine* engine)
{
    assert(engine);

    // Platform:
    platform_initialize();

    // Arguments:
    if(!s_ArgumentsSet)
        __parameters = sail_DefaultParameters;

    // Timing:
    engine->minimumFrameTime = __parameters.minimumFrameTime;

    // Windowing & Graphics:
    windowing_system_initialize();
    graphics_system_initialize();

    window_create(
        &engine->context.window,
        __parameters.windowWidth,
        __parameters.windowHeight,
        __parameters.windowTitle
    );
    
    graphics_system_late_initialize();

    // Ephemeral:
    ephemeral_initialize(&engine->context.ephemeralSystem, 100);

    // Quad Renderer:
    quad_renderer_initialize(&engine->context.quadRenderer, 32000);

    // Views (TODO: set config for max views):
    view_holder_initialize(&engine->context.viewHolder, 16);
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

gl_handle engine_create_texture(context* context, const char *filepath, u64 channelAmount)
{
    // Wrapper function to handle loading and graphics object creation
    asset_texture_handle assetHandle = ephemeral_imm_load_texture(&context->ephemeralSystem, "res/quad.jpg");
    asset_texture* asset = ephemeral_get_texture(&context->ephemeralSystem, assetHandle);
    if(!asset)
    {
        SAIL_LOG_ERROR("Failed to load texture");
        return invalid_handle;
    }
        
    texture_args args = { 0 };
    {
        args.width = asset->width;
        args.height = asset->height;
        args.format = TEXTURE_FORMAT_RGB8_UNORM;
        args.type = TEXTURE_TYPE_2D;
    }

    gl_handle texture = graphics_create_texture(&args);
    if(texture == invalid_handle)
    {
        SAIL_LOG_ERROR("Failed to create texture");
        return invalid_handle;
    }
       
    graphics_update_texture(texture, TEXTURE_TYPE_2D, asset);
    return texture;
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
                engine->context.frameDeltaTime = frameDeltaTime;

                if(engine->updateCallback)
                    engine->updateCallback(engine, frameDeltaTime);

                on_engine_update(engine, frameDeltaTime);
            }

            graphics_present(engine->context.window);
        }
    }
}
