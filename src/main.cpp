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
#include "global.h"

void display();


int main(int argc, char *argv[])
{
    // 国
    global::countries["usa"] = new Country("USA");
    global::countries["ingland"] = new Country("Ingland");
    global::countries["japan"] = new Country("Japan");

    // 都市
    global::cities["tokyo"] = new City("Tokyo", global::countries["japan"], 9);
    global::cities["london"] = new City("London", global::countries["ingland"], 0);
    global::cities["new-york"] = new City("New York", global::countries["usa"], -5);
    global::cities["san-francisco"] = new City("San Francisco", global::countries["usa"], -8);

    global::clock = new Clock(global::cities, "tokyo");

    global::draw = new Draw(global::clock);

    window::init(&argc, argv, "My Clock", new Xy(600, 480), display, 100);

    return 0;
}

// ウィンドウの表示内容を更新する関数
void display(void)
{
    // 現在時刻を記録
    global::clock->record_now();

    // --- 描画ゾーン ---
    // 背景
    global::draw->background();
    // 時計の針
    global::draw->clock_needles();

    glFlush();
}
