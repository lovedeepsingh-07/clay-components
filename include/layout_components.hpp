#include "layout_engine.hpp"

namespace layout_components {
    bool button(const std::string& id, const std::string& text, LayoutEngine::LayoutEngine& layout_engine);
    void checkbox(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void input(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void tooltip(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void dropdown(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void modal(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
    void tabs(const std::string& id, LayoutEngine::LayoutEngine& layout_engine);
};
