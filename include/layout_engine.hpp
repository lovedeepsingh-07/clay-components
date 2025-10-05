#pragma once

#include "memory_arena.hpp"
#include <memory>
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

namespace LayoutEngine {
    namespace component_context {
        class Component {
          public:
            virtual ~Component() = default;
        };
        class Button : public Component {
          public:
            bool hovered{ false }; // mouse is hovering over the button
            bool pressed{ false }; // mouse was clicked but never released
        };
        class Checkbox : public Component {
          public:
            bool hovered{ false };
            bool pressed{ false };
            bool checked{ false };
        };
        class Input : public Component {
          public:
            std::string value;
            bool focused{ false };
        };
        class Dropdown : public Component {
          public:
            bool open{ false };
        };
        class Tabs : public Component {
          public:
            std::vector<std::string> tab_list;
            std::string curr_tab;
        };
        class Tooltip : public Component {};
        class Modal : public Component {
          public:
            bool open{ false };
        };
        class CodeBlock : public Component {};
    };

    struct Theme {
        std::unordered_map<std::string, Color> colors;
        float radius;
    };

    class LayoutEngine {
      private:
        std::unordered_map<std::string, std::unique_ptr<component_context::Component>> m_element_map;
        std::unordered_map<std::string, Theme> m_themes;
        std::string m_curr_theme_id;

      public:
        MemoryArena::MemoryArena frame_arena{ MemoryArena::MemoryArena(1024) };
        LayoutEngine() = default;
        ~LayoutEngine() = default;

        // disable copying
        LayoutEngine(const LayoutEngine&) = delete;
        LayoutEngine& operator=(const LayoutEngine&) = delete;

        void setup();

        void add_theme(const std::string& theme_id, Theme theme);
        void set_theme(const std::string& theme_id);
        std::string get_curr_theme();
        Color get_color(const std::string& color_id);
        float get_radius();

        // NOTE: I actually have no idea why unique_ptr is needed here, some guy in a discord server said to just do it and I did and it works, so why question it
        void add_element(const std::string& element_id, std::unique_ptr<component_context::Component> element);
        template <typename ComponentType>
        ComponentType* get_element(const std::string& element_id) {
            auto iter = m_element_map.find(element_id);
            if (iter == m_element_map.end()) {
                return nullptr;
            }
            return dynamic_cast<ComponentType*>(iter->second.get());
        }
        void clear_engine();
    };
}
