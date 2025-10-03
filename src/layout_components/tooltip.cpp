#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"
#include <clay.h>
#include <cstring>

void layout_components::tooltip(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    auto id_cs = Clay_String{
        .length = (std::int32_t)id.size(),
        .chars = layout_engine.frame_arena.alloc_string(id),
    };
    Clay_ElementId tooltip_id = CLAY_SID(id_cs);

    layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Tooltip>());
    auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Tooltip>(id);

    // state configuration
    bool hovering = Clay_PointerOver(tooltip_id);
    std::string direction = "down";
    Clay_FloatingAttachPointType element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
    Clay_FloatingAttachPointType parent_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;
    auto floating_offset = Clay_Vector2{ 0, 6 };
    if (direction == "top") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_BOTTOM;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        floating_offset = { 0, -6 };
    }
    if (direction == "right") {
        element_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
        floating_offset = { 6, 0 };
    }
    if (direction == "left") {
        element_attach_point = CLAY_ATTACH_POINT_RIGHT_TOP;
        parent_attach_point = CLAY_ATTACH_POINT_LEFT_TOP;
        floating_offset = { -6, 0 };
    }

    // color values
    Color tooltip_background_color = layout_engine.get_color("card");
    Color tooltip_foreground_color = layout_engine.get_color("card-foreground");
    Color tooltip_border_color = layout_engine.get_color("border");

    CLAY(Clay_ElementDeclaration{
        .id = tooltip_id,
        .layout = { .sizing = { .width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
    }) {
        // acutal content
        if (layout_components::button("tooltip_button", layout_engine)) {
#ifdef __EMSCRIPTEN__
            js::alert("tooltip button clicked!");
#else
            printf("tooltip button clicked!");
#endif
        }
        if (hovering) {
            // floating container
            CLAY(Clay_ElementDeclaration{
                .id = CLAY_ID_LOCAL("FLOATING_CONTAINER"),
                .floating = { .offset = floating_offset,
                              .attachPoints = { .element = element_attach_point, .parent = parent_attach_point },
                              .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_PASSTHROUGH,
                              .attachTo = CLAY_ATTACH_TO_PARENT } }) {
                // content container
                CLAY(Clay_ElementDeclaration{
                    .id = CLAY_ID_LOCAL("CONTENT_CONTAINER"),
                    .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                            .height = CLAY_SIZING_FIT(37) },
                                .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                                .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(tooltip_background_color),
                    .cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
                    .border = { .color = app_utils::raylib_to_clay(tooltip_border_color),
                                .width = { 1, 1, 1, 1, 0 } },
                }) {
                    // tooltip content
                    CLAY_TEXT(
                        CLAY_STRING("tooltip"),
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(tooltip_foreground_color),
                            .fontId = 0,
                            .fontSize = 25,
                        })
                    );
                }
            }
        }
    }
}
