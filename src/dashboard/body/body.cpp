#include "dashboard.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void dashboard::body::body(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String body_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_body");
    Clay_ElementId body_id = CLAY_SID(body_id_cs);

    float corner_radius = layout_engine.get_radius();
    Color background_color = layout_engine.get_color("background");
    Color foreground_color = layout_engine.get_color("foreground");
    Color border_color = layout_engine.get_color("border");

    CLAY(Clay_ElementDeclaration{
        .id = body_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .padding = CLAY_PADDING_ALL(8),
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(corner_radius),
        .border = { .color = app_utils::raylib_to_clay(border_color),
                    .width = { 1, 1, 1, 1, 0 } } }) {
        dashboard::body::navbar(layout_engine);
        CLAY_TEXT(
            CLAY_STRING("Body"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(foreground_color),
                .fontId = 0,
                .fontSize = 48,
            })
        );
    }
}
