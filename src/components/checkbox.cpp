#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::_checkbox_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Checkbox>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Checkbox>(_id);

    // checkbox state configuration
    bool hovering = _clay->pointerOver(_id);
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        ctx->checked = !ctx->checked;
    }

    // default color values
    Color checkbox_background_color =
        _engine->get_color(ctx->checked ? "foreground" : "background");
    Color checkbox_foreground_color = _engine->get_color("background");
    Color button_border_color = _engine->get_color("border");

    // default checkbox style
    auto checkbox_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(24), .height = CLAY_SIZING_FIT(24) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(checkbox_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color = app_utils::raylib_to_clay(button_border_color),
                    .width = { 1, 1, 1, 1, 0 } }
    };

    // apply custom styles
    if (_custom_styled) {
        checkbox_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            checkbox_style.backgroundColor = _style.backgroundColor;
        }
        checkbox_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            checkbox_style.border.color = _style.border.color;
        }
        checkbox_style.border.width = _style.border.width;
    }

    _clay->openElement(checkbox_style);
    {
        if (ctx->checked)
            // FIXME: when I am writing this note, I have no idea how to add a 'check' symbol into raylib so I am just using the '*' symbol as the check symbol
            _clay->textElement(
                "*",
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(checkbox_foreground_color),
                    .fontId = 0,
                    .fontSize = 24,
                }
            );
    }
    _clay->closeElement();
}
layout_components::_checkbox_builder layout_components::checkbox() {
    return _checkbox_builder{};
};
