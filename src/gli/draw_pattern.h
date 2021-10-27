#ifndef _DRAW_PATTERN_H_
#define _DRAW_PATTERN_H_

#include "../base/dim.h"
#include "../base/color.h"

// 塗りつぶされた円を描画
void draw_circle(Xy *, float, Rgb *);
// 針を描画
void draw_clock_needle(float, float, float, Rgb *);

#endif