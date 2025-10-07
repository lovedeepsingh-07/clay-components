#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::dropdown(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId dropdown_id = CLAY_SID(id_cs);

    Clay_String floating_container_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_FLOATING_CONTAINER");
    Clay_ElementId floating_container_id = CLAY_SID(floating_container_id_cs);

    Clay_String dropdown_button_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_DROPDOWN_BUTTON");
    Clay_ElementId dropdown_button_id = CLAY_SID(dropdown_button_id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Dropdown>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Dropdown>(id);

    // dropdown state configuration
    bool hovering_floating_container = Clay_PointerOver(floating_container_id);
    bool hovering_dropdown_button = Clay_PointerOver(dropdown_button_id);
    if ((IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        && !hovering_floating_container && !hovering_dropdown_button) {
        ctx->open = false;
    }

    CLAY(Clay_ElementDeclaration{ .id = dropdown_id }) {
        // dropdown button
        if (layout_components::button(id + "_DROPDOWN_BUTTON", "dropdown_button", "primary", layout_engine)) {
            ctx->open = !ctx->open;
        };
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
                        CLAY_STRING("Dropdown Children 1"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-"
                                                                                           "foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                    CLAY_TEXT(
                        CLAY_STRING("Dropdown Children 2"),
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
