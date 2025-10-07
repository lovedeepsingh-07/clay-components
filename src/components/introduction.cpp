#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void layout_components::introduction(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId introduction_id = CLAY_SID(id_cs);

    CLAY(Clay_ElementDeclaration{
        .id = introduction_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .left = 12, .right = 12 },
                    .childGap = 12,
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1000), .height = CLAY_SIZING_FIT() },
                        .childGap = 12,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            CLAY_TEXT(
                CLAY_STRING("Introduction"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 48,
                })
            );
            CLAY_TEXT(
                CLAY_STRING("Why would I do this? I was bored."),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
            CLAY_TEXT(
                CLAY_STRING(R"(How does this work? Basically, it's all the magic of web assembly. I use a library called "Clay" for the layout, raylib for rendering, and I just compile the project to a WASM binary and render it on the web in a canvas. Consider checking out those libraries, they are awesome.)"
                ),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
            CLAY_TEXT(
                CLAY_STRING(R"(Most of the stuff that you see on this website is only possible because of the Clay library. It is a simple layout library for C/C++ which is incredibly efficient. For rendering this website I am using raylib, but that is only temporary. Clay allows us to use even the HTML itself to render on the web without having to rely on canvas altogether. But, at the time of writing this, I don't have any idea on how to do that, until I figure out how to use Clay's HTML or the simple canvas renderer, this website will be using raylib for the heavy lifting. NOTE: because I am using raylib, some of the components will contain some raylib-specific code.)"
                ),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
            CLAY_TEXT(
                CLAY_STRING(R"(Before we get started, there are a few things that are important to discuss. I am using C++ to write but this same website can also be written in C. Also, there are 2 extra things that this website is using. First one is a "LayoutEngine", it is just a class that stores theme data, and some context about each component, like a button is pressed, a modal or a dropdown is open etc etc. The other thing is a "FrameArena" which is a memory arena that I use to make temporary allocations, these allocations are only valid till the frame and when the frame is rendered, these allocations are also freed up.)"
                ),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 24,
                })
            );
        }
    }
}
