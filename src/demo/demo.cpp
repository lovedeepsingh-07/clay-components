#include "demo.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void demo::demo(LayoutEngine::LayoutEngine& layout_engine) {
    CLAY(Clay_ElementDeclaration{
        // ------ main container ------
        .id = CLAY_ID("main_container"),
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                    .childGap = 10,
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        // ------ header container ------
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("header_container"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                        .padding = CLAY_PADDING_ALL(8),
                        .childGap = 8,
                        .childAlignment = { .x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_CENTER } } }) {
            if (layout_components::button("theme_button", "theme", "primary", layout_engine)) {
                if (layout_engine.get_curr_theme() == "dark") {
                    layout_engine.set_theme("light");
                } else {
                    layout_engine.set_theme("dark");
                }
            }
            if (layout_components::button("github_button", "github", "primary", layout_engine)) {
#ifdef __EMSCRIPTEN__
                js::open_link("https://github.com/lovedeepsingh-07/"
                              "clay-components");
#else
                printf("github button clicked!\n");
#endif
            }
        }
        // ------ content container ------
        CLAY(Clay_ElementDeclaration{
            .id = CLAY_ID("content_container"),
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                        .childGap = 8,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            // button elements
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                            .childGap = 8 } }) {
                if (layout_components::button("button", "button", "primary", layout_engine)) {
#ifdef __EMSCRIPTEN__
                    js::alert("button clicked!");
#else
                    printf("button clicked!\n");
#endif
                }
                layout_components::tooltip("tooltip", layout_engine);
                layout_components::dropdown("dropdown", layout_engine);
                layout_components::modal("modal", layout_engine);
            }
            // input elements
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                            .childGap = 8 } }) {
                layout_components::checkbox("checkbox", layout_engine);
                layout_components::input("input", layout_engine);
            }
            layout_components::tabs("tabs", layout_engine);
            std::string code_block_text = R"(#include <iostream>
int main() {
    std::cout << "Hello World" << '\n';
    return 0;
})";
            layout_components::code_block("code_block", code_block_text, layout_engine);
        }

        // right-click context-menu
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 320),
                                    .height = CLAY_SIZING_FIT(0) } } }) {
            CLAY_TEXT(
                CLAY_STRING("NOTE: right-click anywhere to open the "
                            "context-menu, "
                            "you can find the debug mode there"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
            layout_components::context_menu("main_context_menu", layout_engine);
        }
    }
}
