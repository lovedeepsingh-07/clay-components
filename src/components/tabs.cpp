#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::_tabs_root_builder::build() {
    auto tab_ctx = LayoutEngine::component_context::Tabs{};
    tab_ctx.curr_tab = "home";
    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Tabs>(tab_ctx));
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Tabs>(_id);

    // main container
    _clay->openElement(Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(200, 1280),
                                .height = CLAY_SIZING_GROW(100, 720) },
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = app_utils::raylib_to_clay(_engine->get_color("card")),
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color =
                        app_utils::raylib_to_clay(_engine->get_color("border")),
                    .width = { 1, 1, 1, 1, 0 } } });
    {
        // tab button list
        _clay->openElement(Clay_ElementDeclaration{
            .id = _clay->hashID(_id + "_TABS_LIST_CONTAINER"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                        .padding = CLAY_PADDING_ALL(12),
                        .childGap = 8,
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_LEFT_TO_RIGHT },
        });
        {
            std::string next_tab = ctx->curr_tab;
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW() } } }) {} // filler
            if (layout_components::button()
                    .clay_man(*_clay)
                    .engine(*_engine)
                    .id(_id + "TAB_BUTTON_home")
                    .variant("primary")
                    .text("home")
                    .build()) {
                next_tab = "home";
            }
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW() } } }) {} // filler
            if (layout_components::button()
                    .clay_man(*_clay)
                    .engine(*_engine)
                    .id(_id + "TAB_BUTTON_posts")
                    .variant("primary")
                    .text("posts")
                    .build()) {
                next_tab = "posts";
            }
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW() } } }) {} // filler
            if (layout_components::button()
                    .clay_man(*_clay)
                    .engine(*_engine)
                    .id(_id + "TAB_BUTTON_about")
                    .variant("primary")
                    .text("about")
                    .build()) {
                next_tab = "about";
            }
            if (next_tab != ctx->curr_tab) {
                ctx->curr_tab = next_tab;
            }
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW() } } }) {} // filler
        }
        _clay->closeElement();
        // tab content
        _clay->openElement(Clay_ElementDeclaration{
            .id = _clay->hashID(_id + "_TABS_CONTENT_CONTAINER"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                        .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                        .layoutDirection = CLAY_TOP_TO_BOTTOM },
        });
        {
            if (ctx != nullptr && ctx->curr_tab == "home") {
                _clay->textElement(
                    "home",
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                        .fontId = 0,
                        .fontSize = 24,
                    }
                );
            }
            if (ctx != nullptr && ctx->curr_tab == "posts") {
                _clay->textElement(
                    "posts",
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                        .fontId = 0,
                        .fontSize = 24,
                    }
                );
            }
            if (ctx != nullptr && ctx->curr_tab == "about") {
                _clay->textElement(
                    "about",
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(_engine->get_color("card-foreground")),
                        .fontId = 0,
                        .fontSize = 24,
                    }
                );
            }
        }
        _clay->closeElement();
    }
    _clay->closeElement();
}
layout_components::_tabs_root_builder layout_components::tabs_root() {
    return _tabs_root_builder{};
};
