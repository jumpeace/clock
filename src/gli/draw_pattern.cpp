#include <GL/glut.h>
#include <cmath>

#include "tool.h"
#include "../base/math.h"
#include "draw_pattern.h"

void drawPattern::circle(Xy *center_pos, float round, Rgb *filling_color)
{
    int edge_num = 360;
    float angle;

    glBegin(GL_POLYGON);
    Gl::color(filling_color);

    for (auto i = 0; i < edge_num; i++)
    {
        angle = math::n_ary_convertor(i, edge_num, M_PI * 2);
        glVertex2i(
            center_pos->x + (int)(round * sin(angle)),
            center_pos->y - (int)(round * cos(angle)));
    }

    glEnd();
}

// 針を描画
void drawPattern::clock_needle(float len, float angle, float lineWidth, Rgb *color)
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

void drawPattern::_str(string str, Xy *init_pos)
{
    // 画面上にテキスト描画
    glRasterPos2f(init_pos->x, init_pos->y);
    int size = (int)str.size();
    for (int i = 0; i < size; ++i)
    {
        char ic = str[i];
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, ic);
    }
}

void drawPattern::textbox(
    string text, int text_num,
    Rgb *text_color, Rgb *bg_color, Rgb *border_color,
    Xy *start_pos, Xy *pad_size, Xy *border_size)
{

    float c_size = 9;
    
    glBegin(GL_QUADS);
    Gl::color(border_color);
    glVertex2i(start_pos->x - pad_size->x - border_size->x / 2,
               start_pos->y - pad_size->y - border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x + border_size->x / 2 + (c_size * text_num),
               start_pos->y - pad_size->y - border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x + border_size->x / 2 + (c_size * text_num),
               start_pos->y + c_size + pad_size->y + border_size->y / 2);
    glVertex2i(start_pos->x - pad_size->x - border_size->x / 2,
               start_pos->y + c_size + pad_size->y + border_size->y / 2);
    glEnd();

    glBegin(GL_QUADS);
    Gl::color(bg_color);
    glVertex2i(start_pos->x - pad_size->x + border_size->x / 2,
               start_pos->y - pad_size->y + border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x - border_size->x / 2 + (c_size * text_num),
               start_pos->y - pad_size->y + border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x - border_size->x / 2 + (c_size * text_num),
               start_pos->y + c_size + pad_size->y - border_size->y / 2);
    glVertex2i(start_pos->x - pad_size->x + border_size->x / 2,
               start_pos->y + c_size + pad_size->y - border_size->y / 2);
    glEnd();

    Gl::color(text_color);
    drawPattern::_str(text, new Xy(start_pos->x, start_pos->y + c_size));
}