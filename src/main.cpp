#include <GL/glut.h>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

#include "base/dim.h"
#include "cui/country.h"
#include "cui/city.h"
#include "cui/clock.h"
#include "gui/tool.h"
#include "gui/window.h"
#include "gui/draw.h"
#include "gui/draw_pattern.h"
#include "global.h"

void display();

int main(int argc, char *argv[])
{
    // 国
    global::countries["china"] = new Country("China");
    global::countries["egypt"] = new Country("Egypt");
    global::countries["france"] = new Country("France");
    global::countries["india"] = new Country("India");
    global::countries["ingland"] = new Country("Ingland");
    global::countries["japan"] = new Country("Japan");
    global::countries["usa"] = new Country("USA");

    // 都市
    global::cities["beljing"] = new City("Beljing", global::countries["china"], 8);
    global::cities["cairo"] = new City("Cairo", global::countries["egypt"], 2);
    global::cities["delhi"] = new City("Delhi", global::countries["india"], 5.5);
    global::cities["honolulu"] = new City("Honolulu", global::countries["usa"], -10);
    global::cities["london"] = new City("London", global::countries["ingland"], 0);
    global::cities["new-york"] = new City("New York", global::countries["usa"], -5);
    global::cities["paris"] = new City("Paris", global::countries["france"], 1);
    global::cities["san-francisco"] = new City("San Francisco", global::countries["usa"], -8);
    global::cities["tokyo"] = new City("Tokyo", global::countries["japan"], 9);

    global::clock = new Clock(global::cities, "tokyo");

    global::draw = new Draw(global::clock);
    global::city_keys.resize(global::cities.size());
    vector<string> city_names(global::cities.size());

    int i = 0;
    int init_city_i;
    for (auto itr = global::cities.begin(); itr != global::cities.end(); ++itr) {
        global::city_keys[i] = itr->first;
        city_names[i] = itr->second->name;
        if (global::clock->get_now_city()->name == city_names[i]) {
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

    cout << "position" << Gl::centerPos()->x << ", " << Gl::centerPos() -> y - 220 << "\n";

    global::window->mainLoop();

    return 0;
}

// ウィンドウの表示内容を更新する関数
void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT);
    // 現在時刻を記録
    global::clock->record_now();

    // --- 描画ゾーン ---
    // 背景
    global::draw->background();
    // 時計の針
    global::draw->clock_needles();


    global::date_textbox->rePos(new Xy(
        Gl::centerPos()->x - global::date_textbox->size()->x * 0.5
        , Gl::centerPos()->y + 220 - global::city_combobox->size()->y));
    auto clock_strs = global::clock->get_city_time_by_str_map();
    global::date_textbox->setText(
        clock_strs["year"] + "/" + clock_strs["mon"] + "/" + clock_strs["mday"] 
        + "(" + clock_strs["wday"] + ")"
    );
    global::date_textbox->draw();

    global::city_combobox->rePos(new Xy(
        Gl::centerPos()->x - global::city_combobox->size()->x * 0.5, 
        Gl::centerPos()->y - 220));
    global::city_combobox->draw();


    glFlush();
}
