#include "layout_components.hpp"
#include "utils.hpp"

layout_components::_tooltip_builder&
layout_components::_tooltip_builder::direction(const std::string& direction) {
    this->_direction = direction;
    return *this;
}

void layout_components::_tooltip_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Tooltip>());

    // tooltip state configuration
    bool hovering = _clay->pointerOver(_id);
    auto tooltip_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(120), .height = CLAY_SIZING_FIT(20) },
                    .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
    };

    Clay_FloatingAttachPointType element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
    Clay_FloatingAttachPointType parent_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;

    if (_direction == "top") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
    }
    if (_direction == "right") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
    }
    if (_direction == "left") {
        element_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
    }

    _clay->openElement(tooltip_style);
    layout_components::button()
        .clay_man(*_clay)
        .engine(*_engine)
        .id(_id + "_BUTTON")
        .variant("primary")
        .text("tooltip")
        .build();


    if (hovering) {
        _clay->openElement(Clay_ElementDeclaration{
            .id = _clay->hashID(_id + "_FLOATING_CONTAINER"),
            .floating = {
                .offset = { 4, 0 },
                .attachPoints = { .element = element_attach_point, .parent = parent_attach_point },
                .attachTo = CLAY_ATTACH_TO_PARENT,
            } });
        {
            _clay->openElement(Clay_ElementDeclaration{
                .id = _clay->hashID(_id + "_TOOLTIP_CONTAINER"),
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                        .height = CLAY_SIZING_FIT(37) },
                            .padding = { .left = 10, .right = 10, .top = 8, .bottom = 8 },
                            .childGap = 14,
                            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_to_clay(_engine->get_color("card")),
                .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
                .border = { .color = app_utils::raylib_to_clay(_engine->get_color("border")),
                            .width = { 1, 1, 1, 1, 0 } },
            });
            _clay->textElement(
                "this is a tooltip",
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                    .fontId = 0,
                    .fontSize = 25,
                }
            );
            _clay->closeElement();
        }
        _clay->closeElement();
    }
    _clay->closeElement();
}

layout_components::_tooltip_builder layout_components::tooltip() {
    return _tooltip_builder{};
}
