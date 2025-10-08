#include "dashboard.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void dashboard::sidebar::body(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String body_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_sidebar_body");
    Clay_ElementId body_id = CLAY_SID(body_id_cs);

    Color foreground_color = layout_engine.get_color("card-foreground");

    CLAY(Clay_ElementDeclaration{
        .id = body_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT() },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT } }) {
        CLAY_TEXT(
            CLAY_STRING("Body"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(foreground_color),
                .fontId = 0,
                .fontSize = 24,
            })
        );
    }
}
