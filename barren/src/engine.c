#include "engine.h"
#include "window.h"
#include "bare-graphics/graphics.h"

#include <stdio.h>

static engine_parameters __parameters;

void engine_set_parameters(const engine_parameters *parameters)
{
    __parameters = *parameters;
}
u64 engine_initialize(engine *engine)
{
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
    return SUCCESS;
}

void engine_set_initialize_callback(engine* engine, engine_callback callback)
{
    engine->initializeCallback = callback;
}
void engine_set_update_callback(engine *engine, engine_update_callback callback)
{
    engine->updateCallback = callback;
}

void engine_run(engine *engine)
{
    engine->initializeCallback(engine);

    f64 previousTime = glfwGetTime();
    f64 currentTime = previousTime;
    f64 previousFrameTime = previousTime;
    f64 accumulatedTime = 0;
    f64 deltaTime = 0;
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
            engine->updateCallback(engine, frameDeltaTime);
            graphics_present(engine->context.window);
        }
    }
}
