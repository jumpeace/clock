// 18411 川原隼平

#ifndef _CITY_H_
#define _CITY_H_

#include <iostream>
#include "country.h"
using namespace std;

class City {
public:
    string name;
    Country* country;
    float time_diff;

    City (string, Country*, float);
};

#endif