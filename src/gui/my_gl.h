#ifndef _my_gl_H_
#define _my_gl_H_

#include <GL/glut.h>
#include "../base/color.h"
#include "../base/dim.h"

class Gl {
public:
    static Xy* windowSize();
    static Xy* centerPos();
    static void color3(Rgb*);
    static void color4(Rgba*);
    static void clearColor(Rgba*);
};

#endif