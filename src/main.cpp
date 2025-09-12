#include "clay_raylib.hpp"
#include "clayman.hpp"
#include "ui_engine.hpp"
#include "utils.hpp"

int main() {
    std::array<Font, 1> font_list;
    ClayMan clay(1280, 720, Raylib_MeasureText, font_list.data());

    Clay_Raylib_Initialize(clay.getWindowWidth(), clay.getWindowHeight(), "basement", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(90);

    // font_list[0] =
    //     LoadFontEx("../../deps/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, nullptr, 300);
    font_list[0] = GetFontDefault();
    // SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);

    auto UI_engine = UIEngine::UIEngine{};
    UI_engine.setup();
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
                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            } });
        {
            if (UIEngine::elements::button(clay, UI_engine, "theme_button", [&]() {
                    // auto* button_ctx =
                    //     UI_engine.get_element<UIEngine::element_context::Button>("theme_button");
                    clay.textElement(
                        "toggle",
                        Clay_TextElementConfig{
                            .textColor = game_utils::raylib_to_clay(UI_engine.get_color("primary_foreground")),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                })) {
                if (UI_engine.get_curr_theme() == "dark") {
                    UI_engine.set_theme("light");
                } else {
                    UI_engine.set_theme("dark");
                }
            }
            UIEngine::elements::dropdown(clay, UI_engine, "main_dropdown", [&]() {
                clay.element(Clay_ElementDeclaration{}, [&]() {
                    clay.textElement(
                        "Dropdown Children 1",
                        Clay_TextElementConfig{
                            .textColor = game_utils::raylib_to_clay(UI_engine.get_color("card_foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        }
                    );
                });
                clay.element(Clay_ElementDeclaration{}, [&]() {
                    clay.textElement(
                        "Dropdown Children 2",
                        Clay_TextElementConfig{
                            .textColor = game_utils::raylib_to_clay(UI_engine.get_color("card_foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        }
                    );
                });
            });
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
