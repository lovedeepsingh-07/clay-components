#include "ui_engine.hpp"
#include "utils.hpp"

bool UIEngine::elements::button(
    ClayMan& clay,
    UIEngine& UI_engine,
    const std::string& element_id,
    const std::variant<std::string, std::function<void()>> children_input
) {
    UI_engine.add_element(element_id, std::make_unique<element_context::Button>());
    auto* ctx = UI_engine.get_element<element_context::Button>(element_id);
    bool button_clicked = false;

    clay.openElement(Clay_ElementDeclaration{
        .id = clay.hashID(element_id),
        .layout = { .sizing = { .width = { 120 }, .height = { 20 } },
                    .padding = CLAY_PADDING_ALL(2),
                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
        .backgroundColor = game_utils::raylib_to_clay(
            ColorAlpha(UI_engine.get_color("primary"), ((ctx->hovered || ctx->pressed) ? 0.85 : 1))
        ),
        .cornerRadius = CLAY_CORNER_RADIUS(UI_engine.get_radius()),
        .border = { .color = game_utils::raylib_to_clay(ColorAlpha(
                        UI_engine.get_color("border"), ((ctx->hovered || ctx->pressed) ? 0.85 : 1)
                    )),
                    .width = { 1, 1, 1, 1, 0 } } });
    {
        bool hovering = clay.pointerOver(element_id);

        if (hovering && !ctx->hovered) {
            ctx->hovered = true;
        }
        if (!hovering && ctx->hovered) {
            ctx->hovered = false;
        }
        if (hovering && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            ctx->pressed = true;
        }
        if (hovering && IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ctx->pressed) {
            button_clicked = true;
        }
        if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && ctx->pressed) {
            ctx->pressed = false;
        }

        std::visit(
            [&](auto&& arg) {
                using curr_type = std::decay_t<decltype(arg)>;
                if constexpr (std::is_same_v<curr_type, std::string>) {
                    // text element
                    clay.textElement(
                        arg,
                        Clay_TextElementConfig{
                            .textColor = game_utils::raylib_to_clay(UI_engine.get_color("primary-foreground")),
                            .fontId = 0,
                            .fontSize = 25,
                        }
                    );
                }
                if constexpr (std::is_same_v<curr_type, std::function<void()>>) {
                    // children element
                    arg();
                }
            },
            children_input
        );
    }
    clay.closeElement();

    return button_clicked;
}
