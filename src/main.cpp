#include <GL/glut.h>
#include <iostream>
#include <cmath>
#include <map>
using namespace std;

#include "base/dim.h"
#include "base/color.h"
#include "cli/country.h"
#include "cli/city.h"
#include "cli/time.h"
#include "cli/clock.h"
#include "gli/gl.h"

void reshapeDisplay(int, int);
void display();

int main(int argc, char *argv[])
{
    // glutの初期化
    glutInit(&argc, argv);

    // ウィンドウの初期化
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(600, 480);

    // ウィンドウ作成
    glutCreateWindow("sample1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshapeDisplay);

    // 初期描画
    display();

    // ウィンドウの描画
    glutMainLoop();

    return 0;
}

// 画面サイズが変わっても、座標が混乱しないようにする
void reshapeDisplay(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

// 針を描画
void draw_clock_needle(double len, double angle, float lineWidth, Rgb* color)
{
    // BUG 線の太さが変わらない
    auto window_w = glutGet(GLUT_WINDOW_WIDTH);
    auto window_h = glutGet(GLUT_WINDOW_HEIGHT);
    auto window_half_x = window_w / 2;
    auto window_half_y = window_h / 2;

    glBegin(GL_LINES);
    Gl::color(color);
    glLineWidth(lineWidth);
    glVertex2i(window_half_x, window_half_y);
    glVertex2i(
        window_half_x + (int)(len * sin(angle)),
        window_half_y - (int)(len * cos(angle)));
    glEnd();
}

// n1進法からn2進法に変換
double n_ary_convertor(double src, double n1, double n2)
{
    return src * (n2 / n1);
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
        // glClearColor(0.0, 1.0, 1.0, 1.0);
    else
        Gl::clear_color(new Rgba(255, 0, 255, 255));
        // glClearColor(1.0, 0.0, 1.0, 1.0);

    Rgb* color = (is_morning) ? new Rgb(0, 0, 0) : new Rgb(255, 255, 255);
    // 針を描画
    draw_clock_needle(90,
                      n_ary_convertor(clock->city_time->hour % 12, 12, M_PI * 2) + n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 12), 
                      20.0, color);
    draw_clock_needle(110,
                      n_ary_convertor(clock->city_time->min, 60, M_PI * 2) + n_ary_convertor(clock->city_time->min, 60, (M_PI * 2) / 60),
                      4.0, color);
    draw_clock_needle(120,
                      n_ary_convertor(clock->city_time->sec, 60, M_PI * 2),
                      2.0, color);

    glFlush();
}
