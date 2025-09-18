#include "demo.hpp"
#include "utils.hpp"

void demo::button(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("BUTTONS_DEMO_CONTAINER"),
        .layout = {
            .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
            .layoutDirection = CLAY_LEFT_TO_RIGHT,
        } });
    {
        // primary button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_primary")
            .variant("primary")
            .text("primary")
            .build();
        // secondary button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_secondary")
            .variant("secondary")
            .text("secondary")
            .build();
        // muted button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_muted")
            .variant("muted")
            .text("muted")
            .build();
        // accent button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_accent")
            .variant("accent")
            .text("accent")
            .build();
        // destructive button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_destructive")
            .variant("destructive")
            .text("destructive")
            .build();
        // custom button
        layout_components::button()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_button_custom")
            .style(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_FIT(120),
                                        .height = CLAY_SIZING_FIT(20) },
                            .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM },
                .backgroundColor = app_utils::raylib_to_clay(MAROON),
                .cornerRadius = CLAY_CORNER_RADIUS(0),
                .border = { .color = app_utils::raylib_to_clay(PURPLE),
                            .width = { 2, 2, 2, 2, 0 } } })
            .build();
        {
            clay.textElement(
                "custom",
                Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(YELLOW),
                    .fontId = 0,
                    .fontSize = 25,
                }
            );
        }
        layout_components::close_button(clay);
    }
    clay.closeElement();
}
