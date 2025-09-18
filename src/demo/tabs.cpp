#include "demo.hpp"

void demo::tabs(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("TABS_DEMO_CONTAINER"),
        .layout = {
            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
        } });
    {
        layout_components::tabs_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tabs_default")
            .build();
    }
    clay.closeElement();
}
