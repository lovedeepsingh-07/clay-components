#include "dashboard.hpp"
#include "js.hpp"
#include "utils.hpp"

void dashboard::body::navbar(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String navbar_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_body_navbar");
    Clay_ElementId navbar_id = CLAY_SID(navbar_id_cs);

    Color foreground_color = layout_engine.get_color("card-foreground");
    Color border_color = layout_engine.get_color("border");

    CLAY(Clay_ElementDeclaration{
        .id = navbar_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .left = 4, .right = 4, .bottom = 8 },
                    .childGap = 8,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT },
        .border = { .color = app_utils::raylib_to_clay(border_color),
                    .width = { .bottom = 1 } } }) {
        CLAY_TEXT(
            CLAY_STRING("Documents"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(foreground_color),
                .fontId = 0,
                .fontSize = 26,
            })
        );
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(),
                                    .height = CLAY_SIZING_FIT() } } }) {}
        // ------ github button ------
        if (dashboard::body::navbar_button("github_button", "github", layout_engine)) {
#ifdef __EMSCRIPTEN__
            js::open_link("https://github.com/lovedeepsingh-07/"
                          "clay-components");
#else
            printf("github button clicked!\n");
#endif
        }
        // ------ theme button ------
        if (dashboard::body::navbar_button("theme_button", "theme", layout_engine)) {
            if (layout_engine.get_curr_theme() == "dark") {
                layout_engine.set_theme("light");
            } else {
                layout_engine.set_theme("dark");
            }
        }
    }
}
