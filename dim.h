// 18411 川原隼平

#ifndef _DIM_H_
#define _DIM_H_

class Xy
{
public:
    float x;
    float y;
    Xy(float, float);
    // 引数によって一意に決まる正方形に入っているか
    bool isIn(Xy*, Xy*);
};


#endif