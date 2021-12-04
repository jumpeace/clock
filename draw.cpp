// 18411 川原隼平

#include "draw.h"

#include <GL/glut.h>
#include <GL/glpng.h>
#include <cmath>

#include "funcs.h"
#include "color.h"
#include "my_gl.h"
#include "draw_pattern.h"
#include "global.h"

// 画面の背景を描画
Draw::Draw(Clock *_clock)
{
    clock = _clock;
}

void Draw::background()
{
    glClear(GL_COLOR_BUFFER_BIT);

    // 画面の背景色
    Gl::clearColor((clock->city_time->isMorning()) ? new Rgba(100, 237, 237, 255) : new Rgba(237, 172, 102, 255));

    // 時計の中心と枠線外側との距離
    int border_outer_round = 185;
    // 時計の中心と枠線内側との距離
    int border_inner_round = 180;
    // 時計の中心と大きい目盛り線の内側の端との距離
    int bigger_scale_round = border_inner_round - 25;
    // 時計の中心と小さい目盛り線の内側の端との距離
    int smaller_scale_round = border_inner_round - 10;

    // 枠線の外枠の円を描画
    drawPattern::circle(Gl::centerPos(), border_outer_round, new Rgb(90, 90, 90));
    // 枠線の内枠の円を描画
    drawPattern::circle(Gl::centerPos(), border_inner_round, new Rgb(240, 240, 240));


    // 目盛りを描画
    Gl::color3(new Rgb(0, 0, 0));
    for (int i = 0; i < 60; i++)
    {
        float angle = funcs::nAryConvertor((float)i, 60.0, M_PI * 2);
        auto center_pos = Gl::centerPos();

        // 5目盛りごとに大きい目盛りになる
        auto inner_round = (i % 5 == 0) ? bigger_scale_round : smaller_scale_round;

        drawPattern::normalLine(
            new Xy(
                center_pos->x + (int)(inner_round * sin(angle)),
                center_pos->y - (int)(inner_round * cos(angle))),
            new Xy(
                center_pos->x + (int)(border_inner_round * sin(angle)),
                center_pos->y - (int)(border_inner_round * cos(angle))),
            new Rgb(0, 0, 0));
    }

    // 日にちのテキストボックスを描画
    global::date_textbox->rePos(new Xy(
        Gl::centerPos()->x - global::date_textbox->size()->x * 0.5, Gl::centerPos()->y + 220 - global::city_combobox->size()->y));
    auto clock_strs = global::clock->getCityTime_ByStrList();
    global::date_textbox->setText(
        clock_strs["year"] + "/" + clock_strs["mon"] + "/" + clock_strs["mday"] + "(" + clock_strs["wday"] + ")");
    global::date_textbox->draw();

    // 都市変更用のコンボボックスを描画
    global::city_combobox->rePos(new Xy(
        Gl::centerPos()->x - global::city_combobox->size()->x * 0.5,
        Gl::centerPos()->y - 220));
    global::city_combobox->draw();
}

// 針を描画
void Draw::clockNeedles()
{
    // 秒針
    drawPattern::clockNeedle(167.5,
                             funcs::nAryConvertor(clock->city_time->sec, 60, M_PI * 2),
                             4.0, new Rgb(207, 123, 93));

    // 分針
    drawPattern::clockNeedle(160,
                             funcs::nAryConvertor(clock->city_time->min, 60, M_PI * 2),
                             4.0, new Rgb(0, 0, 0));

    // 時針
    drawPattern::clockNeedle(90,
                             funcs::nAryConvertor(clock->city_time->hour % 12, 12, M_PI * 2) + funcs::nAryConvertor(clock->city_time->min, 60, (M_PI * 2) / 12),
                             10.0, new Rgb(0, 0, 0));
}
