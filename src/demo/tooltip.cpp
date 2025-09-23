#include "demo.hpp"
#include "utils.hpp"

void demo::tooltip(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("TOOLTIP_DEMO_CONTAINER"),
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
        } });
    {
        layout_components::tooltip()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tooltip_default_bottom")
            .direction("bottom")
            .text("default")
            .build();
        {
            layout_components::button()
                .clay_man(clay)
                .engine(layout_engine)
                .id("demo_tooltip_default_bottom_button")
                .variant("primary")
                .text("tooltip")
                .build();
        }
        layout_components::close_tooltip(clay);
        layout_components::tooltip()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tooltip_custom_bottom")
            .text("default")
            .style(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                        .height = CLAY_SIZING_FIT(37) },
                            .padding = { .left = 6, .right = 6, .top = 4, .bottom = 4 },
                            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_to_clay(MAROON),
                .cornerRadius = CLAY_CORNER_RADIUS(0),
                .border = { .color = app_utils::raylib_to_clay(PURPLE),
                            .width = { 2, 2, 2, 2, 0 } },
            })
            .direction("bottom")
            .build();
        {
            layout_components::button()
                .clay_man(clay)
                .engine(layout_engine)
                .id("demo_tooltip_custom_bottom_button")
                .variant("primary")
                .text("tooltip")
                .build();
        }
        layout_components::close_tooltip(clay);
    }
    clay.closeElement();
}
