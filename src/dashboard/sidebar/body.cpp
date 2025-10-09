#include "dashboard.hpp"
#include "utils.hpp"
#include <array>

const std::array<std::string, 6> header_list = { "Quick Create", "Dashboard",
                                                 "Lifecycle",    "Analytics",
                                                 "Projects",     "Team" };
const std::array<std::string, 3> header_document_list = { "Data Library", "Reports",
                                                          "Word Assistant" };

void dashboard::sidebar::body(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String body_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_sidebar_body");
    Clay_ElementId body_id = CLAY_SID(body_id_cs);

    // state configuration variables
    float corner_radius = layout_engine.get_radius();
    Color background_color = layout_engine.get_color("card");
    Color foreground_color = layout_engine.get_color("card-foreground");
    Color border_color = layout_engine.get_color("border");
    Color selected_color = layout_engine.get_color("primary");
    Color selected_foreground_color =
        layout_engine.get_color("primary-foreground");

    CLAY(Clay_ElementDeclaration{
        .id = body_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .childGap = 10,
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .cornerRadius = CLAY_CORNER_RADIUS(corner_radius) }) {
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
                    curr_item == std::string("Quick Create")
                        ? selected_color
                        : (hovering_curr_item ? ColorAlpha(layout_engine.get_color("accent"), 0.85) : background_color)
                ),
                .cornerRadius = CLAY_CORNER_RADIUS(corner_radius) }) {
                CLAY_TEXT(
                    curr_item_cs,
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(
                            curr_item == std::string("Quick Create") ? selected_foreground_color : foreground_color
                        ),
                        .fontId = 0,
                        .fontSize = 20,
                    })
                );
            }
        }
    }
    CLAY(Clay_ElementDeclaration{
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .bottom = 8 } },
        .border = { .color = app_utils::raylib_to_clay(border_color),
                    .width = { 0, 0, 0, 1, 0 } } }) {
        CLAY_TEXT(
            CLAY_STRING("Documents"),
            CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(foreground_color),
                .fontId = 0,
                .fontSize = 18,
            })
        );
    }
    CLAY(Clay_ElementDeclaration{
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .childGap = 10,
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .cornerRadius = CLAY_CORNER_RADIUS(corner_radius) }) {
        for (const auto& curr_item : header_document_list) {
            Clay_String curr_item_cs =
                layout_engine.frame_arena.alloc_clay_string(curr_item);
            Clay_ElementId curr_id = CLAY_SID(curr_item_cs);
            bool hovering_curr_item = Clay_PointerOver(curr_id);

            CLAY(Clay_ElementDeclaration{
                .id = curr_id,
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 220),
                                        .height = CLAY_SIZING_FIT() },
                            .padding = CLAY_PADDING_ALL(6),
                            .childAlignment = { .y = CLAY_ALIGN_Y_CENTER } },
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
                CLAY(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(),
                                            .height = CLAY_SIZING_FIT() } } }) {}
                dashboard::sidebar::sidebar_dropdown(curr_item + "_dropdown", hovering_curr_item, layout_engine);
            }
        }
    }
}
