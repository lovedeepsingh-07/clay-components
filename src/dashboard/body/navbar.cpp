#include "dashboard.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void dashboard::body::navbar(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String navbar_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_body_navbar");
    Clay_ElementId navbar_id = CLAY_SID(navbar_id_cs);

    Color foreground_color = layout_engine.get_color("card-foreground");

    CLAY(Clay_ElementDeclaration{
        .id = navbar_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .childGap = 8,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT } }) {
        CLAY_TEXT(
            CLAY_STRING("Navbar"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(foreground_color),
                .fontId = 0,
                .fontSize = 24,
            })
        );
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(),
                                    .height = CLAY_SIZING_FIT() } } }) {}
        // ------ github button ------
        if (layout_components::button("github_button", "github", "primary", layout_engine)) {
#ifdef __EMSCRIPTEN__
            js::open_link("https://github.com/lovedeepsingh-07/"
                          "clay-components");
#else
            printf("github button clicked!\n");
#endif
        }
        // ------ theme button ------
        if (layout_components::button("theme_button", "theme", "primary", layout_engine)) {
            if (layout_engine.get_curr_theme() == "dark") {
                layout_engine.set_theme("light");
            } else {
                layout_engine.set_theme("dark");
            }
        }
    }
}
