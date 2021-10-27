#include <GL/glut.h>
#include "window.h"
#include "tool.h"

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

void window_init(int *argc, char *argv[], Xy* size, void(* display) (void)) {
    // glutの初期化
    glutInit(argc, argv);

    // ウィンドウの初期化
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize(size->x, size->y);

    // ウィンドウ作成
    glutCreateWindow("sample1");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);

    // 初期描画
    display();

    // ウィンドウの描画
    glutMainLoop();
}