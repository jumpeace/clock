#include "image.h"

#include <cmath>

#include "my_gl.h"
#include "../base/color.h"

// OpenGLで画像の描画を可能にする
void Image::init() {
    // テクスチャのアルファチャンネルを有効にする
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC0_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Image::Image(string filename) {
    img = pngBind(filename.c_str(), PNG_NOMIPMAP, PNG_ALPHA, &info, GL_CLAMP, GL_NEAREST, GL_NEAREST);
}

// 画像を描画する(位置調整、回転、大きさ調整が可能)
void Image::putSprite(Xy* pos, float scale, float angle) {
    auto size = new Xy(info.Width * scale, info.Height * scale);

    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, img);
    Gl::color4(new Rgba(255, 255, 255, 255));

    glBegin(GL_QUADS);

    // Aの座標を計算
    glTexCoord2i(0, 0);
    glVertex2i(pos->x - size->x * 0.5 * cos(angle) + size->y * 0.5 * sin(angle),
    pos->y - size->x * 0.5 * sin(angle) - size->y * 0.5 * cos(angle)
    );

    // Bの座標を計算
    glTexCoord2i(0, 1);
    glVertex2i(pos->x - size->x * 0.5 * cos(angle) - size->y * 0.5 * sin(angle), 
    pos->y - size->x * 0.5 * sin(angle) + size->y * 0.5 * cos(angle));

    // Cの座標を計算
    glTexCoord2i(1, 1);
    glVertex2i(pos->x + size->x * 0.5 * cos(angle) - size->y * 0.5 * sin(angle),
    pos->y + size->x * 0.5 * sin(angle) + size->y * 0.5 * cos(angle)
    );

    // Dの座標を計算
    glTexCoord2i(1, 0);
    glVertex2i(pos->x + size->x * 0.5 * cos(angle) + size->y * 0.5 * sin(angle), 
    pos->y + size->x * 0.5 * sin(angle) - size->y * 0.5 * cos(angle));

    glEnd();

    glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}