#include "my_gl.h"

Xy* Gl::windowSize() {
    return new Xy(
        glutGet(GLUT_WINDOW_WIDTH),
        glutGet(GLUT_WINDOW_HEIGHT)
    );
}

Xy* Gl::centerPos() {
    auto window_size = Gl::windowSize();
    return new Xy(
        window_size->x / 2.0,
        window_size->y / 2.0
    );
}

void Gl::color3(Rgb* rgb)
{
    glColor3ub(rgb->r, rgb->g, rgb->b);
}
void Gl::color4(Rgba* rgba)
{
    glColor4ub(rgba->r, rgba->g, rgba->b, rgba->a);
}
void Gl::clearColor(Rgba* rgba)
{
    auto gl_color = rgba->toGl();
    glClearColor(gl_color["r"], gl_color["g"], gl_color["b"], gl_color["a"]);
}