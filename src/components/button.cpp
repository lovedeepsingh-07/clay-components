#include "layout_components.hpp"
#include "utils.hpp"
#include <array>

layout_components::_button_builder&
layout_components::_button_builder::variant(const std::string& variant) {
    this->_variant = variant;
    return *this;
}
layout_components::_button_builder&
layout_components::_button_builder::style(Clay_ElementDeclaration style) {
    this->_custom_styled = true;
    this->_style = style;
    this->_style.id = this->_clay->hashID(this->_id);
    return *this;
}
layout_components::_button_builder&
layout_components::_button_builder::text(const std::string& text) {
    this->_text_button = true;
    this->_text = text;
    return *this;
}

bool layout_components::_button_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Button>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Button>(_id);
    bool button_clicked = false;

    // button state configuration
    bool hovering = _clay->pointerOver(_id);
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

    // button variant
    std::array<std::string, 5> accepted_variants = { "primary", "secondary", "muted",
                                                     "accent", "destructive" };
    std::string button_variant =
        (std::find(std::begin(accepted_variants), std::end(accepted_variants), _variant)
         != std::end(accepted_variants))
        ? _variant
        : "primary"; // if the variant is valid, the we take that or else, we default to primary

    // default color values
    Color button_background_color =
        ColorAlpha(_engine->get_color(button_variant), ((ctx->hovered || ctx->pressed) ? 0.85 : 1));
    Color button_foreground_color =
        _engine->get_color((_custom_styled ? "foreground" : button_variant + "-foreground"));
    Color button_border_color =
        ColorAlpha(_engine->get_color("border"), ((ctx->hovered || ctx->pressed) ? 0.85 : 1));

    // default button style
    auto button_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(20) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(button_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color = app_utils::raylib_to_clay(button_border_color),
                    .width = { 1, 1, 1, 1, 0 } }
    };

    // apply custom styles
    if (_custom_styled) {
        button_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            button_style.backgroundColor = _style.backgroundColor;
        }
        if (app_utils::is_color_set(_style.border.color)) {
            button_style.border.color = _style.border.color;
        }
        button_style.cornerRadius = _style.cornerRadius;
    }

    _clay->openElement(button_style);
    {
        if (_text_button) {
            _clay->textElement(
                _text,
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(button_foreground_color),
                    .fontId = 0,
                    .fontSize = 25,
                }
            );
        }
    }
    if (_text_button) {
        _clay->closeElement();
    }
    return button_clicked;
}

layout_components::_button_builder layout_components::button() {
    return _button_builder{};
};
void layout_components::close_button(ClayMan& clay) {
    clay.closeElement();
}
