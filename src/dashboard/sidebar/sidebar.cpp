#include "dashboard.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void dashboard::sidebar::sidebar(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String sidebar_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_sidebar");
    Clay_ElementId sidebar_id = CLAY_SID(sidebar_id_cs);

    Color background_color = layout_engine.get_color("card");
    Color foreground_color = layout_engine.get_color("card-foreground");

    CLAY(Clay_ElementDeclaration{
        .id = sidebar_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 300), .height = CLAY_SIZING_GROW() },
                    .padding = CLAY_PADDING_ALL(10),
                    .childGap = 16,
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(background_color) }) {
        dashboard::sidebar::header(layout_engine);
        dashboard::sidebar::body(layout_engine);
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(),
                                    .height = CLAY_SIZING_GROW() } } }) {}
        dashboard::sidebar::footer(layout_engine);
    }
}
