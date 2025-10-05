#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::code_block(
    const std::string& id, const std::string& text, LayoutEngine::LayoutEngine& layout_engine
) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId code_id = CLAY_SID(id_cs);

    Clay_String code_string_cs = layout_engine.frame_arena.alloc_clay_string(text);

    CLAY(Clay_ElementDeclaration{
        .id = code_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
        .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                    .width = { 1, 1, 1, 1, 0 } } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0) },
                        .padding = CLAY_PADDING_ALL(8),
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
            .floating = { .attachPoints = { .element = CLAY_ATTACH_POINT_RIGHT_TOP,
                                            .parent = CLAY_ATTACH_POINT_RIGHT_TOP },
                          .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                          .attachTo = CLAY_ATTACH_TO_PARENT } }) {
            if (layout_components::button("copy_code_button", "copy", layout_engine)) {
#ifdef __EMSCRIPTEN__
                js::copy_to_clipboard(text.c_str());
#else
                printf("code copy button clicked\n");
#endif
            }
        }
        CLAY_TEXT(
            code_string_cs,
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                .fontId = 0,
                .fontSize = 24,
            })
        );
    }
}
