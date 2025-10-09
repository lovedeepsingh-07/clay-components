#include "dashboard.hpp"
#include "utils.hpp"
#include <array>

const std::array<std::string, 3> header_list = { "Settings", "Get Help", "Search" };

void dashboard::sidebar::footer(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String footer_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_sidebar_footer");
    Clay_ElementId footer_id = CLAY_SID(footer_id_cs);

    float corner_radius = layout_engine.get_radius();
    Color background_color = layout_engine.get_color("card");
    Color foreground_color = layout_engine.get_color("card-foreground");
    Color profile_color = layout_engine.get_color("primary");

    CLAY(Clay_ElementDeclaration{
        .id = footer_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT() },
                    .childGap = 32,
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT() },
                        .childGap = 10,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            for (const auto& curr_item : header_list) {
                Clay_String curr_item_cs =
                    layout_engine.frame_arena.alloc_clay_string(curr_item);
                Clay_ElementId curr_id = CLAY_SID(curr_item_cs);
                bool hovering_curr_item = Clay_PointerOver(curr_id);

                CLAY(Clay_ElementDeclaration{
                    .id = curr_id,
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 220),
                                            .height = CLAY_SIZING_FIT() },
                                .padding = CLAY_PADDING_ALL(6) },
                    .backgroundColor = app_utils::raylib_to_clay(
                        hovering_curr_item ? ColorAlpha(layout_engine.get_color("accent"), 0.85) : background_color
                    ),
                    .cornerRadius = CLAY_CORNER_RADIUS(corner_radius) }) {
                    CLAY_TEXT(
                        curr_item_cs,
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(foreground_color),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                }
            }
        }
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("footer_profile"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 260), .height = CLAY_SIZING_FIT() },
                        .padding = CLAY_PADDING_ALL(6),
                        .childGap = 8,
                        .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_LEFT_TO_RIGHT },
            .backgroundColor = app_utils::raylib_to_clay(
                Clay_PointerOver(CLAY_ID("footer_profile"))
                    ? ColorAlpha(layout_engine.get_color("accent"), 0.85)
                    : background_color
            ),
            .cornerRadius = CLAY_CORNER_RADIUS(corner_radius) }) {
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIXED(32),
                                        .height = CLAY_SIZING_FIXED(32) } },
                .backgroundColor = app_utils::raylib_to_clay(profile_color),
                .cornerRadius = CLAY_CORNER_RADIUS(20) }) {}
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                            .childGap = 4,
                            .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
                CLAY_TEXT(
                    CLAY_STRING("clay-components"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(foreground_color),
                        .fontId = 0,
                        .fontSize = 20,
                    })
                );
                CLAY_TEXT(
                    CLAY_STRING("info@clay-components.com"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(foreground_color),
                        .fontId = 0,
                        .fontSize = 16,
                    })
                );
            }
        }
    }
}
