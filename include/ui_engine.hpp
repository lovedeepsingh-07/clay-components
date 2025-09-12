#pragma once

#include "clayman.hpp"
#include <functional>
#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>

namespace UIEngine {
    namespace element_context {
        class Element {
          public:
            virtual ~Element() = default;
        };
        class Dropdown : public Element {
          public:
            bool open{ false }; // dropdown is open
        };
        class Button : public Element {
          public:
            bool hovered{ false }; // mouse if hovering over the button
            bool active{ true }; // button is active
            bool pressed{ false }; // mouse button was clicked but never released
        };
    }; // namespace element_context

    struct UITheme {
        std::unordered_map<std::string, Color> colors;
        float radius;
    };

    class UIEngine {
      private:
        std::unordered_map<std::string, std::unique_ptr<element_context::Element>> m_element_map;
        std::unordered_map<std::string, UITheme> m_themes;
        std::string m_curr_theme_id;

      public:
        UIEngine() = default;
        ~UIEngine() = default;

        void setup();

        void add_theme(const std::string& theme_id, UITheme theme);
        void set_theme(const std::string& theme_id);
        std::string get_curr_theme();
        Color get_color(const std::string& color_id);
        float get_radius();

        void add_element(const std::string& element_id, std::unique_ptr<element_context::Element> element);
        template <typename ElementType>
        ElementType* get_element(const std::string& element_id) {
            auto iter = m_element_map.find(element_id);
            if (iter == m_element_map.end()) {
                return nullptr;
            }
            return dynamic_cast<ElementType*>(iter->second.get());
        }
        void clear_engine();
    };

    namespace elements {
        void dropdown(
            ClayMan& clay,
            UIEngine& UI_engine,
            const std::string& element_id,
            const std::function<void()>& children_func
        );
        bool button(
            ClayMan& clay,
            UIEngine& UI_engine,
            const std::string& element_id,
            const std::function<void()>& children_func
        );
    }; // namespace elements

} // namespace UIEngine
