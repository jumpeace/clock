#include <GL/glut.h>
#include <iostream>
#include <map>
#include <cmath>
using namespace std;

#include "dim.h"
#include "country.h"
#include "city.h"
#include "clock.h"
#include "my_gl.h"
#include "window.h"
#include "draw.h"
#include "draw_pattern.h"
#include "global.h"

void display();

int main(int argc, char *argv[])
{
    // 国を登録
    global::country_list["china"] = new Country("China");
    global::country_list["egypt"] = new Country("Egypt");
    global::country_list["france"] = new Country("France");
    global::country_list["india"] = new Country("India");
    global::country_list["ingland"] = new Country("Ingland");
    global::country_list["japan"] = new Country("Japan");
    global::country_list["usa"] = new Country("USA");

    // 都市を登録
    global::city_list["beljing"] = new City("Beljing", global::country_list["china"], 8);
    global::city_list["cairo"] = new City("Cairo", global::country_list["egypt"], 2);
    global::city_list["delhi"] = new City("Delhi", global::country_list["india"], 5.5);
    global::city_list["honolulu"] = new City("Honolulu", global::country_list["usa"], -10);
    global::city_list["london"] = new City("London", global::country_list["ingland"], 0);
    global::city_list["new-york"] = new City("New York", global::country_list["usa"], -5);
    global::city_list["paris"] = new City("Paris", global::country_list["france"], 1);
    global::city_list["san-francisco"] = new City("San Francisco", global::country_list["usa"], -8);
    global::city_list["tokyo"] = new City("Tokyo", global::country_list["japan"], 9);

    // 時計を初期化
    global::clock = new Clock(global::city_list, "tokyo");

    // 描画機能を初期化
    global::draw = new Draw(global::clock);

    // 都市をコンボボックスに格納
    // 都市のキーの一覧
    global::city_keys.resize(global::city_list.size());
    // 都市名一覧(キーの一覧と要素番号ごとに同じ都市が対応する)
    vector<string> city_names(global::city_list.size());

    // 都市のキーの一覧と都市名一覧に都市の情報を追加
    int i = 0;
    // 時計の都市のインデックス
    int init_city_i;
    for (auto itr = global::city_list.begin(); itr != global::city_list.end(); ++itr) {
        global::city_keys[i] = itr->first;

        // 時計とコンボボックスで都市を一致させる
        if (global::clock->getNowIdxCity()->name == itr->second->name) {
            init_city_i = i;
        }
        city_names[i] = itr->second->country->name + " / " + itr->second->name;
        i++;
    }

    // 都市のコンボボックスを初期化
    global::city_combobox = new drawPattern::Combobox(city_names, 25,
        new Rgb(0, 0, 0), new Rgb(255, 255, 255), new Rgb(0, 0, 0),
        new Xy(0, 0), new Xy(5, 10), new Xy(1.5, 1.5)
    );

    // 最初の都市
    global::city_combobox->setNowIdx(init_city_i);

    global::date_textbox = new drawPattern::Textbox("", 15,
        new Rgb(0, 0, 0), new Rgb(210, 210, 210), new Rgb(0, 0, 0),
        new Xy(0, 0), new Xy(5, 8), new Xy(1, 1)
    );

    // ウィンドウの制御
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
