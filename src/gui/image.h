#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <GL/glpng.h>
#include <GL/glut.h>
#include <iostream>
using namespace std;
#include "../base/dim.h"

class Image {
public:
    GLuint img;
    pngInfo info;
    static void init();
    Image(string);
    void putSprite(Xy*);
};

#endif