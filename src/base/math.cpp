#include "math.h"

// n1進法からn2進法に変換
float math::n_ary_convertor(float src, float n1, float n2)
{
    return src * (n2 / n1);
}