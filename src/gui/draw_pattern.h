#ifndef _DRAW_PATTERN_H_
#define _DRAW_PATTERN_H_

#include <vector>
#include "../base/dim.h"
#include "../base/color.h"

namespace drawPattern
{
    // 円を描画
    void circle(Xy *, float, Rgb *);
    // OpenGLのGL_LINESを使って線を描画
    void normalLine(Xy *, Xy *, Rgb *);
    // 線
    void circleLine(Xy *, Xy *, float, Rgb *);
    // 針を描画
    void clockNeedle(float, float, float, Rgb *);
    // 文字列
    void _text(string str, Xy *init_pos);

    // テキストボックス
    class Textbox
    {
    private:
        // テキストの最大文字数
        int text_num_max;

    public:
        // 一文字のサイズ
        float c_size;
        // テキスト
        string text;
        // 背景色
        Rgb *bg_color;
        // 枠線の色
        Rgb *border_color;
        // テキストの色
        Rgb *text_color;
        // 描画位置
        Xy *pos;
        // 枠線とテキストの間の余白の幅
        Xy *pad_size;
        // 枠線の幅
        Xy *border_size;

        Textbox(string, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
        // テキストボックスを描画
        void draw();
        // 描画位置を移動
        void rePos(Xy *);
        // テキストを設定
        void setText(string);
        // テキストボックスのサイズを取得
        Xy *size();
    };
    class Combobox
    {
    private:
        int now_text;
        int texts_num;

    public:
        float c_size;
        vector<string> texts;
        int text_num_max;
        Rgb *bg_color;
        Rgb *border_color;
        Rgb *text_color;
        Xy *pos;
        Xy *pad_size;
        Xy *border_size;
        Combobox(vector<string>, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
        void draw();
        bool set_now(int);
        int get_now();
        string get_now_text();
        int get_texts_num();
        bool isInLeftButton(Xy *);
        bool isInRightButton(Xy *);
        void rePos(Xy *);
        Xy *size();
    };
}

#endif