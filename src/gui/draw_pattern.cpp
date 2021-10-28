#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "tool.h"
#include "../base/math.h"
#include "draw_pattern.h"

void drawPattern::circle(Xy *center_pos, float round, Rgb *filling_color)
{
    int edge_num = 360;
    float angle;

    glBegin(GL_POLYGON);
    Gl::color3(filling_color);

    for (auto i = 0; i < edge_num; i++)
    {
        angle = math::n_ary_convertor(i, edge_num, M_PI * 2);
        glVertex2f(
            center_pos->x + (int)(round * sin(angle)),
            center_pos->y - (int)(round * cos(angle)));
    }

    glEnd();
}

void drawPattern::line(Xy *p1, Xy *p2, float line_width, Rgb* color)
{
    float denseness = 2;
    glPointSize(line_width);
    auto diff = new Xy(p2->x - p1->x, p2->y - p1->y);
    float angle = atan(diff->y / diff->x);
    // cout << "angle:" << angle << "\n";
    int div_num = sqrt(pow(diff->x, 2) + pow(diff->y, 2)) * denseness;
    auto step_w = new Xy(diff->x / div_num, diff->y / div_num);
    for (int i = 0; i < div_num; i++)
    {
        drawPattern::circle(new Xy(
            p1->x + step_w->x * (i + 0.5), 
            p1->y + step_w->y * (i + 0.5)), 
        line_width / 2.0, color);
        // glBegin(GL_POINTS);
        // glVertex2f(p1->x + step_w->x * (i + 0.5), 
        // p1->y + step_w->y * (i + 0.5));
        // // glVertex2i(p1->x + step_w->x * (i + 0.5), 
        // // p1->y + step_w->y * (i + 0.5));
        // glEnd();
    }
}

// 針を描画
void drawPattern::clock_needle(float len, float angle, float line_width, Rgb *color)
{
    // BUG 線の太さが変わらない
    auto center_pos = Gl::centerPos();


    Gl::color3(color);
    drawPattern::line(
        new Xy(center_pos->x, center_pos->y),
        new Xy(center_pos->x + (int)(len * sin(angle)),
        center_pos->y - (int)(len * cos(angle))), line_width,
        color
    );
    // glBegin(GL_LINES);
    // glVertex2i(center_pos->x, center_pos->y);
    // glVertex2i(
    //     center_pos->x + (int)(len * sin(angle)),
    //     center_pos->y - (int)(len * cos(angle)));
    // glEnd();
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

// 左右のボタンをつけて、世界時計のための入力装置を作る
void drawPattern::textbox(
    string text, int text_num_max,
    Rgb *text_color, Rgb *bg_color, Rgb *border_color,
    Xy *start_pos, Xy *pad_size, Xy *border_size)
{

    float c_size = 9;

    glBegin(GL_QUADS);
    Gl::color3(border_color);
    glVertex2i(start_pos->x - border_size->x / 2,
               start_pos->y - border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x * 2 + border_size->x / 2 + (c_size * text_num_max),
               start_pos->y - border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x * 2 + border_size->x / 2 + (c_size * text_num_max),
               start_pos->y + c_size + pad_size->y * 2 + border_size->y / 2);
    glVertex2i(start_pos->x - border_size->x / 2,
               start_pos->y + c_size + pad_size->y * 2 + border_size->y / 2);
    glEnd();

    glBegin(GL_QUADS);
    Gl::color3(bg_color);
    glVertex2i(start_pos->x + border_size->x / 2,
               start_pos->y + border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x * 2 - border_size->x / 2 + (c_size * text_num_max),
               start_pos->y + border_size->y / 2);
    glVertex2i(start_pos->x + pad_size->x * 2 - border_size->x / 2 + (c_size * text_num_max),
               start_pos->y + c_size + pad_size->y * 2 - border_size->y / 2);
    glVertex2i(start_pos->x + border_size->x / 2,
               start_pos->y + c_size + pad_size->y * 2 - border_size->y / 2);
    glEnd();

    Gl::color3(text_color);
    drawPattern::_str(text, new Xy(start_pos->x + pad_size->x, start_pos->y + pad_size->y + c_size));
}
drawPattern::Combobox::Combobox(
    vector<string> _texts, int _text_num_max,
    Rgb *_text_color, Rgb *_bg_color, Rgb *_border_color,
    Xy *_start_pos, Xy *_pad_size, Xy *_border_size)
{
    c_size = 9;
    texts = _texts;
    texts_num = texts.size();
    now_text = 0;
    text_num_max = _text_num_max;
    text_color = _text_color;
    bg_color = _bg_color;
    border_color = _border_color;
    start_pos = _start_pos;
    pad_size = _pad_size;
    border_size = _border_size;
}

void drawPattern::Combobox::rePos(Xy* pos) {
    start_pos = pos;
}

void drawPattern::Combobox::draw()
{
    rePos(new Xy(
        Gl::centerPos()->x - size()->x * 0.5, Gl::centerPos()->y - 220));
    drawPattern::textbox("<", 1, new Rgb(0, 0, 0), new Rgb(255, 255, 255), new Rgb(0, 0, 0),
                         new Xy(start_pos->x - c_size - pad_size->x * 2, start_pos->y), pad_size, border_size);
    drawPattern::textbox(texts[now_text], text_num_max, text_color, bg_color, border_color, start_pos, pad_size, border_size);
    drawPattern::textbox(">", 1, text_color, bg_color, border_color,
                         new Xy(start_pos->x + c_size * text_num_max + pad_size->x * 2, start_pos->y), pad_size, border_size);
}

bool drawPattern::Combobox::set_now(int new_now)
{
    if (new_now >= texts_num || new_now < 0)
        return false;
    now_text = new_now;
    return true;
}

int drawPattern::Combobox::get_now()
{
    return now_text;
}

string drawPattern::Combobox::get_now_text()
{
    return texts[drawPattern::Combobox::get_now()];
}

int drawPattern::Combobox::get_texts_num()
{
    return texts_num;
}

Xy* drawPattern::Combobox::size() {
    return new Xy(c_size * (text_num_max + 2), c_size + pad_size->y * 2);
}

bool drawPattern::Combobox::isInLeftButton(Xy *mouse)
{
    auto button_start_pos = new Xy(start_pos->x - c_size - pad_size->x * 2, start_pos->y);
    return mouse->isIn(
        button_start_pos,
        new Xy(button_start_pos->x + c_size + pad_size->x * 2, start_pos->y + c_size + pad_size->y * 2));
    return mouse->isIn(
        button_start_pos,
        new Xy(button_start_pos->x + pad_size->x * 2 + c_size, button_start_pos->y + c_size + pad_size->y));
}
bool drawPattern::Combobox::isInRightButton(Xy *mouse)
{
    auto button_start_pos = new Xy(start_pos->x + c_size * text_num_max + pad_size->x * 2, start_pos->y);
    return mouse->isIn(
        button_start_pos,
        new Xy(button_start_pos->x + pad_size->x * 2 + c_size, button_start_pos->y + c_size + pad_size->y));
}
