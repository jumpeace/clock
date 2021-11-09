#include <GL/glut.h>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

#include "base/dim.h"
#include "cui/country.h"
#include "cui/city.h"
#include "cui/clock.h"
#include "gui/my_gl.h"
#include "gui/window.h"
#include "gui/draw.h"
#include "gui/draw_pattern.h"
#include "global.h"

void display();

int main(int argc, char *argv[])
{
    // 国
    global::country_list["china"] = new Country("China");
    global::country_list["egypt"] = new Country("Egypt");
    global::country_list["france"] = new Country("France");
    global::country_list["india"] = new Country("India");
    global::country_list["ingland"] = new Country("Ingland");
    global::country_list["japan"] = new Country("Japan");
    global::country_list["usa"] = new Country("USA");

    // 都市
    global::city_list["beljing"] = new City("Beljing", global::country_list["china"], 8);
    global::city_list["cairo"] = new City("Cairo", global::country_list["egypt"], 2);
    global::city_list["delhi"] = new City("Delhi", global::country_list["india"], 5.5);
    global::city_list["honolulu"] = new City("Honolulu", global::country_list["usa"], -10);
    global::city_list["london"] = new City("London", global::country_list["ingland"], 0);
    global::city_list["new-york"] = new City("New York", global::country_list["usa"], -5);
    global::city_list["paris"] = new City("Paris", global::country_list["france"], 1);
    global::city_list["san-francisco"] = new City("San Francisco", global::country_list["usa"], -8);
    global::city_list["tokyo"] = new City("Tokyo", global::country_list["japan"], 9);

    global::clock = new Clock(global::city_list, "tokyo");

    global::draw = new Draw(global::clock);
    global::city_keys.resize(global::city_list.size());
    vector<string> city_names(global::city_list.size());

    int i = 0;
    int init_city_i;
    for (auto itr = global::city_list.begin(); itr != global::city_list.end(); ++itr) {
        global::city_keys[i] = itr->first;
        city_names[i] = itr->second->name;
        if (global::clock->getNowCity()->name == city_names[i]) {
            init_city_i = i;
        }
        city_names[i] = itr->second->country->name + " / " + city_names[i];
        i++;
    }
    global::city_combobox = new drawPattern::Combobox(city_names, 25,
        new Rgb(0, 0, 0), new Rgb(255, 255, 255), new Rgb(0, 0, 0),
        new Xy(0, 0), new Xy(5, 10), new Xy(1.5, 1.5)
    );

    global::city_combobox->set_now(init_city_i);

    global::date_textbox = new drawPattern::Textbox("", 15, 
        new Rgb(0, 0, 0), new Rgb(210, 210, 210), new Rgb(0, 0, 0),
        new Xy(0, 0), new Xy(5, 8), new Xy(1, 1)
    );
    
    global::window = new Window(&argc, argv, "My Clock", new Xy(600, 480), display, 250);
    global::window->init();

    global::window->mainLoop();

    return 0;
}

// ウィンドウの表示内容を更新する関数
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    // 現在時刻を記録
    global::clock->recordNow();

    // --- 描画ゾーン ---
    // 背景
    global::draw->background();
    // 時計の針
    global::draw->clockNeedles();

    glFlush();
    // ダブルバッファリング
    glutSwapBuffers();
}
