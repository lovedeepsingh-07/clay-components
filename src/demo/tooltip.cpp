#include "demo.hpp"

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
            .id("demo_tooltip_default_left")
            .direction("left")
            .build();
        layout_components::tooltip()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tooltip_default_top")
            .direction("top")
            .build();
        layout_components::tooltip()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tooltip_default_bottom")
            .direction("bottom")
            .build();
        layout_components::tooltip()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tooltip_default_right")
            .direction("right")
            .build();
    }
    clay.closeElement();
}
