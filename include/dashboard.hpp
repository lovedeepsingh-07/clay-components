#include "layout_engine.hpp"

namespace dashboard {
    void dashboard(LayoutEngine::LayoutEngine& layout_engine);
    namespace sidebar {
        void sidebar(LayoutEngine::LayoutEngine& layout_engine);
        void sidebar_dropdown(const std::string& id, bool hovering_curr_item, LayoutEngine::LayoutEngine& layout_engine);
        void header(LayoutEngine::LayoutEngine& layout_engine);
        void body(LayoutEngine::LayoutEngine& layout_engine);
        void footer(LayoutEngine::LayoutEngine& layout_engine);
    }
    namespace body {
        void navbar(LayoutEngine::LayoutEngine& layout_engine);
        bool navbar_button(const std::string& id, const std::string& text, LayoutEngine::LayoutEngine& layout_engine);
        void body(LayoutEngine::LayoutEngine& layout_engine);
    }
};
