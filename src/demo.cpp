#include "demo.hpp"
#include "js.hpp"
#include "layout_components.hpp"

void demo::demo(LayoutEngine::LayoutEngine& layout_engine){ CLAY(Clay_ElementDeclaration{
    // ------ main container ------
    .id = CLAY_ID("main_container"),
    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0) },
                .childGap = 8,
                .layoutDirection = CLAY_TOP_TO_BOTTOM

    } }
){ // ------ header container ------
   CLAY(Clay_ElementDeclaration{
       .id = CLAY_ID("header_container"),
       .layout = { .sizing = { .width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_FIT(0) },
                   .padding = CLAY_PADDING_ALL(8),
                   .childAlignment = { .x = CLAY_ALIGN_X_RIGHT, .y = CLAY_ALIGN_Y_CENTER } } }
   ){ // github repository button
      if (layout_components::button("github_button", "github", layout_engine)){
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
        if (layout_components::button("button", "button", layout_engine)) {
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
}
}
}
;
