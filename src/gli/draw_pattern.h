#ifndef _DRAW_PATTERN_H_
#define _DRAW_PATTERN_H_

#include "../base/dim.h"
#include "../base/color.h"

namespace drawPattern
{
    // 塗りつぶされた円を描画
    void circle(Xy *, float, Rgb *);
    // 針を描画
    void clock_needle(float, float, float, Rgb *);
    // 文字列
    void _str(string str, Xy *init_pos);
    void textbox(string, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
}

#endif