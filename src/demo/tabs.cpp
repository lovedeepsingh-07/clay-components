#include "demo.hpp"
#include "utils.hpp"

void demo::tabs(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID("TABS_DEMO_CONTAINER"),
        .layout = {
            .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_GROW() },
            .padding = CLAY_PADDING_ALL(8),
            .childGap = 8,
            .layoutDirection = CLAY_TOP_TO_BOTTOM,
        } });
    {
        // default tabs
        layout_components::tabs_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tabs_default")
            .tab_list({ "home", "posts", "about" })
            .build();
        {
            auto* default_tabs_ctx =
                layout_engine.get_element<LayoutEngine::component_context::Tabs>("demo_tabs_default");
            layout_components::tabs_button_list()
                .clay_man(clay)
                .engine(layout_engine)
                .root_id("demo_tabs_default")
                .build();

            layout_components::tabs_content()
                .clay_man(clay)
                .engine(layout_engine)
                .root_id("demo_tabs_default")
                .build();
            if (default_tabs_ctx != nullptr) {
                for (int i = 0; i < default_tabs_ctx->tab_list.size(); i++) {
                    if (default_tabs_ctx->curr_tab == default_tabs_ctx->tab_list[i]) {
                        clay.textElement(
                            default_tabs_ctx->tab_list[i],
                            Clay_TextElementConfig{
                                .textColor =
                                    app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                                .fontId = 0,
                                .fontSize = 25,
                            }
                        );
                    }
                }
            }
            layout_components::close_tabs_content(clay);
        }
        layout_components::close_tabs_root(clay);
        // custom tabs
        layout_components::tabs_root()
            .clay_man(clay)
            .engine(layout_engine)
            .id("demo_tabs_custom")
            .tab_list({ "home", "posts", "about" })
            .build();
        {
            auto* custom_tabs_ctx =
                layout_engine.get_element<LayoutEngine::component_context::Tabs>("demo_tabs_custom");
            layout_components::tabs_button_list()
                .clay_man(clay)
                .engine(layout_engine)
                .root_id("demo_tabs_custom")
                .build();

            layout_components::tabs_content()
                .clay_man(clay)
                .engine(layout_engine)
                .root_id("demo_tabs_custom")
                .build();
            if (custom_tabs_ctx != nullptr) {
                for (int i = 0; i < custom_tabs_ctx->tab_list.size(); i++) {
                    if (custom_tabs_ctx->curr_tab == custom_tabs_ctx->tab_list[i]) {
                        clay.textElement(
                            custom_tabs_ctx->tab_list[i],
                            Clay_TextElementConfig{
                                .textColor =
                                    app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                                .fontId = 0,
                                .fontSize = 25,
                            }
                        );
                    }
                }
            }
            layout_components::close_tabs_content(clay);
        }
        layout_components::close_tabs_root(clay);
    }
    clay.closeElement();
}
