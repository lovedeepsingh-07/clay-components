#define CLAY_IMPLEMENTATION
#include "layout_components.hpp"
#include "layout_engine.hpp"
#include "utils.hpp"
#include <array>
#include <clay_raylib.hpp>

int main() {
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
    std::array<Font, 1> font_list;
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
            && IsKeyPressed(KEY_K)) {
            Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
        }
        // theme
        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
            && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            && IsKeyPressed(KEY_L)) {
            if (layout_engine.get_curr_theme() == "dark") {
                layout_engine.set_theme("light");
            } else {
                layout_engine.set_theme("dark");
            }
        }

        Clay_BeginLayout();
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("container"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                        .childGap = 16

            } }) {
            if (layout_components::button("button", layout_engine)) {
                printf("button clicked!\n");
            }
            layout_components::checkbox("checkbox", layout_engine);
            layout_components::input("input", layout_engine);
            layout_components::tooltip("tooltip", layout_engine);
            layout_components::dropdown("dropdown", layout_engine);
            layout_components::modal("modal", layout_engine);
        }
        Clay_RenderCommandArray renderCommands = Clay_EndLayout();

        BeginDrawing();
        ClearBackground(layout_engine.get_color("background"));
        Clay_Raylib_Render(renderCommands, font_list.data());
        EndDrawing();
    }
    return 0;
}
