#include <GL/glut.h>
#include <cmath>
#include <iostream>

#include "my_gl.h"
#include "../base/math.h"
#include "draw_pattern.h"

// 円を描画
void drawPattern::circle(Xy *center_pos, float round, Rgb *filling_color)
{
    int edge_num = 360;
    float angle;

    Gl::color3(filling_color);

    glBegin(GL_POLYGON);

    for (auto i = 0; i < edge_num; i++)
    {
        angle = math::n_ary_convertor(i, edge_num, M_PI * 2);
        glVertex2f(
            center_pos->x + (int)(round * sin(angle)),
            center_pos->y - (int)(round * cos(angle)));
    }

    glEnd();
}

// OpenGLのGL_LINESを使って線を描画
void drawPattern::normalLine(Xy *p1, Xy *p2, Rgb *color)
{

    Gl::color3(color);

    glBegin(GL_LINES);
    glVertex2i(p1->x, p1->y);
    glVertex2i(p2->x, p2->y);
    glEnd();
}

// 円をつなげて線を描画
void drawPattern::circleLine(Xy *p1, Xy *p2, float width, Rgb *color)
{
    // 線の密度
    float dense = 2;
    // 線の両端の座標差（x, y座標別々で計算）
    auto edge_diff = new Xy(
        p2->x - p1->x, 
        p2->y - p1->y
    );

    // 描画する円の個数
    int circle_num = sqrt(pow(edge_diff->x, 2) + pow(edge_diff->y, 2)) * dense;
    // 円の間隔
    auto interval = new Xy(edge_diff->x / circle_num, edge_diff->y / circle_num);

    // 円をいくつか描画して線を描画
    for (int i = 0; i < circle_num; i++)
    {
        drawPattern::circle(new Xy(
                                p1->x + interval->x * (i + 0.5),
                                p1->y + interval->y * (i + 0.5)),
                            width / 2.0, color);
    }
}

// 針を描画
void drawPattern::clockNeedle(float len, float angle, float width, Rgb *color)
{
    // 時計の中心座標
    auto center_pos = Gl::centerPos();

    Gl::color3(color);
    
    drawPattern::circleLine(
        new Xy(center_pos->x, center_pos->y),
        new Xy(center_pos->x + (int)(len * sin(angle)),
               center_pos->y - (int)(len * cos(angle))),
        width,
        color);
}

void drawPattern::_text(string str, Xy *init_pos)
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

drawPattern::Textbox::Textbox(
    string _text, int _text_num_max,
    Rgb *_text_color, Rgb *_bg_color, Rgb *_border_color,
    Xy *_pos, Xy *_pad_size, Xy *_border_size)
{

    c_size = 9;
    text = _text;
    text_num_max = _text_num_max;
    text_color = _text_color;
    bg_color = _bg_color;
    border_color = _border_color;
    pos = _pos;
    pad_size = _pad_size;
    border_size = _border_size;
}

// テキストボックスを描画
void drawPattern::Textbox::draw()
{
    float c_size = 9;

    glBegin(GL_QUADS);
    Gl::color3(border_color);
    glVertex2i(pos->x - border_size->x / 2,
               pos->y - border_size->y / 2);
    glVertex2i(pos->x + pad_size->x * 2 + border_size->x / 2 + (c_size * text_num_max),
               pos->y - border_size->y / 2);
    glVertex2i(pos->x + pad_size->x * 2 + border_size->x / 2 + (c_size * text_num_max),
               pos->y + c_size + pad_size->y * 2 + border_size->y / 2);
    glVertex2i(pos->x - border_size->x / 2,
               pos->y + c_size + pad_size->y * 2 + border_size->y / 2);
    glEnd();

    glBegin(GL_QUADS);
    Gl::color3(bg_color);
    glVertex2i(pos->x + border_size->x / 2,
               pos->y + border_size->y / 2);
    glVertex2i(pos->x + pad_size->x * 2 - border_size->x / 2 + (c_size * text_num_max),
               pos->y + border_size->y / 2);
    glVertex2i(pos->x + pad_size->x * 2 - border_size->x / 2 + (c_size * text_num_max),
               pos->y + c_size + pad_size->y * 2 - border_size->y / 2);
    glVertex2i(pos->x + border_size->x / 2,
               pos->y + c_size + pad_size->y * 2 - border_size->y / 2);
    glEnd();

    Gl::color3(text_color);
    drawPattern::_text(text, new Xy(pos->x + pad_size->x, pos->y + pad_size->y + c_size));
}

// 描画位置を移動
void drawPattern::Textbox::rePos(Xy *_pos)
{
    pos = _pos;
}

// テキストを設定
void drawPattern::Textbox::setText(string _text)
{
    text = _text;
}

// テキストボックスのサイズを取得
Xy *drawPattern::Textbox::size()
{
    return new Xy(c_size * text_num_max, c_size + pad_size->y * 2);
}

drawPattern::Combobox::Combobox(
    vector<string> _texts, int _text_num_max,
    Rgb *_text_color, Rgb *_bg_color, Rgb *_border_color,
    Xy *_pos, Xy *_pad_size, Xy *_border_size)
{
    c_size = 9;
    texts = _texts;
    texts_num = texts.size();
    now_text = 0;
    text_num_max = _text_num_max;
    text_color = _text_color;
    bg_color = _bg_color;
    border_color = _border_color;
    pos = _pos;
    pad_size = _pad_size;
    border_size = _border_size;
}

void drawPattern::Combobox::rePos(Xy *_pos)
{
    pos = _pos;
}

void drawPattern::Combobox::draw()
{
    auto left_button = new drawPattern::Textbox(
        "<", 1, new Rgb(0, 0, 0), new Rgb(255, 255, 255), new Rgb(0, 0, 0),
        new Xy(pos->x - c_size - pad_size->x * 2, pos->y), pad_size, border_size);
    auto center_text = new drawPattern::Textbox(
        texts[now_text], text_num_max, text_color, bg_color, border_color, pos, pad_size, border_size);
    auto right_button = new drawPattern::Textbox(">", 1, text_color, bg_color, border_color,
                                                 new Xy(pos->x + c_size * text_num_max + pad_size->x * 2, pos->y), pad_size, border_size);
    left_button->draw();
    center_text->draw();
    right_button->draw();
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

Xy *drawPattern::Combobox::size()
{
    return new Xy(c_size * (text_num_max + 2), c_size + pad_size->y * 2);
}

bool drawPattern::Combobox::isInLeftButton(Xy *mouse)
{
    auto button_pos = new Xy(pos->x - c_size - pad_size->x * 2, pos->y);
    return mouse->isIn(
        button_pos,
        new Xy(button_pos->x + c_size + pad_size->x * 2, pos->y + c_size + pad_size->y * 2));
    return mouse->isIn(
        button_pos,
        new Xy(button_pos->x + pad_size->x * 2 + c_size, button_pos->y + c_size + pad_size->y));
}
bool drawPattern::Combobox::isInRightButton(Xy *mouse)
{
    auto button_pos = new Xy(pos->x + c_size * text_num_max + pad_size->x * 2, pos->y);
    return mouse->isIn(
        button_pos,
        new Xy(button_pos->x + pad_size->x * 2 + c_size, button_pos->y + c_size + pad_size->y));
}
