#include "layout_components.hpp"
#include "utils.hpp"
#include <clay.h>
#include <cstring>

void layout_components::tabs(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    auto id_cs = Clay_String{
        .length = (std::int32_t)id.size(),
        .chars = layout_engine.frame_arena.alloc_string(id),
    };
    Clay_ElementId tab_id = CLAY_SID(id_cs);
    std::string button_list_container_str = id + "_BUTTON_LIST_CONTAINER";
    auto button_list_container_cs = Clay_String{
        .length = (std::int32_t)button_list_container_str.size(),
        .chars = layout_engine.frame_arena.alloc_string(button_list_container_str),
    };
    Clay_ElementId button_list_container_id = CLAY_SID(button_list_container_cs);
    std::string content_container_str = id + "_CONTENT_CONTAINER";
    auto content_container_cs = Clay_String{
        .length = (std::int32_t)content_container_str.size(),
        .chars = layout_engine.frame_arena.alloc_string(content_container_str),
    };
    Clay_ElementId content_container_id = CLAY_SID(content_container_cs);

    auto tab_ctx = LayoutEngine::component_context::Tabs{};
    tab_ctx.tab_list = std::vector<std::string>({ "home", "posts", "about" });
    tab_ctx.curr_tab = tab_ctx.tab_list[0];

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Tabs>(tab_ctx));
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Tabs>(id);

    // root container
    CLAY(Clay_ElementDeclaration{
        .id = tab_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1280),
                                .height = CLAY_SIZING_GROW(0, 720) },
                    .padding = CLAY_PADDING_ALL(12),
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()) }) {
        // button list container
        CLAY(Clay_ElementDeclaration{
            .id = button_list_container_id,
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 500), .height = CLAY_SIZING_FIT() },
                        .padding = CLAY_PADDING_ALL(6),
                        // .childGap = 8,
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_LEFT_TO_RIGHT },
            .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
            .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                        .width = { 1, 1, 1, 1, 0 } } }) {
            std::string next_tab = ctx->curr_tab;
            for (int i = 0; i < ctx->tab_list.size(); i++) {
                std::string curr_button_str = id + "_BUTTON_" + ctx->tab_list[i];
                auto curr_button_cs = Clay_String{
                    .length = (std::int32_t)curr_button_str.size(),
                    .chars = layout_engine.frame_arena.alloc_string(curr_button_str),
                };
                Clay_ElementId curr_button_id = CLAY_SID(curr_button_cs);
                if (Clay_PointerOver(curr_button_id)
                    && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    next_tab = ctx->tab_list[i];
                }
                CLAY(Clay_ElementDeclaration{
                    .id = curr_button_id,
                    .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                            .height = CLAY_SIZING_FIT(20) },
                                .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color(
                        (ctx != nullptr && ctx->curr_tab == ctx->tab_list[i]) ? "primary" : "card"
                    )),
                    .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    std::string curr_tab_str = ctx->tab_list[i];
                    auto curr_tab_cs = Clay_String{
                        .length = (std::int32_t)curr_tab_str.size(),
                        .chars = layout_engine.frame_arena.alloc_string(curr_tab_str),
                    };
                    CLAY_TEXT(
                        curr_tab_cs,
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color(
                                (ctx != nullptr && ctx->curr_tab == ctx->tab_list[i]) ? "primary-foreground" : "card-foreground"
                            )),
                            .fontId = 0,
                            .fontSize = 24,
                        })
                    );
                };
            }
            if (next_tab != ctx->curr_tab) {
                ctx->curr_tab = next_tab;
            }
        }
        // content container
        CLAY(Clay_ElementDeclaration{
            .id = content_container_id,
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                        .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
        }) {
            for (int i = 0; i < ctx->tab_list.size(); i++) {
                if (ctx->curr_tab == ctx->tab_list[i]) {
                    std::string curr_tab_str = ctx->tab_list[i];
                    auto curr_tab_cs = Clay_String{
                        .length = (std::int32_t)curr_tab_str.size(),
                        .chars = layout_engine.frame_arena.alloc_string(curr_tab_str),
                    };
                    CLAY_TEXT(
                        curr_tab_cs,
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                            .fontId = 0,
                            .fontSize = 25,
                        })
                    );
                }
            }
        }
    }
}
