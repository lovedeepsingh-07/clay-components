#include "ui_engine.hpp"

void UIEngine::UIEngine::setup() {
    this->add_theme("light", UITheme{ .colors = {
			{ "background", { 242, 241, 242, 255 } }, 
			{ "foreground", { 2, 2, 2, 255 } }, 
			{ "card", { 230, 228, 229, 255 } }, 
			{ "card-foreground", { 26, 24, 25, 255 } }, 
			{ "popover", { 242, 241, 242, 255 } }, 
			{ "popover-foreground", { 4, 0, 1, 255 } }, 
			{ "primary", { 67, 49, 53, 255 } }, 
			{ "primary-foreground", { 255, 255, 255, 255 } }, 
			{ "secondary", { 186, 170, 174, 255 } }, 
			{ "secondary-foreground", { 0, 0, 0, 0 } }, 
			{ "muted", { 220, 212, 219, 255 } }, 
			{ "muted-foreground", { 91, 87, 88, 255 } }, 
			{ "accent", { 209, 198, 207, 255 } }, 
			{ "accent-foreground", { 26, 24, 25, 255 } }, 
			{ "destructive", { 114, 38, 38, 255 } }, 
			{ "destructive-foreground", { 230, 228, 229, 255 } }, 
			{ "border", { 152, 102, 113, 255 } }, 
			{ "input", { 55, 36, 40, 255 } }, 
			{ "ring", { 67, 49, 53, 255 } }, 
		}, 
		.radius = 5.0F 
	});
    this->add_theme("dark", UITheme{ .colors = {
			{"background", {14, 11, 12, 255}},
			{"foreground", {230, 228, 229, 255}},
			{"card", {2, 2, 2, 255}},
			{"card-foreground", {230, 228, 229, 255}},
			{"popover", {14, 11, 12, 255}},
			{"popover-foreground", {230, 228, 229, 255}},
			{"primary", {67, 49, 53, 255}},
			{"primary-foreground", {255, 255, 255, 255}},
			{"secondary", {28, 22, 24, 255}},
			{"secondary-foreground", {255, 255, 255, 255}},
			{"muted", {42, 34, 40, 255}},
			{"muted-foreground", {155, 150, 151, 255}},
			{"accent", {42, 34, 40, 255}},
			{"accent-foreground", {230, 228, 229, 255}},
			{"destructive", {114, 38, 38, 255}},
			{"destructive-foreground", {230, 228, 229, 255}},
			{"border", {55, 36, 40, 255}},
			{"input", {55, 36, 40, 255}},
			{"ring", {67, 49, 53, 255}},
		}, 
		.radius = 5.0F 
	});
}

void UIEngine::UIEngine::add_theme(const std::string& theme_id, UITheme theme) {
    if (m_themes.find(theme_id) != m_themes.end()) {
        printf("WARN: theme with this ID already exists, doing "
               "nothing\n");
        return;
    }
    m_themes.emplace(theme_id, theme);
}
void UIEngine::UIEngine::set_theme(const std::string& theme_id) {
    if (m_curr_theme_id != theme_id) {
        m_curr_theme_id = theme_id;
    }
}
std::string UIEngine::UIEngine::get_curr_theme() {
    return m_curr_theme_id;
}
Color UIEngine::UIEngine::get_color(const std::string& color_id) {
    return m_themes.at(m_curr_theme_id).colors.at(color_id);
};
float UIEngine::UIEngine::get_radius() {
    return m_themes.at(m_curr_theme_id).radius;
}

void UIEngine::UIEngine::add_element(
    const std::string& element_id, std::unique_ptr<element_context::Element> element
) {
    if (m_element_map.find(element_id) != m_element_map.end()) {
        return; // element with this ID already exists
    }
    m_element_map.emplace(element_id, std::move(element));
}
void UIEngine::UIEngine::clear_engine() {
    if (m_element_map.size() != 0) {
        m_element_map.clear();
    }
}
