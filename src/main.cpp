#define CLAY_IMPLEMENTATION
#include "dashboard.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"
#include <array>
#include <clay_raylib.hpp>

int main() {
    SetTraceLogLevel(LOG_NONE); // disable logging
    // window setup
    Clay_Raylib_Initialize(1280, 720, "clay-components", FLAG_WINDOW_RESIZABLE);

    // clay setup
    uint64_t clay_required_memory = Clay_MinMemorySize();
    Clay_Arena clay_memory =
        Clay_CreateArenaWithCapacityAndMemory(clay_required_memory, malloc(clay_required_memory));
    Clay_Initialize(
        clay_memory,
        (Clay_Dimensions){ .width = (float)GetScreenWidth(),
                           .height = (float)GetScreenHeight() },
        (Clay_ErrorHandler){ app_utils::handle_clay_errors }
    );

    // font setup
    std::array<Font, 2> font_list;
    font_list[0] =
        LoadFontEx("./assets/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, NULL, 400);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, font_list.data());

    // layout engine
    LayoutEngine::LayoutEngine layout_engine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        // clear the frame memory arena at the starting of every frame
        layout_engine.frame_arena.clear();
        // window state
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta =
            Vector2Scale(GetMouseWheelMoveV(), 2); // scroll delta scaled 2 times
        float delta_time = GetFrameTime();

        // update clay state
        Clay_SetLayoutDimensions((Clay_Dimensions){ (float)GetScreenWidth(),
                                                    (float)GetScreenHeight() });
        Clay_SetPointerState((Clay_Vector2){ mouse_pos.x, mouse_pos.y }, IsMouseButtonDown(0));
        Clay_UpdateScrollContainers(
            true, (Clay_Vector2){ scroll_delta.x, scroll_delta.y }, delta_time
        );

        Clay_BeginLayout();
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("main_container"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            layout_components::context_menu("main_context_menu", layout_engine);
            dashboard::dashboard(layout_engine);
        }
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(layout_engine.get_color("background"));
        Clay_Raylib_Render(renderCommands, font_list.data());
        EndDrawing();
    }
    return 0;
}
