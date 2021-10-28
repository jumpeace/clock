#include <GL/glut.h>
#include <iostream>
#include "window.h"
#include "tool.h"
#include "../global.h"
#include "draw_pattern.h"

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
    // cout << x << ", " << y << "\n";
    if (global::city_combo->isInLeftButton(new Xy(x, y))) {
        global::city_combo->set_now(
            (global::city_combo->get_now() + global::city_combo->get_texts_num() - 1) % global::city_combo->get_texts_num());
    }
    else if (global::city_combo->isInRightButton(new Xy(x, y))) {
        global::city_combo->set_now(
            (global::city_combo->get_now() + 1) % global::city_combo->get_texts_num());
    }
    global::clock->set_city(global::city_keys[global::city_combo->get_now()]);
    // drawPattern::_str(text, new Xy(start_pos->x + pad_size->x, start_pos->y + pad_size->y + c_size));
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

void window::init(int *argc, char *argv[], string title, Xy *size, void (*display)(void), int _wait_ms)
{
    // glutの初期化
    glutInit(argc, argv);

    // ウィンドウの初期化
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(size->x, size->y);

    // ウィンドウ作成
    glutCreateWindow(title.c_str());
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseFunc);
    wait_ms = _wait_ms;
    glutTimerFunc(wait_ms, timer, 0);

    // 初期描画
    display();

    // ウィンドウの描画
    glutMainLoop();
}