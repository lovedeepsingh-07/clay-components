#include "clayman.hpp"
#include "layout_engine.hpp"
#include <functional>
#include <string>
#include <variant>

namespace layout_components {
    class _button_builder {
      private:
        ClayMan* _clay = nullptr;
        LayoutEngine::LayoutEngine* _engine = nullptr;
        std::string _id;
        std::string _variant{ "primary" };
        bool _custom_styled{ false };
        Clay_ElementDeclaration _style;
        std::variant<std::string, std::function<void()>> _children_input;

      public:
        _button_builder& clay_man(ClayMan& clay);
        _button_builder& engine(LayoutEngine::LayoutEngine& engine);
        _button_builder& id(const std::string& id);
        _button_builder& variant(const std::string& variant);
        _button_builder& style(Clay_ElementDeclaration style);
        _button_builder&
        children_input(std::variant<std::string, std::function<void()>> children_input);
        bool build();
    };
    _button_builder button();
};
