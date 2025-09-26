#define CLAY_IMPLEMENTATION
#include "layout_engine.hpp"
#include "utils.hpp"
#include <clay_raylib.hpp>

int main() {
    // window setup
    Clay_Raylib_Initialize(1280, 720, "basement", FLAG_WINDOW_RESIZABLE);

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
    Font font_list[1];
    font_list[0] =
        LoadFontEx("../deps/fonts/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, NULL, 400);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);
    Clay_SetMeasureTextFunction(Raylib_MeasureText, font_list);

    // layout engine
    LayoutEngine::LayoutEngine layout_engine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        // window state
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta = GetMouseWheelMoveV();
        float delta_time = GetFrameTime();

        // update clay state
        Clay_SetLayoutDimensions((Clay_Dimensions){ (float)GetScreenWidth(),
                                                    (float)GetScreenHeight() });
        Clay_SetPointerState((Clay_Vector2){ mouse_pos.x, mouse_pos.y }, IsMouseButtonDown(0));
        Clay_UpdateScrollContainers(
            true, (Clay_Vector2){ scroll_delta.x, scroll_delta.y }, delta_time
        );

        // debug mode
        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
            && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            && IsKeyPressed(KEY_I)) {
            Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
        }
        // theme
        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
            && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            && IsKeyPressed(KEY_O)) {
            if (layout_engine.get_curr_theme() == "dark") {
                layout_engine.set_theme("light");
            } else {
                layout_engine.set_theme("dark");
            }
        }

        Clay_BeginLayout();
        CLAY_TEXT(
            CLAY_STRING("hello, world!"),
            CLAY_TEXT_CONFIG({
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                .fontId = 0,
                .fontSize = 25,
            })
        );
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(layout_engine.get_color("background"));
        Clay_Raylib_Render(renderCommands, font_list);
        EndDrawing();
    }
    return 0;
}
