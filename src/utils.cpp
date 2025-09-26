#include "utils.hpp"

void app_utils::handle_clay_errors(Clay_ErrorData errorData) {
    printf("%s\n", errorData.errorText.chars);
};

Clay_Color app_utils::raylib_to_clay(Color ray_color) {
    Clay_Color clay_color;
    clay_color.r = ray_color.r;
    clay_color.g = ray_color.g;
    clay_color.b = ray_color.b;
    clay_color.a = ray_color.a;
    return clay_color;
}

Color app_utils::clay_to_raylib(Clay_Color clay_color) {
    Color ray_color;
    ray_color.r = clay_color.r;
    ray_color.g = clay_color.g;
    ray_color.b = clay_color.b;
    ray_color.a = clay_color.a;
    return ray_color;
}

bool app_utils::is_color_set(Clay_Color color) {
    if (color.r == 0 && color.g == 0 && color.b == 0 && color.a == 0) {
        return false;
    }
    return true;
}
