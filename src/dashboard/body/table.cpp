#include "dashboard.hpp"
#include "utils.hpp"

void dashboard::body::body_table(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    // color values
    float corner_radius = layout_engine.get_radius();
    Color foreground_color = layout_engine.get_color("foreground");
    Color border_color = layout_engine.get_color("border");
    Color header_background_color = layout_engine.get_color("card");
    Color header_foreground_color = layout_engine.get_color("card-foreground");

    CLAY(Clay_ElementDeclaration{
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .padding = { 12, 12, 0, 12 },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                        .padding = {},
                        .childGap = 0,
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
            .cornerRadius = CLAY_CORNER_RADIUS(corner_radius),
            .border = { .color = app_utils::raylib_to_clay(border_color),
                        .width = { 1, 1, 1, 1, 0 } } }) {
            // ------ table header ------
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                            .padding = { 12, 12, 8, 8 },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
                .backgroundColor = app_utils::raylib_to_clay(header_background_color) }) {
                CLAY_TEXT(
                    CLAY_STRING("Table Header"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(header_foreground_color),
                        .fontId = 0,
                        .fontSize = 20,
                    })
                );
            }
            // ------ table body ------
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER,
                                                .y = CLAY_ALIGN_Y_CENTER } } }) {
                CLAY_TEXT(
                    CLAY_STRING("Table Body"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(foreground_color),
                        .fontId = 0,
                        .fontSize = 48,
                    })
                );
            }
        }
    }
}
