#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::_dropdown_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Dropdown>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Dropdown>(_id);

    // dropdown container
    _clay->openElement(Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
    });
    {
        // dropdown_button
        bool clicked = layout_components::button()
                           .clay_man(*_clay)
                           .engine(*_engine)
                           .id(_id + "_DROPDOWN_BUTTON")
                           .variant("primary")
                           .text(ctx->open ? "close" : "open")
                           .build();
        if (clicked) {
            ctx->open = !ctx->open;
        }
        if (ctx->open) {
            Clay_ElementData dropdown_button_data =
                Clay_GetElementData(_clay->getClayElementId(_id + "_DROPDOWN_BUTTON"));
            float floating_container_offset_y =
                (dropdown_button_data.found ? dropdown_button_data.boundingBox.height + 5 : 45);

            // dropdown floating container
            _clay->openElement(Clay_ElementDeclaration{
                .id = _clay->hashID(_id + "_DROPDOWN_FLOATING_CONTAINER"),
                .floating = { .offset = { 0, floating_container_offset_y },
                              .attachTo = CLAY_ATTACH_TO_PARENT } });
            {
                // dropdown children container
                _clay->openElement(Clay_ElementDeclaration{
                    .id = _clay->hashID(_id + "_DROPDOWN_CHILDREN_CONTAINER"),
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
                {
                    _clay->element(Clay_ElementDeclaration{}, [&]() {
                        _clay->textElement(
                            "Dropdown Children 1",
                            Clay_TextElementConfig{
                                .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                                .fontId = 0,
                                .fontSize = 20,
                            }
                        );
                    });
                    _clay->element(Clay_ElementDeclaration{}, [&]() {
                        _clay->textElement(
                            "Dropdown Children 2",
                            Clay_TextElementConfig{
                                .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                                .fontId = 0,
                                .fontSize = 20,
                            }
                        );
                    });
                }
                _clay->closeElement();
            }
            _clay->closeElement();
        }
    }
    _clay->closeElement();
}
layout_components::_dropdown_builder layout_components::dropdown() {
    return _dropdown_builder{};
};
