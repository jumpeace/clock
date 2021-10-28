#ifndef _DRAW_PATTERN_H_
#define _DRAW_PATTERN_H_

#include <vector>
#include "../base/dim.h"
#include "../base/color.h"

namespace drawPattern
{
    // 塗りつぶされた円を描画
    void circle(Xy *, float, Rgb *);
    // 針を描画
    void clock_needle(float, float, float, Rgb *);
    // 文字列
    void _str(string str, Xy *init_pos);
    void textbox(string, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
    class Combobox {
    private:
        int now_text;
        int texts_num;
    public:
        float c_size;
        vector<string> texts;
        int text_num_max;
        Rgb* bg_color;
        Rgb* border_color;
        Rgb* text_color;
        Xy *start_pos;
        Xy *pad_size;
        Xy *border_size;
        Combobox(vector<string>, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
        void draw();
        bool set_now(int);
        int get_now();
        string get_now_text();
        int get_texts_num();
        bool isInLeftButton(Xy*);
        bool isInRightButton(Xy*);
    };
}

#endif