#include "draw.h"

#include <GL/glut.h>
#include <cmath>

#include "../base/math.h"
#include "../base/color.h"
#include "../gui/tool.h"
#include "../gui/draw_pattern.h"

Draw::Draw(Clock* _clock) {
    clock = _clock;
}

void Draw::background()
{
    glClear(GL_COLOR_BUFFER_BIT);

    Gl::clear_color((clock->city_time->is_morning()) ? 
        new Rgba(100, 237, 237, 255) :new Rgba(237, 172, 102, 255));

    drawPattern::circle(Gl::centerPos(), 155, new Rgb(90, 90, 90));
    drawPattern::circle(Gl::centerPos(), 150, new Rgb(240, 240, 240));
}

// 針を描画
void Draw::clock_needles() {

    // 針を描画
    drawPattern::clock_needle(90,
                      math::n_ary_convertor(clock->city_time->hour % 12, 12, M_PI * 2) + math::n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 12),
                      20.0, new Rgb(0, 0, 0));
    drawPattern::clock_needle(110,
                      math::n_ary_convertor(clock->city_time->min, 60, M_PI * 2) + math::n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 60),
                      4.0, new Rgb(0, 0, 0));
    drawPattern::clock_needle(120,
                      math::n_ary_convertor(clock->city_time->sec, 60, M_PI * 2),
                      2.0, new Rgb(0, 0, 0));
}