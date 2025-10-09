#include "dashboard.hpp"
#include "utils.hpp"

void dashboard::sidebar::sidebar_dropdown(
    const std::string& id, bool hovering_curr_item, LayoutEngine::LayoutEngine& layout_engine
) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId dropdown_id = CLAY_SID(id_cs);

    Clay_String floating_container_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_floating_container");
    Clay_ElementId floating_container_id = CLAY_SID(floating_container_id_cs);

    Clay_String dropdown_button_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_button");
    Clay_ElementId dropdown_button_id = CLAY_SID(dropdown_button_id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Dropdown>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Dropdown>(id);

    // dropdown state configuration
    bool hovering_floating_container = Clay_PointerOver(floating_container_id);
    bool hovering_dropdown_button = Clay_PointerOver(dropdown_button_id);
    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && hovering_dropdown_button) {
        ctx->open = !ctx->open;
    }
    if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        && !hovering_floating_container && !hovering_dropdown_button) {
        ctx->open = false;
    }

    // color values
    Color button_background_color =
        ColorAlpha(layout_engine.get_color("primary"), (float)(hovering_dropdown_button ? 0.85 : 1));
    Color button_foreground_color = layout_engine.get_color("primary-foreground");
    Color button_border_color =
        ColorAlpha(layout_engine.get_color("border"), (float)(hovering_dropdown_button ? 0.85 : 1));

    CLAY(Clay_ElementDeclaration{
        .id = dropdown_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() } } }) {
        if (hovering_curr_item) {
            CLAY(Clay_ElementDeclaration{
                .id = dropdown_button_id,
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(), .height = CLAY_SIZING_FIT() },
                            .padding = { .left = 8, .right = 8, .top = 4, .bottom = 4 },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_to_clay(button_background_color),
                .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
                .border = { .color = app_utils::raylib_to_clay(button_border_color),
                            .width = { 1, 1, 1, 1, 0 } } }) {
                Clay_String button_text_cs =
                    layout_engine.frame_arena.alloc_clay_string("...");
                CLAY_TEXT(
                    button_text_cs,
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(button_foreground_color),
                        .fontId = 0,
                        .fontSize = 8,
                    })
                );
            };
        }
        if (ctx->open) {
            // floating container
            CLAY(Clay_ElementDeclaration{
                .id = floating_container_id,
                .floating = { .offset = { 0, 6 },
                              .zIndex = 80,
                              .attachPoints = { .element = CLAY_ATTACH_POINT_LEFT_TOP,
                                                .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM },
                              .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                              .attachTo = CLAY_ATTACH_TO_PARENT } }) {
                // dropdown content container
                CLAY(Clay_ElementDeclaration{
                    .id = CLAY_ID_LOCAL("content_container"),
                    .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                            .height = CLAY_SIZING_FIT(37) },
                                .padding = { .left = 10, .right = 10, .top = 8, .bottom = 8 },
                                .childGap = 14,
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color("card")),
                    .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } },
                }) {
                    CLAY_TEXT(
                        CLAY_STRING("Open"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                    CLAY_TEXT(
                        CLAY_STRING("Share"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                    CLAY_TEXT(
                        CLAY_STRING("Delete"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                };
            };
        }
    }
}
