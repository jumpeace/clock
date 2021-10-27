#include "gl.h"

void Gl::color(Rgb* rgb)
{
    glColor3ub(rgb->r, rgb->g, rgb->b);
}
void Gl::clear_color(Rgba* rgba)
{
    auto gl_color = rgba->to_gl();
    glClearColor(gl_color["r"], gl_color["g"], gl_color["b"], gl_color["a"]);
}