#include "clay_raylib.hpp"
#include "clayman.hpp"
#include "layout_components.hpp"

int main() {
    std::array<Font, 1> font_list;
    ClayMan clay(1280, 720, Raylib_MeasureText, font_list.data());

    Clay_Raylib_Initialize(clay.getWindowWidth(), clay.getWindowHeight(), "clay-components", FLAG_WINDOW_RESIZABLE);
    SetTargetFPS(90);

    font_list[0] =
        LoadFontEx("../deps/JetBrainsMonoNLNerdFontComplete-Regular.ttf", 48, nullptr, 300);
    SetTextureFilter(font_list[0].texture, TEXTURE_FILTER_BILINEAR);

    auto layout_engine = LayoutEngine::LayoutEngine{};
    layout_engine.setup();
    layout_engine.set_theme("dark");

    while (!WindowShouldClose()) {
        Vector2 mouse_pos = GetMousePosition();
        Vector2 scroll_delta = GetMouseWheelMoveV();
        clay.updateClayState(
            GetScreenWidth(), GetScreenHeight(), mouse_pos.x, mouse_pos.y,
            scroll_delta.x, scroll_delta.y, GetFrameTime(), IsMouseButtonDown(0)
        );

        clay.beginLayout();
        clay.openElement(Clay_ElementDeclaration{
            .id = clay.hashID("MAIN_CONTAINER"),
            .layout = {
                .sizing = { CLAY_SIZING_FIT(0), CLAY_SIZING_FIT(0) },
                .padding = CLAY_PADDING_ALL(4),
                .childGap = 2,
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
            } });
        {
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("DEMO_ACTION_BUTTON_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                if (layout_components::button()
                        .clay_man(clay)
                        .engine(layout_engine)
                        .id("theme_button")
                        .variant("primary")
                        .children_input("theme")
                        .build()) {
                    if (layout_engine.get_curr_theme() == "dark") {
                        layout_engine.set_theme("light");
                    } else {
                        layout_engine.set_theme("dark");
                    }
                }
                if (layout_components::button()
                        .clay_man(clay)
                        .engine(layout_engine)
                        .id("debug_button")
                        .variant("primary")
                        .children_input("debug")
                        .build()) {
                    Clay_SetDebugModeEnabled(!Clay_IsDebugModeEnabled());
                }
            }
            clay.closeElement();
            clay.openElement(Clay_ElementDeclaration{
                .id = clay.hashID("BUTTONS_DISPLAY_CONTAINER"),
                .layout = {
                    .sizing = { CLAY_SIZING_GROW(0), CLAY_SIZING_GROW(0) },
                    .padding = CLAY_PADDING_ALL(8),
                    .childGap = 8,
                    .layoutDirection = CLAY_LEFT_TO_RIGHT,
                } });
            {
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_primary")
                    .variant("primary")
                    .children_input("primary")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_secondary")
                    .variant("secondary")
                    .children_input("secondary")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_muted")
                    .variant("muted")
                    .children_input("muted")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_accent")
                    .variant("accent")
                    .children_input("accent")
                    .build();
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_destructive")
                    .variant("destructive")
                    .children_input("destructive")
                    .build();
                // NOTE: based on the current setup, I can only manage to add custom
                // styles for `layout` and `cornerRadius` because there are some
                // things that are difficult to get allow customization,
                // e.g I don't know how to allow user to add styles for when a button is hovered
                layout_components::button()
                    .clay_man(clay)
                    .engine(layout_engine)
                    .id("demo_button_custom")
                    .style(Clay_ElementDeclaration{
                        .layout = { .sizing = { .width = { 120 }, .height = { 20 } },
                                    .padding = CLAY_PADDING_ALL(2),
                                    .childAlignment = { .x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER },
                                    .layoutDirection = CLAY_TOP_TO_BOTTOM },
                        .cornerRadius = CLAY_CORNER_RADIUS(0),
                    })
                    .children_input("custom")
                    .build();
            }
            clay.closeElement();
        }
        clay.closeElement();

        Clay_RenderCommandArray render_commands = clay.endLayout();
        BeginDrawing();
        ClearBackground(layout_engine.get_color("background"));

        Clay_Raylib_Render(render_commands, font_list.data());

        EndDrawing();
    }
    return 0;
}
