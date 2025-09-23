#include "layout_components.hpp"
#include "utils.hpp"

layout_components::_tooltip_builder&
layout_components::_tooltip_builder::direction(const std::string& direction) {
    this->_direction = direction;
    return *this;
}

layout_components::_tooltip_builder&
layout_components::_tooltip_builder::text(const std::string& text) {
    this->_text = text;
    return *this;
}

void layout_components::_tooltip_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Tooltip>());

    // tooltip state configuration
    bool hovering = _clay->pointerOver(_id);
    Clay_FloatingAttachPointType element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
    Clay_FloatingAttachPointType parent_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;
    auto floating_offset = Clay_Vector2{ 0, 6 };

    if (_direction == "top") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        floating_offset = { 0, -6 };
    }
    if (_direction == "right") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
        floating_offset = { 6, 0 };
    }
    if (_direction == "left") {
        element_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        floating_offset = { -6, 0 };
    }

    // default styles
    auto root_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
    };
    auto tooltip_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id + "_TOOLTIP_CONTAINER"),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(37) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(_engine->get_color("card")),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color =
                        app_utils::raylib_to_clay(_engine->get_color("border")),
                    .width = { 1, 1, 1, 1, 0 } },
    };

    // apply custom styles
    if (_custom_styled) {
        tooltip_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            tooltip_style.backgroundColor = _style.backgroundColor;
        }
        tooltip_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            tooltip_style.border.color = _style.border.color;
        }
        tooltip_style.border.width = _style.border.width;
    }

    _clay->openElement(root_style);

    if (hovering) {
        _clay->openElement(Clay_ElementDeclaration{
            .id = _clay->hashID(_id + "_FLOATING_CONTAINER"),
            .floating = {
                .offset = floating_offset,
                .attachPoints = { .element = element_attach_point, .parent = parent_attach_point },
                .attachTo = CLAY_ATTACH_TO_PARENT,
            } });
        {
            _clay->openElement(tooltip_style);
            _clay->textElement(
                _text,
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(
                        _engine->get_color(_custom_styled ? "foreground" : "card-foreground")
                    ),
                    .fontId = 0,
                    .fontSize = 25,
                }
            );
            _clay->closeElement();
        }
        _clay->closeElement();
    }
}

layout_components::_tooltip_builder layout_components::tooltip() {
    return _tooltip_builder{};
}
void layout_components::close_tooltip(ClayMan& clay) {
    clay.closeElement();
}
