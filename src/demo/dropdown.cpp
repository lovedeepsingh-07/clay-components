#include "demo.hpp"
#include "utils.hpp"

void demo::dropdown(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("DROPDOWN_DEMO_CONTAINER"),
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
        } });
    {
        // default dropdown
        layout_components::dropdown_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_dropdown_default")
            .build();
        {
            auto* default_dropdown_ctx =
                layout_engine.get_element<LayoutEngine::component_context::Dropdown>("demo_dropdown_default"
                );
            bool clicked =
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_dropdown_default_BUTTON")
                    .variant("primary")
                    .text(
                        (default_dropdown_ctx != nullptr && default_dropdown_ctx->open) ? "close" : "open"
                    )
                    .build();
            layout_components::dropdown_content()
                .clay_man(clay)
                .engine(layout_engine)
                .root_id("demo_dropdown_default")
                .button_clicked(clicked)
                .children([&]() {
                    clay.textElement(
                        "Dropdown Children 1",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        }
                    );
                })
                .build();
        }
        layout_components::close_dropdown_root(clay);
        // custom dropdown
        layout_components::dropdown_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_dropdown_custom")
            .build();
        {
            auto* default_dropdown_ctx =
                layout_engine.get_element<LayoutEngine::component_context::Dropdown>("demo_dropdown_custom");
            bool clicked =
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_dropdown_custom_BUTTON")
                    .variant("primary")
                    .text(
                        (default_dropdown_ctx != nullptr && default_dropdown_ctx->open) ? "close" : "open"
                    )
                    .build();
            layout_components::dropdown_content()
                .clay_man(clay)
                .engine(layout_engine)
                .style(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                            .height = CLAY_SIZING_FIT(37) },
                                .padding = { .left = 10, .right = 10, .top = 8, .bottom = 8 },
                                .childGap = 14,
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(MAROON),
                    .cornerRadius = CLAY_CORNER_RADIUS(0),
                    .border = { .color = app_utils::raylib_to_clay(PURPLE),
                                .width = { 2, 2, 2, 2, 0 } },
                })
                .root_id("demo_dropdown_custom")
                .button_clicked(clicked)
                .children([&]() {
                    clay.textElement(
                        "Dropdown Children 2",
                        Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        }
                    );
                })
                .build();
        }
        layout_components::close_dropdown_root(clay);
    }
    clay.closeElement();
}
