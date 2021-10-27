#ifndef _GL_H_
#define _GL_H_

#include <GL/glut.h>
#include "../base/color.h"
#include "../base/dim.h"

class Gl {
public:
    static void color(Rgb*);
    static void clear_color(Rgba*);
};

#endif