#include "layout_components.hpp"
#include "utils.hpp"

bool layout_components::button(const std::string& id, const std::string& text, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId button_id = CLAY_SID(id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Button>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Button>(id);
    bool button_clicked = false;

    // button state configuration
    bool hovering = Clay_PointerOver(button_id);
    if (hovering && !ctx->hovered) {
        ctx->hovered = true;
    }
    if (!hovering && ctx->hovered) {
        ctx->hovered = false;
    }
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ctx->pressed = true;
    }
    if (hovering && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ctx->pressed) {
        button_clicked = true;
    }
    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ctx->pressed) {
        ctx->pressed = false;
    }

    // color values
    Color button_background_color =
        Fade(layout_engine.get_color("primary"), (float)((ctx->hovered || ctx->pressed) ? 0.85 : 1));
    Color button_foreground_color = layout_engine.get_color("primary-foreground");
    Color button_border_color =
        ColorAlpha(layout_engine.get_color("border"), (float)((ctx->hovered || ctx->pressed) ? 0.85 : 1));

    CLAY(Clay_ElementDeclaration{
        .id = button_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(20) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(button_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
        .border = { .color = app_utils::raylib_to_clay(button_border_color),
                    .width = { 1, 1, 1, 1, 0 } } }) {
        Clay_String button_text_cs = layout_engine.frame_arena.alloc_clay_string(text);
        CLAY_TEXT(
            button_text_cs,
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(button_foreground_color),
                .fontId = 0,
                .fontSize = 24,
            })
        );
    };
    return button_clicked;
}
