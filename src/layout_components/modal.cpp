#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::modal(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId modal_id = CLAY_SID(id_cs);

    Clay_String floating_container_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_FLOATING_CONTAINER");
    Clay_ElementId floating_container_id = CLAY_SID(floating_container_id_cs);

    Clay_String content_container_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_CONTENT_CONTAINER");
    Clay_ElementId content_container_id = CLAY_SID(content_container_id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Modal>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Modal>(id);

    // modal state configuration
    bool hovering_floating_container = Clay_PointerOver(floating_container_id);
    bool hovering_content_container = Clay_PointerOver(content_container_id);
    if (hovering_floating_container && !hovering_content_container
        && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
        && ctx->open) {
        ctx->open = false;
    }

    // modal button
    if (layout_components::button(id + "_button", "modal_button", "primary", layout_engine)) {
        ctx->open = true;
    }

    // root container
    CLAY(Clay_ElementDeclaration{ .id = modal_id }) {
        // floating container
        if (ctx->open) {
            CLAY(Clay_ElementDeclaration{
                .id = floating_container_id,
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
                .backgroundColor = app_utils::raylib_to_clay(ColorAlpha(BLACK, 0.5)),
                .floating = { .zIndex = 90,
                              .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                              .attachTo = CLAY_ATTACH_TO_ROOT } }) {
                // content container
                CLAY(Clay_ElementDeclaration{
                    .id = content_container_id,
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 480),
                                            .height = CLAY_SIZING_GROW(0, 270) },
                                .padding = { .left = 10, .right = 10, .top = 10, .bottom = 10 },
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color("card")),
                    .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } },
                }) {
                    // modal content
                    CLAY_TEXT(
                        CLAY_STRING("modal_text"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                            .fontId = 0,
                            .fontSize = 20,
                        })
                    );
                }
            }
        }
    }
}
