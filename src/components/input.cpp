#include "layout_components.hpp"
#include "utils.hpp"
#include <cctype>

layout_components::_input_builder&
layout_components::_input_builder::placeholder(const std::string& placeholder) {
    this->_placeholder = placeholder;
    return *this;
};

layout_components::_input_builder&
layout_components::_input_builder::value(std::string& value) {
    this->_value = &value;
    return *this;
};

void layout_components::_input_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Input>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Input>(_id);

    // input state configuration
    bool hovering = _clay->pointerOver(_id);
    if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && !ctx->focused) {
        ctx->focused = true;
    }
    if (!hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && ctx->focused) {
        ctx->focused = false;
    }
    if (ctx->value.c_str() != _value->c_str()) {
        ctx->value = _value->c_str();
    }
    if (ctx->focused) {
        int key = GetCharPressed();
        while (key > 0) {
            if (key >= 32 && key <= 126) {
                _value->push_back((char)key);
            }
            key = GetCharPressed();
        }
        if ((IsKeyPressed(KEY_BACKSPACE)) && !_value->empty()) {
            _value->pop_back();
        }
        if (IsKeyPressed(KEY_BACKSPACE)
            && (IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL))) {
            _value->clear();
        }
    }

    // default color values
    Color input_background_color = _engine->get_color(ctx->focused ? "card" : "background");
    Color input_placeholder_color = _engine->get_color("muted-foreground");
    Color input_foreground_color = _engine->get_color("foreground");
    Color input_border_color = _engine->get_color("border");
    auto input_border_width = ctx->focused ? Clay_BorderWidth{ 3, 3, 3, 3, 0 }
                                           : Clay_BorderWidth{ 1, 1, 1, 1, 0 };

    // default input style
    auto input_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(160), .height = CLAY_SIZING_FIT(37) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(input_background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color = app_utils::raylib_to_clay(input_border_color), .width = input_border_width }
    };

    // apply custom styles
    if (_custom_styled) {
        input_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            input_style.backgroundColor = _style.backgroundColor;
        }
        input_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            input_style.border.color = _style.border.color;
        }
        input_style.border.width = _style.border.width;
    }

    _clay->openElement(input_style);
    {
        // FIXME: there has to be a way to allow users to modify the style of placeholder text as well as input text
        if (_value->empty() && !ctx->focused) {
            _clay->textElement(
                _placeholder,
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(input_placeholder_color),
                    .fontId = 0,
                    .fontSize = 25,
                }
            );
        }
        _clay->textElement(
            ctx->value,
            Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(input_foreground_color),
                .fontId = 0,
                .fontSize = 25,
            }
        );
    }
    _clay->closeElement();
}

layout_components::_input_builder layout_components::input() {
    return _input_builder{};
};
