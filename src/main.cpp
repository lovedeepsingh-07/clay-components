#include "clay_raylib.hpp"
#include "demo.hpp"

int main() {
    // font setup
    std::array<Font, 1> font_list;
    ClayMan clay(1280, 720, Raylib_MeasureText, font_list.data());

    // raylib window
    Clay_Raylib_Initialize(clay.getWindowWidth(), clay.getWindowHeight(), "clay-components", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(90);

    font_list[0] =
        LoadFontEx("../deps/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, nullptr, 300);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);

    // layout engine setup
    auto layout_engine = LayoutEngine::LayoutEngine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta = GetMouseWheelMoveV();
        clay.updateClayState(
            GetScreenWidth(), GetScreenHeight(), mouse_pos.x, mouse_pos.y,
            scroll_delta.x, scroll_delta.y, GetFrameTime(), IsMouseButtonDown(0)
        );

        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
            && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            && IsKeyPressed(KEY_I)) {
            Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
        }
        if ((IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))
            && (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT))
            && IsKeyPressed(KEY_O)) {
            if (layout_engine.get_curr_theme() == "dark") {
                layout_engine.set_theme("light");
            } else {
                layout_engine.set_theme("dark");
            }
        }

        clay.beginLayout();
        clay.openElement(Clay_ElementDeclaration{
            .id = clay.hashID("MAIN_CONTAINER"),
            .layout = {
                .sizing = { CLAY_SIZING_GROW(), CLAY_SIZING_GROW() },
                .padding = CLAY_PADDING_ALL(4),
                .childGap = 2,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            } });
        {
            // demo::button(clay, layout_engine);
            // demo::input(clay, layout_engine);
            // demo::checkbox(clay, layout_engine);
            // demo::dropdown(clay, layout_engine);
            demo::tabs(clay, layout_engine);
        }
        clay.closeElement();

        Clay_RenderCommandArray render_commands = clay.endLayout();
        BeginDrawing();
        ClearBackground(layout_engine.get_color("background"));

        Clay_Raylib_Render(render_commands, font_list.data());

        EndDrawing();
    }
    return 0;
}
