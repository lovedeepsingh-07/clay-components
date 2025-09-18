// #include "demo.hpp"
// #include "utils.hpp"

// FIXME: instead of using `value()` to bind to a string, we have to store the value of input inside the input context

// void demo::input(ClayMan& clay, LayoutEngine::LayoutEngine& layout_engine) {
//     // input demo container
//     clay.openElement(Clay_ElementDeclaration{
//         .id = clay.hashID("INPUT_DEMO_CONTAINER"),
//         .layout = {
//             .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
//             .padding = CLAY_PADDING_ALL(8),
//             .childGap = 8,
//             .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
//             .layoutDirection = CLAY_LEFT_TO_RIGHT,
//         } });
//     {
//         // default input
//         layout_components::input()
//             .clay_man(clay)
//             .engine(layout_engine)
//             .id("demo_input_default")
//             .placeholder("input_box")
//             .value(input_default_text)
//             .build();
//         clay.textElement(
//             "input_default_text: " + input_default_text,
//             Clay_TextElementConfig{
//                 .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
//                 .fontId = 0,
//                 .fontSize = 25,
//             }
//         );
//         // custom input
//         auto* custom_input_ctx =
//             layout_engine.get_element<LayoutEngine::component_context::Input>("demo_input_custom");
//         layout_components::input()
//             .clay_man(clay)
//             .engine(layout_engine)
//             .id("demo_input_custom")
//             .style(Clay_ElementDeclaration{
//                 .layout = { .sizing = { .width = CLAY_SIZING_FIT(160),
//                                         .height = CLAY_SIZING_FIT(37) },
//                             .padding = { .left = 8, .right = 8, .top = 6, .bottom = 6 },
//                             .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_CENTER },
//                             .layoutDirection = CLAY_TOP_TO_BOTTOM },
//                 .backgroundColor = app_utils::raylib_to_clay(MAROON),
//                 .cornerRadius = CLAY_CORNER_RADIUS(0),
//                 .border = { .color = app_utils::raylib_to_clay(PURPLE),
//                             .width =
//                                 (custom_input_ctx != nullptr && custom_input_ctx->focused
//                                      ? Clay_BorderWidth{ 4, 4, 4, 4, 0 }
//                                      : Clay_BorderWidth{ 2, 2, 2, 2, 0 }) } })
//             .placeholder("custom_input")
//             .value(input_custom_text)
//             .build();
//         clay.textElement(
//             "input_custom_text: "
//                 + (custom_input_ctx == nullptr ? "" : custom_input_ctx->value),
//             Clay_TextElementConfig{
//                 .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
//                 .fontId = 0,
//                 .fontSize = 25,
//             }
//         );
//     }
//     clay.closeElement();
// }
