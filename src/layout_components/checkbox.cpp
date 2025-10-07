#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::checkbox(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId checkbox_id = CLAY_SID(id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Checkbox>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Checkbox>(id);

    // checkbox state configuration
    bool hovering = Clay_PointerOver(checkbox_id);
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ctx->checked = !ctx->checked;
    }

    // color values
    Color checkbox_background_color =
        layout_engine.get_color(ctx->checked ? "foreground" : "background");
    Color checkbox_foreground_color = layout_engine.get_color("background");
    Color button_border_color = layout_engine.get_color("border");

    CLAY(Clay_ElementDeclaration{
        .id = checkbox_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(24), .height = CLAY_SIZING_FIT(24) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(checkbox_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
        .border = { .color = app_utils::raylib_to_clay(button_border_color),
                    .width = { 1, 1, 1, 1, 0 } } }) {
        if (ctx->checked) {
            CLAY_TEXT(
                CLAY_STRING("*"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(checkbox_foreground_color),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
        }
    }
}
