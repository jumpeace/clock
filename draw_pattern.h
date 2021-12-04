#ifndef _DRAW_PATTERN_H_
#define _DRAW_PATTERN_H_

#include <vector>
#include "dim.h"
#include "color.h"

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
    // テキストを描画
    void text(string str, Xy *init_pos);

    // テキストボックス
    class Textbox
    {
    private:
        // テキストの最大文字数
        int text_num_max;
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

    public:

        Textbox(string, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
        // テキストボックスを描画
        void draw();

        // 描画位置を移動
        void rePos(Xy *);
        // テキストボックスのサイズを取得
        Xy *size();

        // テキストを設定
        void setText(string);
    };
    class Combobox
    {
    private:
        // テキストの最大文字数
        int text_num_max;
        // 描画対象のテキストの要素番号
        int now_idx;
        // 格納されているテキストの個数
        int texts_num;
        // 一文字のサイズ
        float c_size;
        // 描画するテキストの一覧
        vector<string> texts;
        // 背景色
        Rgb *bg_color;
        // 枠線の色
        Rgb *border_color;
        // テキストの色
        Rgb *text_color;
        // 描画位置
        Xy *pos;
        // 余白の幅
        Xy *pad_size;
        // 枠線の幅
        Xy *border_size;

    public:

        Combobox(vector<string>, int, Rgb *, Rgb *, Rgb *, Xy *, Xy *, Xy *);
        // コンボボックスを描画
        void draw();

        // 描画位置を移動
        void rePos(Xy *);
        // コンボボックスのサイズを取得
        Xy *size();

        // 描画対象のテキストの要素番号を変更
        bool setNowIdx(int);
        // 描画対象のテキストの要素番号を取得
        int getNowIdx();
        // 描画対象のテキストを取得
        string getNowIdxText();

        // インスタンス変数 texts_num の ゲッター
        int getTextsNum();

        // 左のボタンの処理
        void leftButtonProc(int, int, Xy *, void(*)(void));
        // 右のボタンの処理
        void rightButtonProc(int, int, Xy *, void(*)(void));
    };
}

#endif