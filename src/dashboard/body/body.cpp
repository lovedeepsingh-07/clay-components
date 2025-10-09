#include "dashboard.hpp"
#include "utils.hpp"
#include <array>

struct Card {
    std::string header_title;
    std::string header_text;
    std::string footer_title;
    std::string footer_description;
};

const std::array<Card, 4> card_list = {
    Card{ "Total Revenue", "$1,250.00", "Trending up this month", "Visitors for the last 6 months" },
    Card{ "New Customers", "1,234", "Down 20% this period", "Acquisition needs attention" },
    Card{ "Active Accounts", "45,678", "Strong user retention", "Engagement exceed targets" },
    Card{ "Growth Rate", "4.5%", "Steady performance icrease", "Meets growth projections" }
};


void dashboard::body::body(LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String body_id_cs =
        layout_engine.frame_arena.alloc_clay_string("dashboard_body");
    Clay_ElementId body_id = CLAY_SID(body_id_cs);

    float corner_radius = layout_engine.get_radius();
    Color card_background_color = layout_engine.get_color("card");
    Color card_foreground_color = layout_engine.get_color("card-foreground");
    Color background_color = layout_engine.get_color("background");
    Color foreground_color = layout_engine.get_color("foreground");
    Color border_color = layout_engine.get_color("border");

    CLAY(Clay_ElementDeclaration{
        .id = body_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
                    .padding = CLAY_PADDING_ALL(8),
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(background_color),
        .cornerRadius = CLAY_CORNER_RADIUS(corner_radius),
        .border = { .color = app_utils::raylib_to_clay(border_color),
                    .width = { 1, 1, 1, 1, 0 } } }) {
        // ------ navbar ------
        dashboard::body::navbar(layout_engine);
        // ------ card list ------
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                        .padding = { 12, 12, 40, 12 },
                        .childGap = 20,
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } } }) {
            for (const Card& curr_card : card_list) {
                CLAY(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                                .padding = CLAY_PADDING_ALL(16),
                                .childGap = 8,
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(card_background_color),
                    .cornerRadius = CLAY_CORNER_RADIUS(corner_radius),
                    .border = { .color = app_utils::raylib_to_clay(border_color),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    CLAY_TEXT(
                        layout_engine.frame_arena.alloc_clay_string(curr_card.header_title),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(card_foreground_color),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                    CLAY_TEXT(
                        layout_engine.frame_arena.alloc_clay_string(curr_card.header_text),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(card_foreground_color),
                            .fontId = 0,
                            .fontSize = 48,
                        })
                    );
                    CLAY_TEXT(
                        layout_engine.frame_arena.alloc_clay_string(curr_card.footer_title),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(card_foreground_color),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                    CLAY_TEXT(
                        layout_engine.frame_arena.alloc_clay_string(curr_card.footer_description),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(card_foreground_color),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                }
            }
        }
        // ------ table ------
        dashboard::body::body_table("body_table", layout_engine);
    }
}
