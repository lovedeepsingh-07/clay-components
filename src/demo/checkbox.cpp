#include "demo.hpp"
#include "utils.hpp"

void demo::checkbox(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("CHECKBOX_DEMO_CONTAINER"),
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
        } });
    {
        // default checkbox
        layout_components::checkbox()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_checkbox_default")
            .build();
        auto* checkbox_default_ctx =
            layout_engine.get_element<LayoutEngine::component_context::Checkbox>("demo_checkbox_default");
        clay.textElement(
            "default_checkbox: "
                + std::string(
                    (checkbox_default_ctx != nullptr && checkbox_default_ctx->checked) ? "checked" : "not_checked"
                ),
            Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                .fontId = 0,
                .fontSize = 25,
            }
        );
        // custom checkbox
        auto* custom_checkbox_ctx =
            layout_engine.get_element<LayoutEngine::component_context::Checkbox>("demo_checkbox_custom");
        layout_components::checkbox()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_checkbox_custom")
            .style(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(24), .height = CLAY_SIZING_FIT(24) },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_to_clay(
                    (custom_checkbox_ctx != nullptr && custom_checkbox_ctx->checked) ? PURPLE : MAROON
                ),
                .cornerRadius = CLAY_CORNER_RADIUS(0),
                .border = { .color = app_utils::raylib_to_clay(
                                (custom_checkbox_ctx != nullptr
                                 && custom_checkbox_ctx->checked)
                                    ? MAROON
                                    : PURPLE
                            ),
                            .width =
                                (custom_checkbox_ctx != nullptr
                                         && custom_checkbox_ctx->checked
                                     ? Clay_BorderWidth{ 4, 4, 4, 4, 0 }
                                     : Clay_BorderWidth{ 2, 2, 2, 2, 0 }) } })
            .build();
        clay.textElement(
            "custom_checkbox: "
                + std::string(
                    (custom_checkbox_ctx != nullptr && custom_checkbox_ctx->checked) ? "checked" : "not_checked"
                ),
            Clay_TextElementConfig{
                .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                .fontId = 0,
                .fontSize = 25,
            }
        );
    }
    clay.closeElement();
}
