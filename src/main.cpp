#include <GL/glut.h>
#include <iostream>
#include <map>
using namespace std;

#include "base/dim.h"
#include "base/color.h"
#include "base/math.h"
#include "cli/country.h"
#include "cli/city.h"
#include "cli/time.h"
#include "cli/clock.h"
#include "gli/tool.h"
#include "gli/window.h"
#include "gli/draw_pattern.h"

void display();


int main(int argc, char *argv[])
{
    window_init(&argc, argv, new Xy(600, 480), display, 100);

    return 0;
}

// ウィンドウの表示内容を更新する関数
void display(void)
{
    // 国と都市を定義
    // CLEAN 別の場所で常に変数として持つ（毎回読み込むのは良くないため）
    map<string, Country *> country_map;

    country_map["usa"] = new Country("USA");
    country_map["ingland"] = new Country("Ingland");
    country_map["japan"] = new Country("Japan");

    map<string, City *> city_map;

    city_map["tokyo"] = new City("Tokyo", country_map["japan"], 9);
    city_map["london"] = new City("London", country_map["ingland"], 0);
    city_map["new-york"] = new City("New York", country_map["usa"], -5);
    city_map["san-francisco"] = new City("San Francisco", country_map["usa"], -8);

    // 時刻を取得
    // CLEAN 別の場所で常に変数として持つ（毎回読み込むのは良くないため）
    Clock *clock = new Clock(city_map, "tokyo");

    clock->record_now();
    bool is_morning = clock->city_time->is_morning();

    // --- 描画ゾーン ---
    // 背景クリア
    glClear(GL_COLOR_BUFFER_BIT);

    if (is_morning)
        Gl::clear_color(new Rgba(0, 255, 255, 255));
    else
        Gl::clear_color(new Rgba(255, 255, 0, 255));

    draw_circle(Gl::centerPos(), 155, new Rgb(255, 255, 255));
    draw_circle(Gl::centerPos(), 150, new Rgb(0, 0, 0));

    // 針を描画
    draw_clock_needle(90,
                      n_ary_convertor(clock->city_time->hour % 12, 12, M_PI * 2) + n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 12),
                      20.0, new Rgb(255, 255, 255));
    draw_clock_needle(110,
                      n_ary_convertor(clock->city_time->min, 60, M_PI * 2) + n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 60),
                      4.0, new Rgb(255, 255, 255));
    draw_clock_needle(120,
                      n_ary_convertor(clock->city_time->sec, 60, M_PI * 2),
                      2.0, new Rgb(255, 255, 255));

    glFlush();
}
