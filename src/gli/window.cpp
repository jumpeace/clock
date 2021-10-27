#include <GL/glut.h>
#include "window.h"
#include "tool.h"

int wait_ms;

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(wait_ms, timer, 0);
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

void window::init(int *argc, char *argv[], string title, Xy* size, void(* display) (void), int _wait_ms) {
    // glutの初期化
    glutInit(argc, argv);

    // ウィンドウの初期化
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(size->x, size->y);

    // ウィンドウ作成
    glutCreateWindow(title.c_str());
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    wait_ms = _wait_ms;
    glutTimerFunc(wait_ms, timer, 0);

    // 初期描画
    display();

    // ウィンドウの描画
    glutMainLoop();
}