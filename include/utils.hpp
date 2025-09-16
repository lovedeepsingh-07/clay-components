#pragma once

#include "clay.h"
#include <iostream>
#include <raylib.h>

namespace app_utils {
    constexpr float PPM = 32.0F;
    constexpr float MPP = (1.0F / PPM);

    template <typename... Args>
    void println(Args&&... args) {
        (std::cout << ... << std::forward<Args>(args)) << '\n';
    }
    Clay_Color raylib_to_clay(Color ray_color);
    Color clay_to_raylib(Clay_Color clay_color);
    bool is_color_set(Clay_Color color);
} // namespace app_utils
