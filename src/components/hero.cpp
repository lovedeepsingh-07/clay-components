#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::hero(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId hero_id = CLAY_SID(id_cs);

    CLAY(Clay_ElementDeclaration{
        .id = hero_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .top = 80 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY_TEXT(
            CLAY_STRING("Build Websites"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                .fontId = 0,
                .fontSize = 64,
            })
        );
        CLAY_TEXT(
            CLAY_STRING("with C/C++"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                .fontId = 0,
                .fontSize = 64,
            })
        );
        // ------ CTA button ------
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() },
                        .padding = { .top = 20 },
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } } }) {
            if (layout_components::button(id + "_cta_button", "Get Started", layout_engine)) {
                printf("Hero CTA button works!\n");
            }
        }
    }
}
