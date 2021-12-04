// 18411 川原隼平

#include <GL/glut.h>
#include <GL/glpng.h>
#include <iostream>
#include "window.h"
#include "my_gl.h"
#include "global.h"
#include "draw_pattern.h"

int wait_ms;

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(wait_ms, timer, 0);
}

// 左のボタンが押されたときのコールバック関数
void leftButtonCallback() {
    // 前の都市に変更
    global::city_combobox->setNowIdx(
        (global::city_combobox->getNowIdx() + global::city_combobox->getTextsNum() - 1) % global::city_combobox->getTextsNum());
}

// 右のボタンが押されたときのコールバック関数
void rightButtonCallback() {
    // 次の都市に変更
    global::city_combobox->setNowIdx(
        (global::city_combobox->getNowIdx() + 1) % global::city_combobox->getTextsNum());
}

// マウスイベントがあったら呼ばれる関数
void changeCity(int button, int state, int x, int y)
{
    // 左のボタンが押されたときの処理
    global::city_combobox->leftButtonProc(button, state, new Xy(x, y), leftButtonCallback);
    // 右のボタンが押されたときの処理
    global::city_combobox->rightButtonProc(button, state, new Xy(x, y), rightButtonCallback);
    // 時計に都市の変更を反映する
    global::clock->setCity(global::city_keys[global::city_combobox->getNowIdx()]);
}

// 画面サイズが変わっても、座標が混乱しないようにする
void reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
    glScaled(1, -1, 1);
    glTranslated(0, -h, 0);
}

Window::Window(int *argc, char *argv[], string title, Xy *size, void (*_display)(void), int _wait_ms)
{
    display = _display;
    // glutの初期化
    glutInit(argc, argv);

    // ウィンドウの初期化
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA | GLUT_DOUBLE);
    glutInitWindowSize(size->x, size->y);
    glutCreateWindow(title.c_str());

    // glutMainLoop関数を実行する際に呼ばれる関数
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(changeCity);
    wait_ms = _wait_ms;
    glutTimerFunc(wait_ms, timer, 0);
}

void Window::init() {
    // 初期描画
    display();
}

void Window::mainLoop() {
    // ウィンドウの描画
    glutMainLoop();
}