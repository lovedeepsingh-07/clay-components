#pragma once

#include "clay.h"
#include <iostream>
#include <raylib.h>

namespace app_utils {
    void handle_clay_errors(Clay_ErrorData errorData);
    Clay_Color raylib_to_clay(Color ray_color);
    Color clay_to_raylib(Clay_Color clay_color);
    bool is_color_set(Clay_Color color);
} // namespace app_utils
