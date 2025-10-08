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
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 360), .height = CLAY_SIZING_GROW() },
                    .padding = CLAY_PADDING_ALL(8),
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(background_color) }) {
        // CLAY_TEXT(
        //     CLAY_STRING("Sidebar"),
        //     CLAY_TEXT_CONFIG(Clay_TextElementConfig{
        //         .textColor = app_utils::raylib_to_clay(foreground_color),
        //         .fontId = 0,
        //         .fontSize = 24,
        //     })
        // );
        dashboard::sidebar::header(layout_engine);
        dashboard::sidebar::body(layout_engine);
        dashboard::sidebar::footer(layout_engine);
    }
}
