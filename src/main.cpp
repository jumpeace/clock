#include <GL/glut.h>
#include <cmath>
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
#include "gli/draw.h"
// using namespace Draw;

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

    // --- 描画ゾーン ---
    Draw* draw = new Draw(clock);
    draw->background();
    draw->clock_needles();

    glFlush();
}
