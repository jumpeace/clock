#include "image.h"
#include "tool.h"
#include "../base/color.h"

void Image::init() {
    // テクスチャのアルファチャンネルを有効にする
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Image::Image(string filename) {
    img = pngBind(filename.c_str(), PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
}

void Image::putSprite(Xy* pos) {
    auto size = new Xy(info.Width, info.Height);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, img);
    Gl::color4(new Rgba(255, 255, 255, 255));

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(pos->x, pos->y);

    glTexCoord2i(0, 1);
    glVertex2i(pos->x, pos->y + size->y);

    glTexCoord2i(1, 1);
    glVertex2i(pos->x + size->x, pos->y + size->y);

    glTexCoord2i(0, 1);
    glVertex2i(pos->x + size->x, pos->y);

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}