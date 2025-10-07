#include "layout_engine.hpp"

// NOTE: a little info about z-index in these elements
// btw, if you don't know, elements with higher z-index will appear over the
// elements with lower z-index
// - context_menu: 100
// - modal: 90
// - dropdown: 80

namespace layout_components {
    bool button(const std::string& id, const std::string& text, const std::string& variant, LayoutEngine::LayoutEngine& layout_engine);
    void checkbox(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void input(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void tooltip(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void dropdown(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void modal(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void tabs(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void code_block(const std::string& id, const std::string& text, LayoutEngine::LayoutEngine& layout_engine);
    void context_menu(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);

    // components used in the actual website (they mostly don't require their own context in the LayoutEngine)
    void navbar(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void hero(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void introduction(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
};
