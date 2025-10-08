#include "demo.hpp"
#include "js.hpp"
#include "layout_components.hpp"
#include "utils.hpp"

void demo::checkbox(const std::string& id, LayoutEngine::LayoutEngine& layout_engine) {
    Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string(id);
    Clay_ElementId checkbox_demo_id = CLAY_SID(id_cs);
    Clay_String code_block_id_cs =
        layout_engine.frame_arena.alloc_clay_string(id + "_code_block");
    Clay_ElementId code_block_id = CLAY_SID(code_block_id_cs);
    float corner_radius = layout_engine.get_radius();
    float display_width = 800;
    float display_height = 320;

    CLAY(Clay_ElementDeclaration{
        .id = checkbox_demo_id,
        .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                    .padding = { .left = 12, .right = 12, .top = 12 },
                    .childGap = 12,
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
        CLAY(Clay_ElementDeclaration{
            .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, 1000), .height = CLAY_SIZING_FIT() },
                        .childGap = 12,
                        .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
            CLAY_TEXT(
                CLAY_STRING("Checkbox"),
                CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                    .textColor = app_utils::raylib_to_clay(layout_engine.get_color("foreground")),
                    .fontId = 0,
                    .fontSize = 48,
                })
            );
            CLAY(Clay_ElementDeclaration{
                .layout = { .sizing = { .width = CLAY_SIZING_GROW(), .height = CLAY_SIZING_FIT() },
                            .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                            .layoutDirection = CLAY_TOP_TO_BOTTOM } }) {
                // ------ component display ------
                CLAY(Clay_ElementDeclaration{
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, display_width),
                                            .height = CLAY_SIZING_FIXED(display_height) },
                                .childGap = 8,
                                .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER } },
                    .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color("card")),
                    .cornerRadius = { corner_radius, corner_radius, 0, 0 },
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    layout_components::checkbox(id + "_component", layout_engine);
                }
                // ------ code block ------
                CLAY(Clay_ElementDeclaration{
                    .id = code_block_id,
                    .layout = { .sizing = { .width = CLAY_SIZING_GROW(0, display_width),
                                            .height = CLAY_SIZING_FIXED(display_height) },
                                .padding = CLAY_PADDING_ALL(8),
                                .layoutDirection = CLAY_TOP_TO_BOTTOM },
                    .backgroundColor = app_utils::raylib_to_clay(layout_engine.get_color("card")),
                    .cornerRadius = { 0, 0, corner_radius, corner_radius },
                    .clip = { .horizontal = true, .vertical = true, .childOffset = Clay_GetScrollOffset() },
                    .border = { .color = app_utils::raylib_to_clay(layout_engine.get_color("border")),
                                .width = { 1, 1, 1, 1, 0 } } }) {
                    std::string code_string = R"(Clay_String id_cs = layout_engine.frame_arena.alloc_clay_string("checkbox");
Clay_ElementId checkbox_id = CLAY_SID(id_cs);

layout_engine.add_element(id, std::make_unique<LayoutEngine::component_context::Checkbox>());
auto* ctx = layout_engine.get_element<LayoutEngine::component_context::Checkbox>(id);

// checkbox state configuration
bool hovering = Clay_PointerOver(checkbox_id);
if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
	ctx->checked = !ctx->checked;
}

// color values
Color checkbox_background_color =
	layout_engine.get_color(ctx->checked ? "foreground" : "background");
Color checkbox_foreground_color = layout_engine.get_color("background");
Color button_border_color = layout_engine.get_color("border");

CLAY(Clay_ElementDeclaration{
	.id = checkbox_id,
	.layout = { .sizing = { .width = CLAY_SIZING_FIT(24), .height = CLAY_SIZING_FIT(24) },
				.childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
				.layoutDirection = CLAY_TOP_TO_BOTTOM },
	.backgroundColor = app_utils::raylib_to_clay(checkbox_background_color),
	.cornerRadius = CLAY_CORNER_RADIUS(layout_engine.get_radius()),
	.border = { .color = app_utils::raylib_to_clay(button_border_color),
				.width = { 1, 1, 1, 1, 0 } } }) {
	if (ctx->checked) {
		CLAY_TEXT(
			CLAY_STRING("*"),
			CLAY_TEXT_CONFIG(Clay_TextElementConfig{
				.textColor = app_utils::raylib_to_clay(checkbox_foreground_color),
				.fontId = 0,
				.fontSize = 24,
			})
		);
	}
})";
                    Clay_String code_string_cs =
                        layout_engine.frame_arena.alloc_clay_string(code_string);
                    CLAY(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = CLAY_SIZING_FIT(0),
                                                .height = CLAY_SIZING_FIT(0) },
                                    .padding = CLAY_PADDING_ALL(8),
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .floating = { .attachPoints = { .element = CLAY_ATTACH_POINT_RIGHT_TOP,
                                                        .parent = CLAY_ATTACH_POINT_RIGHT_TOP },
                                      .pointerCaptureMode = CLAY_POINTER_CAPTURE_MODE_CAPTURE,
                                      .attachTo = CLAY_ATTACH_TO_PARENT } }) {
                        if (layout_components::button(id + "_copy_code_button", "copy", "primary", layout_engine)) {
#ifdef __EMSCRIPTEN__
                            js::copy_to_clipboard(code_string.c_str());
#else
                            printf("code copy button clicked\n");
#endif
                        }
                    }
                    CLAY_TEXT(
                        code_string_cs,
                        CLAY_TEXT_CONFIG(Clay_TextElementConfig{
                            .textColor = app_utils::raylib_to_clay(layout_engine.get_color("card-foreground")),
                            .fontId = 0,
                            .fontSize = 24,
                        })
                    );
                }
            }
        }
    }
}
