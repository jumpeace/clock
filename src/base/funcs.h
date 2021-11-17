#ifndef _MY_MATH_H_
#define _MY_MATH_H_

#include <iostream>
using namespace std;

namespace funcs {
    // n1進法からn2進法に変換
    float nAryConvertor(float, float, float);
    // int型からstring型に変換するときに、0埋めして出力する
    string fillByZero(int, int);
}

#endif