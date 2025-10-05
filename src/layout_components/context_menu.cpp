#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::context_menu(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId context_menu_id = CLAY_SID(id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::ContextMenu>());
    auto* ctx =
        layout_engine.get_element<LayoutEngine::component_context::ContextMenu>(id);

    // context menu state configuration
    bool hovering = Clay_PointerOver(context_menu_id);
    if (!hovering && IsMouseButtonReleased(MOUSE_BUTTON_RIGHT)) {
        ctx->open = true;
        ctx->spawn_pos = GetMousePosition();
    }
    if (!hovering
        && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)
            || (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)))) {
        ctx->open = false;
    }

    if (ctx->open) {
        CLAY(Clay_ElementDeclaration{
            .id = context_menu_id,
            .layout = { .sizing = { .width = CLAY_SIZING_FIT(200), .height = CLAY_SIZING_FIT(160) },
                        .padding = CLAY_PADDING_ALL(8),
                        .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP } },
            .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color("card")),
            .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
            .floating = { .offset = { .x = ctx->spawn_pos.x, .y = ctx->spawn_pos.y },
                          .zIndex = 100,
                          .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                          .attachTo = CLAY_ATTACH_TO_ROOT },
            .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                        .width = { 1, 1, 1, 1, 0 } },
        }) {
            Clay_String context_debug_button =
                layout_engine.frame_arena.alloc_clay_string(id + "_debug_button");
            Clay_ElementId context_debug_button_id = CLAY_SID(context_debug_button);
            bool hovering_debug_button = Clay_PointerOver(context_debug_button_id);
            if (hovering_debug_button && IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
                Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
                ctx->open = false;
            }
            CLAY(Clay_ElementDeclaration{
                .id = context_debug_button_id,
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                            .padding = { .left = 8, .right = 8, .top = 4, .bottom = 4 } },
                .backgroundColor = app_utils::raylib_to_clay(
                    layout_engine.get_color(hovering_debug_button ? "primary" : "card")
                ),
                .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()) }) {
                CLAY_TEXT(
                    CLAY_STRING("Debug Mode"),
                    CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(layout_engine.get_color(
                            hovering_debug_button ? "primary-foreground" : "card-foreground"
                        )),
                        .fontId = 0,
                        .fontSize = 24,
                    })
                );
            }
        }
    }
}
