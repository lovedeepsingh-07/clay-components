#include "clay_raylib.hpp"
#include "clayman.hpp"
#include "layout_components.hpp"
#include "utils.hpp"
#include <iostream>

int main() {
    std::array<Font, 1> font_list;
    ClayMan clay(1280, 720, Raylib_MeasureText, font_list.data());

    Clay_Raylib_Initialize(clay.getWindowWidth(), clay.getWindowHeight(), "clay-components", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(90);

    font_list[0] =
        LoadFontEx("../deps/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, nullptr, 300);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);

    auto layout_engine = LayoutEngine::LayoutEngine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    std::string input_default_text = "";
    std::string input_custom_text = "";

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
                .sizing = { CLAY_SIZING_FIT(0), CLAY_SIZING_FIT(0) },
                .padding = CLAY_PADDING_ALL(4),
                .childGap = 2,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            } });
        {
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("DEMO_ACTION_BUTTON_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                if (layout_components::button()
                        .clay_man(clay)
                        .engine(layout_engine)
                        .id("theme_button")
                        .variant("primary")
                        .text("theme")
                        .build()) {
                    if (layout_engine.get_curr_theme() == "dark") {
                        layout_engine.set_theme("light");
                    } else {
                        layout_engine.set_theme("dark");
                    }
                }
                if (layout_components::button()
                        .clay_man(clay)
                        .engine(layout_engine)
                        .id("debug_button")
                        .variant("primary")
                        .text("debug")
                        .build()) {
                    Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
                }
            }
            clay.closeElement();
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("BUTTONS_DEMO_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_primary")
                    .variant("primary")
                    .text("primary")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_secondary")
                    .variant("secondary")
                    .text("secondary")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_muted")
                    .variant("muted")
                    .text("muted")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_accent")
                    .variant("accent")
                    .text("accent")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_destructive")
                    .variant("destructive")
                    .text("destructive")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_custom")
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                                .height = CLAY_SIZING_FIT(20) },
                                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .backgroundColor = app_utils::raylib_to_clay(MAROON),
                        .cornerRadius = CLAY_CORNER_RADIUS(0),
                    })
                    .build();
                {
                    clay.textElement(
                        "custom text",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(YELLOW),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }
                layout_components::close_button(clay);
            }
            clay.closeElement();

            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("INPUT_DEMO_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                layout_components::input()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_input_default")
                    .placeholder("input_box")
                    .value(input_default_text)
                    .build();
                clay.textElement(
                    "input_default_text: " + input_default_text,
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
                layout_components::input()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_input_custom")
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_FIT(160),
                                                .height = CLAY_SIZING_FIT(37) },
                                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .backgroundColor = app_utils::raylib_to_clay(MAROON),
                        .cornerRadius = CLAY_CORNER_RADIUS(0),
                        .border = { .color = app_utils::raylib_to_clay(YELLOW),
                                    .width = Clay_BorderWidth{ 1, 1, 1, 1, 0 } } })
                    .placeholder("custom_input")
                    .value(input_custom_text)
                    .build();
                auto* input_custom_ctx =
                    layout_engine.get_element<LayoutEngine::component_context::Input>("demo_input_custom");
                clay.textElement(
                    "input_custom_text: " + input_custom_ctx->value,
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
            }
            clay.closeElement();
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
