#include "demo.hpp"

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
        layout_components::modal()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_modal_default")
            .build();
    }
    clay.closeElement();
}
