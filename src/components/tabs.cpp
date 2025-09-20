#include "layout_components.hpp"
#include "utils.hpp"

layout_components::_tabs_root_builder&
layout_components::_tabs_root_builder::tab_list(std::vector<std::string> tab_list) {
    this->_tab_list = tab_list;
    return *this;
};
void layout_components::_tabs_root_builder::build() {
    auto tab_ctx = LayoutEngine::component_context::Tabs{};
    tab_ctx.tab_list = _tab_list;
    tab_ctx.curr_tab = _tab_list[0];

    _engine->add_element(_id, std::make_unique<LayoutEngine::component_context::Tabs>(tab_ctx));
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Tabs>(_id);

    // default style
    auto tabs_root_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_id),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1280),
                                .height = CLAY_SIZING_GROW(0, 720) },
                    .padding = CLAY_PADDING_ALL(12),
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
    };

    // apply custom styles
    if (_custom_styled) {
        tabs_root_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            tabs_root_style.backgroundColor = _style.backgroundColor;
        }
        tabs_root_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            tabs_root_style.border.color = _style.border.color;
        }
        tabs_root_style.border.width = _style.border.width;
    }

    _clay->openElement(tabs_root_style);
}
layout_components::_tabs_root_builder layout_components::tabs_root() {
    return _tabs_root_builder{};
};
void layout_components::close_tabs_root(ClayMan& clay) {
    clay.closeElement();
}

layout_components::_tabs_button_list_builder&
layout_components::_tabs_button_list_builder::root_id(const std::string& root_id) {
    this->_root_id = root_id;
    return *this;
}
void layout_components::_tabs_button_list_builder::build() {
    auto* ctx = _engine->get_element<LayoutEngine::component_context::Tabs>(_root_id);
    if (ctx == nullptr) {
        return;
    }

    // default button list style
    auto button_list_container_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_root_id + "_TABS_BUTTON_LIST_CONTAINER"),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 500), .height = CLAY_SIZING_FIT() },
                    .padding = CLAY_PADDING_ALL(6),
                    // .childGap = 8,
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_LEFT_TO_RIGHT },
        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
        .border = { .color =
                        app_utils::raylib_to_clay(_engine->get_color("border")),
                    .width = { 1, 1, 1, 1, 0 } }
    };

    // apply custom style to button list
    if (_custom_styled) {
        button_list_container_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            button_list_container_style.backgroundColor = _style.backgroundColor;
        }
        button_list_container_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            button_list_container_style.border.color = _style.border.color;
        }
        button_list_container_style.border.width = _style.border.width;
    }

    _clay->openElement(button_list_container_style);
    {
        std::string next_tab = ctx->curr_tab;
        for (int i = 0; i < ctx->tab_list.size(); i++) {
            // FIXME: when writing this comment, there is no way to add custom
            // styles for these buttons because of allowing user to change the style when the current button is selected
            if (layout_components::button()
                    .clay_man(*_clay)
                    .engine(*_engine)
                    .id(_root_id + "_TABS_BUTTON_" + ctx->tab_list[i])
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_GROW(120),
                                                .height = CLAY_SIZING_GROW(20) },
                                    .padding = { .left = 8, .right = 8, .top = 4, .bottom = 4 },
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .backgroundColor = app_utils::raylib_to_clay(_engine->get_color(
                            (ctx != nullptr && ctx->curr_tab == ctx->tab_list[i]) ? "primary" : "card"
                        )),
                        .cornerRadius = CLAY_CORNER_RADIUS(_engine->get_radius()),
                    })
                    .build()) {
                next_tab = ctx->tab_list[i];
            }
            {
                _clay->textElement(
                    ctx->tab_list[i],
                    Clay_TextElementConfig{
                        .textColor = app_utils::raylib_to_clay(_engine->get_color(
                            (ctx != nullptr && ctx->curr_tab == ctx->tab_list[i]) ? "primary-foreground" : "card-foreground"
                        )),
                        .fontId = 0,
                        .fontSize = 24,
                    }
                );
            }
            layout_components::close_button(*_clay);
        }
        if (next_tab != ctx->curr_tab) {
            ctx->curr_tab = next_tab;
        }
    }
    _clay->closeElement();
}
layout_components::_tabs_button_list_builder layout_components::tabs_button_list() {
    return _tabs_button_list_builder{};
};

layout_components::_tabs_content_builder&
layout_components::_tabs_content_builder::root_id(const std::string& root_id) {
    this->_root_id = root_id;
    return *this;
}
void layout_components::_tabs_content_builder::build() {
    // default container style
    auto content_container_style = Clay_ElementDeclaration{
        .id = _clay->hashID(_root_id + "_TABS_CONTENT_CONTAINER"),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_TOP },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
    };

    // apply custom styles
    if (_custom_styled) {
        content_container_style.layout = _style.layout;
        if (app_utils::is_color_set(_style.backgroundColor)) {
            content_container_style.backgroundColor = _style.backgroundColor;
        }
        content_container_style.cornerRadius = _style.cornerRadius;
        if (app_utils::is_color_set(_style.border.color)) {
            content_container_style.border.color = _style.border.color;
        }
        content_container_style.border.width = _style.border.width;
    }

    _clay->openElement(content_container_style);
}
layout_components::_tabs_content_builder layout_components::tabs_content() {
    return _tabs_content_builder{};
};
void layout_components::close_tabs_content(ClayMan& clay) {
    clay.closeElement();
}
