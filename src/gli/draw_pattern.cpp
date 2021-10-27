#include <GL/glut.h>

#include "tool.h"
#include "../base/math.h"
#include "draw_pattern.h"

void draw_circle(Xy* center_pos, float round, Rgb* filling_color) {
    int edge_num = 360;
    float angle;

    glBegin(GL_POLYGON);
    Gl::color(filling_color);
    
    for (auto i = 0; i < edge_num; i++)
    {
        angle = n_ary_convertor(i, edge_num, M_PI * 2);
        glVertex2i(
            center_pos->x + (int)(round * sin(angle)),
            center_pos->y - (int)(round * cos(angle))
        );
    }

    glEnd();
}

// 針を描画
void draw_clock_needle(float len, float angle, float lineWidth, Rgb *color)
{
    // BUG 線の太さが変わらない
    auto center_pos = Gl::centerPos();

    glBegin(GL_LINES);
    Gl::color(color);
    glVertex2i(center_pos->x, center_pos->y);
    glVertex2i(
        center_pos->x + (int)(len * sin(angle)),
        center_pos->y - (int)(len * cos(angle)));
    glEnd();
}