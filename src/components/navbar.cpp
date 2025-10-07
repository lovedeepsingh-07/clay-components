#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::navbar(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId navbar_id = CLAY_SID(id_cs);

    Clay_String title_button_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_title_button");
    Clay_ElementId title_button_id = CLAY_SID(title_button_cs);
    bool hovering_title_button = Clay_PointerOver(title_button_id);

    CLAY(Clay_ElementDeclaration{
        .id = navbar_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1200), .height = CLAY_SIZING_FIT() },
                        .padding = CLAY_PADDING_ALL(8),
                        .childGap = 8 } }) {
            // ------ title button ------
            if (hovering_title_button && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
#ifdef __EMSCRIPTEN__
                js::goto_link("/");
#else
                printf("clicked navbar title button\n");
#endif
            }
            CLAY(Clay_ElementDeclaration{
                .id = title_button_id,
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(),
                                        .height = CLAY_SIZING_FIT() } } }) {
                CLAY_TEXT(
                    CLAY_STRING("clay-components"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                        .fontId = 0,
                        .fontSize = 32,
                    })
                );
            }
            // ------ filling ------
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
}
