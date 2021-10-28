#include "dim.h"

Xy::Xy(float _x, float _y)
{
    x = _x;
    y = _y;
}

bool Xy::isIn(Xy* min, Xy* max) {
    if (x < min->x|| x > max->x) return false;
    if (y < min->y|| y > max->y) return false;
    return true;
}