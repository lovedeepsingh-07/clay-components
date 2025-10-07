#include "demo.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void demo::button(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId button_demo_id = CLAY_SID(id_cs);
    float corner_radius = layout_engine.get_radius();

    CLAY(Clay_ElementDeclaration{
        .id = button_demo_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .left = 12, .right = 12, .top = 12 },
                    .childGap = 12,
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1000), .height = CLAY_SIZING_FIT() },
                        .childGap = 12,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            CLAY_TEXT(
                CLAY_STRING("Button"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 48,
                })
            );
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
                // ------ component display ------
                CLAY(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 600),
                                            .height = CLAY_SIZING_FIXED(320) },
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
                    .cornerRadius = { corner_radius, corner_radius, 0, 0 },
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    if (layout_components::button(id + "_primary_demo_button", "Button", layout_engine)) {
#ifdef __EMSCRIPTEN__
                        js::alert("button clicked!");
#else
                        printf("button clicked!\n");
#endif
                    };
                }
                // ------ code block ------
                CLAY(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 600),
                                            .height = CLAY_SIZING_FIT(0) },
                                .padding = CLAY_PADDING_ALL(8),
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .cornerRadius = { 0, 0, corner_radius, corner_radius },
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    std::string code_string = R"(#include <iostream>
int main() {
    std::cout << "Hello World" << '\n';
    return 0;
})";
                    Clay_String code_string_cs =
                        layout_engine.frame_arena.alloc_clay_string(code_string);
                    CLAY(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_FIT(0),
                                                .height = CLAY_SIZING_FIT(0) },
                                    .padding = CLAY_PADDING_ALL(8),
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .floating = { .attachPoints = { .element = CLAY_ATTACH_POINT_RIGHT_TOP,
                                                        .parent = CLAY_ATTACH_POINT_RIGHT_TOP },
                                      .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                                      .attachTo = CLAY_ATTACH_TO_PARENT } }) {
                        if (layout_components::button("copy_code_button", "copy", layout_engine)) {
#ifdef __EMSCRIPTEN__
                            js::copy_to_clipboard(code_string.c_str());
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
        }
    }
}
