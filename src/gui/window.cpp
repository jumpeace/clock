#include <GL/glut.h>
#include <GL/glpng.h>
#include <iostream>
#include "window.h"
#include "tool.h"
#include "../global.h"
#include "draw_pattern.h"
#include "image.h"

int wait_ms;

void timer(int value)
{
    glutPostRedisplay();
    glutTimerFunc(wait_ms, timer, 0);
}

void mouseFunc(int button, int state, int x, int y)
{
    if (button != GLUT_LEFT_BUTTON || state != GLUT_DOWN)
        return;
    if (global::city_combo->isInLeftButton(new Xy(x, y))) {
        global::city_combo->set_now(
            (global::city_combo->get_now() + global::city_combo->get_texts_num() - 1) % global::city_combo->get_texts_num());
    }
    else if (global::city_combo->isInRightButton(new Xy(x, y))) {
        global::city_combo->set_now(
            (global::city_combo->get_now() + 1) % global::city_combo->get_texts_num());
    }
    global::clock->set_city(global::city_keys[global::city_combo->get_now()]);
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
    glutInitDisplayMode(GLUT_RGBA | GLUT_ALPHA);
    glutInitWindowSize(size->x, size->y);

    // TODO image初期化

    // ウィンドウ作成
    glutCreateWindow(title.c_str());
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunc);
    wait_ms = _wait_ms;
    glutTimerFunc(wait_ms, timer, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    global::images["1"] = new Image("img/1.png");
    global::images["2"] = new Image("img/2.png");
    global::images["3"] = new Image("img/3.png");
    global::images["4"] = new Image("img/4.png");
    global::images["5"] = new Image("img/5.png");
    global::images["6"] = new Image("img/6.png");
    global::images["7"] = new Image("img/7.png");
    global::images["8"] = new Image("img/8.png");
    global::images["9"] = new Image("img/9.png");
    global::images["10"] = new Image("img/10.png");
    global::images["11"] = new Image("img/11.png");
    global::images["12"] = new Image("img/12.png");
}

void Window::init() {
    // 初期描画
    display();
}

void Window::mainLoop() {
    // ウィンドウの描画
    glutMainLoop();
}