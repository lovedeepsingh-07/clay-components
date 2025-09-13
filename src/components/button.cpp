#include "layout_components.hpp"
#include "utils.hpp"
#include <array>

layout_components::_button_builder&
layout_components::_button_builder::clay_man(ClayMan& clay) {
    this->_clay = &clay;
    return *this;
}
layout_components::_button_builder&
layout_components::_button_builder::engine(LayoutEngine::LayoutEngine& engine) {
    this->_engine = &engine;
    return *this;
}
layout_components::_button_builder&
layout_components::_button_builder::id(const std::string& id) {
    this->_id = id;
    return *this;
}
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
layout_components::_button_builder& layout_components::_button_builder::children_input(
    std::variant<std::string, std::function<void()>> children_input
) {
    this->_children_input = children_input;
    return *this;
}

bool layout_components::_button_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Button>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Button>(_id);
    bool button_clicked = false;

    std::array<std::string, 5> accepted_variants = { "primary", "secondary", "muted",
                                                     "accent", "destructive" };
    std::string button_variant =
        (std::find(std::begin(accepted_variants), std::end(accepted_variants), _variant)
         != std::end(accepted_variants))
        ? _variant
        : "primary"; // if the variant is valid, the we take that or else, we default to primary

    // default button style
    auto button_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(20) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = game_utils::raylib_to_clay(
            ColorAlpha(_engine->get_color(button_variant), ((ctx->hovered || ctx->pressed) ? 0.85 : 1))
        ),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color = game_utils::raylib_to_clay(ColorAlpha(
                        _engine->get_color("border"), ((ctx->hovered || ctx->pressed) ? 0.85 : 1)
                    )),
                    .width = { 1, 1, 1, 1, 0 } }
    };

    if (_custom_styled) {
        button_style.layout = _style.layout;
        button_style.cornerRadius = _style.cornerRadius;
    }

    _clay->openElement(button_style);
    {
        // button state configuration
        bool hovering = this->_clay->pointerOver(this->_id);
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

        // rendering children
        std::visit(
            [&](auto&& arg) {
                using curr_type = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<curr_type, std::string>) {
                    // text element
                    this->_clay->textElement(
                        arg,
                        Clay_TextElementConfig{
                            .textColor =
                                game_utils::raylib_to_clay(this->_engine->get_color(
                                    (_custom_styled ? "foreground" : button_variant + "-foreground")
                                )),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }
                if constexpr (std::is_same_v<curr_type, std::function<void()>>) {
                    // children element
                    arg();
                }
            },
            _children_input
        );
    }
    this->_clay->closeElement();

    return button_clicked;
}

layout_components::_button_builder layout_components::button() {
    return _button_builder{};
};
