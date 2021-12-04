// 18411 川原隼平

#ifndef _COLOR_H_
#define _COLOR_H_

#include <iostream>
using namespace std;
#include <map>

class Rgb
{
public:
    int r;
    int g;
    int b;
    Rgb(int, int, int);
    map<string, float> toGl();
};

class Rgba: public Rgb
{
public:
    int a;
    Rgba(int, int, int, int);
    map<string, float> toGl();
};

#endif
