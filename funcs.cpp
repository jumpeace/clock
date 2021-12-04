// 18411 川原隼平

#include "funcs.h"

#include <iomanip>

// n1進法からn2進法に変換
float funcs::nAryConvertor(float src, float n1, float n2)
{
    return src * (n2 / n1);
}

// int型からstring型に変換するときに、0埋めして出力する
string funcs::fillByZero(int src, int keta)
{
    // string型への変換を行う特殊なデータ型
    std::ostringstream s_out;
    // 0埋めをする
    s_out << setfill('0') << setw(keta) << src;
    // string型に変換
    return s_out.str();
}