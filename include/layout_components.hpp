#pragma once

#include "clayman.hpp"
#include "layout_engine.hpp"
#include <string>

namespace layout_components {
    // builder for components
    template <typename BuilderType>
    class Builder {
      protected:
        ClayMan* _clay = nullptr;
        LayoutEngine::LayoutEngine* _engine = nullptr;
        std::string _id;

      public:
        BuilderType& clay_man(ClayMan& clay) {
            this->_clay = &clay;
            return static_cast<BuilderType&>(*this);
        };
        BuilderType& engine(LayoutEngine::LayoutEngine& engine) {
            this->_engine = &engine;
            return static_cast<BuilderType&>(*this);
        };
        BuilderType& id(const std::string& id) {
            this->_id = id;
            return static_cast<BuilderType&>(*this);
        };
    };

    // button
    class _button_builder : public Builder<_button_builder> {
      private:
        std::string _variant{ "primary" };
        bool _custom_styled{ false };
        Clay_ElementDeclaration _style;
        bool _text_button{ false };
        std::string _text;

      public:
        _button_builder& variant(const std::string& variant);
        _button_builder& style(Clay_ElementDeclaration style);
        _button_builder& text(const std::string& text);
        bool build();
    };
    _button_builder button();
    void close_button(ClayMan& clay);

    // input
    class _input_builder : public Builder<_input_builder> {
      private:
        bool _custom_styled{ false };
        Clay_ElementDeclaration _style;
        std::string _placeholder;
        std::string* _value{ nullptr };

      public:
        _input_builder& style(Clay_ElementDeclaration style);
        _input_builder& placeholder(const std::string& placeholder);
        _input_builder& value(std::string& value);
        void build();
    };
    _input_builder input();
};
