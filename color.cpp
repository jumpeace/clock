// 18411 川原隼平

#include "color.h"

Rgb::Rgb(int _r, int _g, int _b) {
    r = _r;
    g = _g;
    b = _b;
}

map<string, float> Rgb::toGl() {
    map<string, float> gl_color_map;

    gl_color_map["r"] = (float)r / 255.0;
    gl_color_map["g"] = (float)g / 255.0;
    gl_color_map["b"] = (float)b / 255.0;

    return gl_color_map;
}

Rgba::Rgba(int _r, int _g, int _b, int _a) : Rgb(_r, _g, _b) {
    a = _a;
}

map<string, float> Rgba::toGl() {
    map<string, float> gl_color_map = Rgb::toGl();

    gl_color_map["a"] = a / 255.0;

    return gl_color_map;
}
