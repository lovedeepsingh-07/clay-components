#include "clay_raylib.hpp"
#include "clayman.hpp"
#include "ui_engine.hpp"

int main() {
    std::array<Font, 1> font_list;
    ClayMan clay(1280, 720, Raylib_MeasureText, font_list.data());

    Clay_Raylib_Initialize(clay.getWindowWidth(), clay.getWindowHeight(), "clay-components", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(90);

    font_list[0] =
        LoadFontEx("../deps/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, nullptr, 300);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);

    auto UI_engine = UIEngine::UIEngine{};
    UI_engine.setup();
    // set default theme
    UI_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta = GetMouseWheelMoveV();
        clay.updateClayState(
            GetScreenWidth(), GetScreenHeight(), mouse_pos.x, mouse_pos.y,
            scroll_delta.x, scroll_delta.y, GetFrameTime(), IsMouseButtonDown(0)
        );

        clay.beginLayout();
        clay.openElement(Clay_ElementDeclaration{
            .id = clay.hashID("MAIN_CONTAINER"),
            .layout = {
                .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 16,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            } });
        {
            if (UIEngine::elements::button(clay, UI_engine, "debug_button", "debug")) {
                Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
            }
            if (UIEngine::elements::button(clay, UI_engine, "theme_button", "toggle")) {
                if (UI_engine.get_curr_theme() == "dark") {
                    UI_engine.set_theme("light");
                } else {
                    UI_engine.set_theme("dark");
                }
            }
        }
        clay.closeElement();

        Clay_RenderCommandArray render_commands = clay.endLayout();
        BeginDrawing();
        ClearBackground(UI_engine.get_color("background"));

        Clay_Raylib_Render(render_commands, font_list.data());

        EndDrawing();
    }
    return 0;
}
