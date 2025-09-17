#include "clay_raylib.hpp"
#include "clayman.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

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
            // action buttons
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
                // theme button
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
                // debug button
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
            // button demo container
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
                // primary button
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_primary")
                    .variant("primary")
                    .text("primary")
                    .build();
                // secondary button
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_secondary")
                    .variant("secondary")
                    .text("secondary")
                    .build();
                // muted button
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_muted")
                    .variant("muted")
                    .text("muted")
                    .build();
                // accent button
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_accent")
                    .variant("accent")
                    .text("accent")
                    .build();
                // destructive button
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_destructive")
                    .variant("destructive")
                    .text("destructive")
                    .build();
                // custom button
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
                        .border = { .color = app_utils::raylib_to_clay(PURPLE),
                                    .width = { 2, 2, 2, 2, 0 } } })
                    .build();
                {
                    clay.textElement(
                        "custom",
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

            // input demo container
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
                // default input
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
                // custom input
                auto* custom_input_ctx =
                    layout_engine.get_element<LayoutEngine::component_context::Input>("demo_input_custom");
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
                        .border = { .color = app_utils::raylib_to_clay(PURPLE),
                                    .width =
                                        (custom_input_ctx != nullptr
                                                 && custom_input_ctx->focused
                                             ? Clay_BorderWidth{ 4, 4, 4, 4, 0 }
                                             : Clay_BorderWidth{ 2, 2, 2, 2, 0 }) } })
                    .placeholder("custom_input")
                    .value(input_custom_text)
                    .build();
                clay.textElement(
                    "input_custom_text: "
                        + (custom_input_ctx == nullptr ? "" : custom_input_ctx->value),
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
            }
            clay.closeElement();
            // checkbox demo container
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("CHECKBOX_DEMO_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                // default checkbox
                layout_components::checkbox()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_checkbox_default")
                    .build();
                auto* checkbox_default_ctx =
                    layout_engine.get_element<LayoutEngine::component_context::Checkbox>("demo_checkbox_default"
                    );
                clay.textElement(
                    "default_checkbox: "
                        + std::string(
                            (checkbox_default_ctx != nullptr
                             && checkbox_default_ctx->checked)
                                ? "checked"
                                : "not_checked"
                        ),
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
                // custom checkbox
                auto* custom_checkbox_ctx =
                    layout_engine.get_element<LayoutEngine::component_context::Checkbox>("demo_checkbox_custom"
                    );
                layout_components::checkbox()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_checkbox_custom")
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_FIT(24),
                                                .height = CLAY_SIZING_FIT(24) },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .backgroundColor = app_utils::raylib_to_clay(
                            (custom_checkbox_ctx != nullptr
                             && custom_checkbox_ctx->checked)
                                ? PURPLE
                                : MAROON
                        ),
                        .cornerRadius = CLAY_CORNER_RADIUS(0),
                        .border = { .color = app_utils::raylib_to_clay(
                                        (custom_checkbox_ctx != nullptr
                                         && custom_checkbox_ctx->checked)
                                            ? MAROON
                                            : PURPLE
                                    ),
                                    .width =
                                        (custom_checkbox_ctx != nullptr
                                                 && custom_checkbox_ctx->checked
                                             ? Clay_BorderWidth{ 4, 4, 4, 4, 0 }
                                             : Clay_BorderWidth{ 2, 2, 2, 2, 0 }) } })
                    .build();
                clay.textElement(
                    "custom_checkbox: "
                        + std::string(
                            (custom_checkbox_ctx != nullptr
                             && custom_checkbox_ctx->checked)
                                ? "checked"
                                : "not_checked"
                        ),
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
            }
            clay.closeElement();
            // dropdown demo container
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("DROPDOWN_DEMO_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                // default dropdown
                layout_components::dropdown()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_dropdown_default")
                    .build();
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
