#include "layout_components.hpp"
#include "utils.hpp"

// dropdown root
void layout_components::_dropdown_root_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Dropdown>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Dropdown>(_id);
    _clay->openElement(Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
    });
}
layout_components::_dropdown_root_builder layout_components::dropdown_root() {
    return _dropdown_root_builder{};
};
void layout_components::close_dropdown_root(ClayMan& clay) {
    clay.closeElement();
};

layout_components::_dropdown_content_builder&
layout_components::_dropdown_content_builder::root_id(const std::string& root_id) {
    this->_root_id = root_id;
    return *this;
}
layout_components::_dropdown_content_builder&
layout_components::_dropdown_content_builder::button_clicked(bool button_clicked) {
    this->_button_clicked = button_clicked;
    return *this;
}
layout_components::_dropdown_content_builder&
layout_components::_dropdown_content_builder::children(std::function<void()> children) {
    this->_children = children;
    return *this;
}
// dropdown content
void layout_components::_dropdown_content_builder::build() {
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Dropdown>(_root_id);

    std::string floating_container_id = _root_id + "_DROPDOWN_FLOATING_CONTAINER";
    std::string children_container_id = _root_id + "_DROPDOWN_CHILDREN_CONTAINER";

    // dropdown state configuration
    bool hovering = _clay->pointerOver(floating_container_id);
    if (_button_clicked) {
        ctx->open = !ctx->open;
    }
    if ((IsMouseButtonReleased(MOUSE_BUTTON_LEFT) || IsMouseButtonReleased(MOUSE_BUTTON_RIGHT))
        && !hovering && !_button_clicked) {
        ctx->open = false;
    }

    // default dropdown children content styles
    auto dropdown_children_content_style = Clay_ElementDeclaration{
        .id = _clay->hashID(children_container_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(37) },
                    .padding = { .left = 10, .right = 10, .top = 8, .bottom = 8 },
                    .childGap = 14,
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
        dropdown_children_content_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            dropdown_children_content_style.backgroundColor = _style.backgroundColor;
        }
        dropdown_children_content_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            dropdown_children_content_style.border.color = _style.border.color;
        }
        dropdown_children_content_style.border.width = _style.border.width;
    }

    if (ctx->open) {
        // dropdown floating container
        _clay->openElement(Clay_ElementDeclaration{
            .id = _clay->hashID(floating_container_id),
            .floating = {
                .offset = { 0, 6 },
                .attachPoints = { .element = CLAY_ATTACH_POINT_LEFT_TOP, .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM },
                .attachTo = CLAY_ATTACH_TO_PARENT,
            } });
        {
            // dropdown children container
            _clay->openElement(dropdown_children_content_style);
            { _children(); }
            _clay->closeElement();
        }
        _clay->closeElement();
    }
}
layout_components::_dropdown_content_builder layout_components::dropdown_content() {
    return _dropdown_content_builder{};
};
