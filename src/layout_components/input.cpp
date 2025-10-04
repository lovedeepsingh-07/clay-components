#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::input(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId input_id = CLAY_SID(id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Input>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Input>(id);

    // input state configuration
    bool hovering = Clay_PointerOver(input_id);
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ctx->focused) {
        ctx->focused = true;
    }
    if (!hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ctx->focused) {
        ctx->focused = false;
    }

    // handlinng input value
    if (ctx->focused) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                ctx->value.push_back((char)key);
            }
            key = GetCharPressed();
        }
        if ((IsKeyPressed(KEY_BACKSPACE)) && !ctx->value.empty()) {
            ctx->value.pop_back();
        }
        if (IsKeyPressed(KEY_BACKSPACE)
            && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            ctx->value.clear();
        }
    }
    Clay_String input_value_cs = layout_engine.frame_arena.alloc_clay_string(ctx->value);

    // color values
    Color input_background_color =
        layout_engine.get_color(ctx->focused ? "card" : "background");
    Color input_placeholder_color = layout_engine.get_color("muted-foreground");
    Color input_foreground_color = layout_engine.get_color("foreground");
    Color input_border_color = layout_engine.get_color("border");
    auto input_border_width = ctx->focused ? Clay_BorderWidth{ 3, 3, 3, 3, 0 }
                                           : Clay_BorderWidth{ 1, 1, 1, 1, 0 };

    CLAY(Clay_ElementDeclaration{
        .id = input_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(160), .height = CLAY_SIZING_FIT(37) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(input_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
        .border = { .color = app_utils::raylib_to_clay(input_border_color),
                    .width = input_border_width } }) {
        if (ctx->value.empty() && !ctx->focused) {
            CLAY_TEXT(
                CLAY_STRING("Input"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(input_placeholder_color),
                    .fontId = 0,
                    .fontSize = 25,
                })
            );
        }
        if (!ctx->value.empty()) {
            CLAY_TEXT(
                input_value_cs,
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(input_foreground_color),
                    .fontId = 0,
                    .fontSize = 25,
                })
            );
        }
    }
}
