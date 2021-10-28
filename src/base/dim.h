#ifndef _DIM_H_
#define _DIM_H_

class Xy
{
public:
    float x;
    float y;
    Xy(float, float);
    bool isIn(Xy*, Xy*);
};


#endif