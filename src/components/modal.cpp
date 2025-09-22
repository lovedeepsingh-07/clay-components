#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::_modal_builder::build() {
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Modal>());
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Modal>(_id);

    std::string button_id = _id + "_MODAL_BUTTON";
    std::string floating_container_id = _id + "_MODAL_FLOATING_CONTAINER";
    std::string content_id = _id + "_MODAL_CONTENT";

    bool hovering_floating_container = _clay->pointerOver(floating_container_id);
    bool hovering_content = _clay->pointerOver(content_id);

    if (hovering_floating_container && !hovering_content
        && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        && ctx->open) {
        ctx->open = false;
    }

    _clay->openElement(Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
    });
    {
        bool button_clicked = layout_components::button()
                                  .clay_man(*_clay)
                                  .engine(*_engine)
                                  .id(button_id)
                                  .variant("primary")
                                  .text("modal")
                                  .build();
        if (button_clicked) {
            ctx->open = true;
        }

        if (ctx->open) {
            _clay->openElement(Clay_ElementDeclaration{
                .id = _clay->hashID(floating_container_id),
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
                .backgroundColor = app_utils::raylib_to_clay(ColorAlpha(BLACK, 0.5)),
                .floating = {
                    .offset = { 0, 0 },
                    .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                    .attachTo = CLAY_ATTACH_TO_ROOT,
                } });
            {
                _clay->openElement(Clay_ElementDeclaration{
                    .id = _clay->hashID(content_id),
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 480),
                                            .height = CLAY_SIZING_GROW(0, 270) },
                                .padding = { .left = 10, .right = 10, .top = 10, .bottom = 10 },
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(_engine->get_color("card")),
                    .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
                    .border = { .color = app_utils::raylib_to_clay(_engine->get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } },
                });
                {

                    _clay->textElement(
                        "modal_text",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }

                _clay->closeElement();
            }
            _clay->closeElement();
        }
    }
    _clay->closeElement();
}

layout_components::_modal_builder layout_components::modal() {
    return _modal_builder{};
}
