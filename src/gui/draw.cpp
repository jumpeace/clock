#include "draw.h"

#include <GL/glut.h>
#include <GL/glpng.h>
#include <cmath>

#include "../base/math.h"
#include "../base/color.h"
#include "../gui/my_gl.h"
#include "../gui/draw_pattern.h"
#include "../global.h"

Draw::Draw(Clock* _clock) {
    clock = _clock;
}

void Draw::background()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Gl::clearColor((clock->city_time->isMorning()) ? 
        new Rgba(100, 237, 237, 255) :new Rgba(237, 172, 102, 255));

    int inner_round = 180;
    int outer_round = 185;
    int text_round = 145;
    int bigger_scale_inner_round = inner_round - 15;
    int smaller_scale_inner_round = inner_round - 7.5;

    drawPattern::circle(Gl::centerPos(), outer_round, new Rgb(90, 90, 90));
    drawPattern::circle(Gl::centerPos(), inner_round, new Rgb(240, 240, 240));

    for (int i = 1; i <= 12; i++) {
        global::images[to_string(i)]->putSprite(
            new Xy(
                Gl::centerPos()->x + text_round * sin(math::n_ary_convertor(i, 12, M_PI * 2)), 
                Gl::centerPos()->y - text_round * cos(math::n_ary_convertor(i, 12, M_PI * 2)))
            , 0.1, math::n_ary_convertor(i, 12, M_PI * 2));
    }

    // 目盛り
    Gl::color3(new Rgb(0, 0, 0));
    for (int i = 0; i < 60; i++) {
        float angle = math::n_ary_convertor((float)i, 60.0, M_PI * 2);
        auto center_pos = Gl::centerPos();
        auto scale_inner_round = (i % 5 == 0) ? 
            bigger_scale_inner_round : smaller_scale_inner_round;
            
        drawPattern::normalLine(
            new Xy(
            center_pos->x + (int)(scale_inner_round * sin(angle)),
            center_pos->y - (int)(scale_inner_round * cos(angle))),
            new Xy(
            center_pos->x + (int)(inner_round * sin(angle)),
            center_pos->y - (int)(inner_round * cos(angle))),
            new Rgb(0, 0, 0)
        );
    }

    global::date_textbox->rePos(new Xy(
        Gl::centerPos()->x - global::date_textbox->size()->x * 0.5
        , Gl::centerPos()->y + 220 - global::city_combobox->size()->y));
    auto clock_strs = global::clock->getCityTimeByStrList();
    global::date_textbox->setText(
        clock_strs["year"] + "/" + clock_strs["mon"] + "/" + clock_strs["mday"] 
        + "(" + clock_strs["wday"] + ")"
    );
    global::date_textbox->draw();

    global::city_combobox->rePos(new Xy(
        Gl::centerPos()->x - global::city_combobox->size()->x * 0.5, 
        Gl::centerPos()->y - 220));
    global::city_combobox->draw();
}

// 針を描画
void Draw::clockNeedles() {

    // 針を描画
    drawPattern::clockNeedle(167.5,
                      math::n_ary_convertor(clock->city_time->sec, 60, M_PI * 2),
                      4.0, new Rgb(207, 123, 93));
    drawPattern::clockNeedle(160,
                      math::n_ary_convertor(clock->city_time->min, 60, M_PI * 2) + math::n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 60),
                      4.0, new Rgb(0, 0, 0));
    drawPattern::clockNeedle(90,
                      math::n_ary_convertor(clock->city_time->hour % 12, 12, M_PI * 2) + math::n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 12),
                      10.0, new Rgb(0, 0, 0));
}
