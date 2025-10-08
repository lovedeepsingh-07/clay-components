#include "layout_engine.hpp"

namespace dashboard {
    void dashboard(LayoutEngine::LayoutEngine& layout_engine);
    namespace sidebar {
        void sidebar(LayoutEngine::LayoutEngine& layout_engine);
        void header(LayoutEngine::LayoutEngine& layout_engine);
        void body(LayoutEngine::LayoutEngine& layout_engine);
        void footer(LayoutEngine::LayoutEngine& layout_engine);
    }
    namespace body {
        void navbar(LayoutEngine::LayoutEngine& layout_engine);
        void body(LayoutEngine::LayoutEngine& layout_engine);
    }
};
