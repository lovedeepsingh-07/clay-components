#include "dashboard.hpp"
#include "utils.hpp"

void dashboard::dashboard(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String dashboard_id_cs = layout_engine.frame_arena.alloc_clay_string("dashboard");
    Clay_ElementId dashboard_id = CLAY_SID(dashboard_id_cs);

    Color background_color = layout_engine.get_color("card");

    // context menu
    dashboard::context_menu("main_context_menu", layout_engine);
    // actual dashboard
    CLAY(Clay_ElementDeclaration{
        .id = dashboard_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .padding = CLAY_PADDING_ALL(8),
                    .layoutDirection = CLAY_LEFT_TO_RIGHT },
        .backgroundColor = app_utils::raylib_to_clay(background_color) }) {
        dashboard::sidebar::sidebar(layout_engine);
        dashboard::body::body(layout_engine);
    }
}
