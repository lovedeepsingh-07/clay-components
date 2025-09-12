#include "ui_engine.hpp"
#include "utils.hpp"

void UIEngine::elements::dropdown(
    ClayMan& clay,
    UIEngine& UI_engine,
    const std::string& element_id,
    const std::function<void()>& children_func
) {
    UI_engine.add_element(element_id, std::make_unique<element_context::Dropdown>());
    auto* ctx = UI_engine.get_element<element_context::Dropdown>(element_id);

    clay.openElement(Clay_ElementDeclaration{ .id = clay.hashID(element_id) });
    {
        const std::string dropdown_button_id = element_id + "_DROPDOWN_BUTTON";
        if (elements::button(clay, UI_engine, dropdown_button_id, [&]() {
                // auto* button_ctx =
                //     UI_engine.get_element<element_context::Button>(dropdown_button_id);
                clay.textElement(
                    (ctx->open ? "close" : "open"),
                    Clay_TextElementConfig{
                        .textColor = game_utils::raylib_to_clay(UI_engine.get_color("primary_"
                                                                                    "foreground")),
                        .fontId = 0,
                        .fontSize = 25,
                    }
                );
            })) {
            ctx->open = !ctx->open;
        };
        if (ctx->open) {
            const std::string dropdown_hovering_container_id =
                element_id + "_DROPDOWN_HOVERING_CONTAINER";
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID(dropdown_hovering_container_id),
                .floating = { .offset = { 0, 35 }, .attachTo = CLAY_ATTACH_TO_PARENT } });
            {
                const std::string dropdown_children_container_id =
                    element_id + "_DROPDOWN_CHILDREN_CONTAINER";
                clay.openElement(Clay_ElementDeclaration{
                    .id = clay.hashID(dropdown_children_container_id),
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(120),
                                            .height = CLAY_SIZING_GROW(20) },
                                .padding = CLAY_PADDING_ALL(8),
                                .childGap = 10,
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = game_utils::raylib_to_clay(UI_engine.get_color("card")),
                    .cornerRadius = CLAY_CORNER_RADIUS(5.0F),
                    .border = { .color = game_utils::raylib_to_clay(UI_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } },
                });
                {
                    // render the children
                    children_func();
                }
                clay.closeElement();
            }
            clay.closeElement();
        }
    }
    clay.closeElement();
}
