#pragma once

#include "clayman.hpp"
#include "layout_engine.hpp"
#include <functional>
#include <string>
#include <vector>

namespace layout_components {
    // builder for components
    template <typename BuilderType>
    class Builder {
      protected:
        ClayMan* _clay = nullptr;
        LayoutEngine::LayoutEngine* _engine = nullptr;
        std::string _id;
        bool _custom_styled{ false };
        Clay_ElementDeclaration _style;

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
        BuilderType& style(Clay_ElementDeclaration style) {
            this->_custom_styled = true;
            this->_style = style;
            return static_cast<BuilderType&>(*this);
        }
    };

    // button
    class _button_builder : public Builder<_button_builder> {
      private:
        std::string _variant{ "primary" };
        bool _text_button{ false };
        std::string _text;

      public:
        _button_builder& variant(const std::string& variant);
        _button_builder& text(const std::string& text);
        bool build();
    };
    _button_builder button();
    void close_button(ClayMan& clay);

    // input
    class _input_builder : public Builder<_input_builder> {
      private:
        std::string _placeholder;
        std::string* _value{ nullptr };

      public:
        _input_builder& placeholder(const std::string& placeholder);
        _input_builder& value(std::string& value);
        void build();
    };
    _input_builder input();

    // checkbox
    class _checkbox_builder : public Builder<_checkbox_builder> {
      public:
        void build();
    };
    _checkbox_builder checkbox();

    // dropdown root : base element in a dropdown component
    class _dropdown_root_builder : public Builder<_dropdown_root_builder> {
      public:
        void build();
    };
    _dropdown_root_builder dropdown_root();
    void close_dropdown_root(ClayMan& clay);
    // dropdown content : the element that contains the actual content of the dropdown
    class _dropdown_content_builder : public Builder<_dropdown_content_builder> {
      private:
        std::string _root_id;
        bool _button_clicked{ false };
        std::function<void()> _children;

      public:
        _dropdown_content_builder& root_id(const std::string& root_id);
        _dropdown_content_builder& button_clicked(bool button_clicked);
        _dropdown_content_builder& children(std::function<void()> children);
        void build();
    };
    _dropdown_content_builder dropdown_content();

    // tabs root : base element in a tabs component
    class _tabs_root_builder : public Builder<_tabs_root_builder> {
        std::vector<std::string> _tab_list;

      public:
        _tabs_root_builder& tab_list(std::vector<std::string> tab_list);
        void build();
    };
    _tabs_root_builder tabs_root();
    void close_tabs_root(ClayMan& clay);
    // tabs button list : header tab buttons
    class _tabs_button_list_builder : public Builder<_tabs_button_list_builder> {
        std::string _root_id;

      public:
        _tabs_button_list_builder& root_id(const std::string& root_id);
        void build();
    };
    _tabs_button_list_builder tabs_button_list();
    // tabs content : actual content
    class _tabs_content_builder : public Builder<_tabs_content_builder> {
        std::string _root_id;

      public:
        _tabs_content_builder& root_id(const std::string& root_id);
        void build();
    };
    _tabs_content_builder tabs_content();
    void close_tabs_content(ClayMan& clay);

    // tooltip
    class _tooltip_builder : public Builder<_tooltip_builder> {
        std::string _direction{ "right" };

      public:
        _tooltip_builder& direction(const std::string& direction);
        void build();
    };
    _tooltip_builder tooltip();
    void close_tooltip(ClayMan& clay);

    // modal
    class _modal_builder : public Builder<_modal_builder> {
      public:
        void build();
    };
    _modal_builder modal();
}
