#include "demo.hpp"
#include "utils.hpp"

void demo::modal(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("MODAL_DEMO_CONTAINER"),
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
        } });
    {
        // default modal
        auto* default_modal_ctx =
            layout_engine.get_element<LayoutEngine::component_context::Modal>("demo_modal_default");
        bool default_modal_button_clicked = layout_components::button()
                                                .clay_man(clay)
                                                .engine(layout_engine)
                                                .id("demo_modal_default_BUTTON")
                                                .variant("primary")
                                                .text("default modal")
                                                .build();
        if (default_modal_ctx != nullptr && !default_modal_ctx->open
            && default_modal_button_clicked) {
            default_modal_ctx->open = true;
        }
        layout_components::modal_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_modal_default")
            .build();
        {
            if (default_modal_ctx != nullptr && default_modal_ctx->open) {
                layout_components::modal_content()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .root_id("demo_modal_default")
                    .build();
                {
                    clay.textElement(
                        "modal_text",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }
                layout_components::close_modal_content(clay);
            }
        }
        layout_components::close_modal_root(clay);
        // custom modal
        auto* custom_modal_ctx =
            layout_engine.get_element<LayoutEngine::component_context::Modal>("demo_modal_custom");
        bool custom_modal_button_clicked = layout_components::button()
                                               .clay_man(clay)
                                               .engine(layout_engine)
                                               .id("demo_modal_custom_BUTTON")
                                               .variant("primary")
                                               .text("custom modal")
                                               .build();
        if (custom_modal_ctx != nullptr && !custom_modal_ctx->open && custom_modal_button_clicked) {
            custom_modal_ctx->open = true;
        }
        layout_components::modal_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_modal_custom")
            .build();
        {
            if (custom_modal_ctx != nullptr && custom_modal_ctx->open) {
                layout_components::modal_content()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .root_id("demo_modal_custom")
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 480),
                                                .height = CLAY_SIZING_GROW(0, 270) },
                                    .padding = { .left = 10, .right = 10, .top = 10, .bottom = 10 },
                                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .backgroundColor = app_utils::raylib_to_clay(MAROON),
                        .cornerRadius = CLAY_CORNER_RADIUS(0),
                        .border = { .color = app_utils::raylib_to_clay(PURPLE),
                                    .width = { 2, 2, 2, 2, 0 } },
                    })
                    .build();
                {
                    clay.textElement(
                        "custom_modal_text",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(YELLOW),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }
                layout_components::close_modal_content(clay);
            }
        }
        layout_components::close_modal_root(clay);
    }
    clay.closeElement();
}
