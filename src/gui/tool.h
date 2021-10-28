#ifndef _TOOL_H_
#define _TOOL_H_

#include <GL/glut.h>
#include "../base/color.h"
#include "../base/dim.h"

class Gl {
public:
    static Xy* windowSize();
    static Xy* centerPos();
    static void color3(Rgb*);
    static void color4(Rgba*);
    static void clear_color(Rgba*);
};

#endif