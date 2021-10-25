#ifndef _CITY_H_
#define _CITY_H_

#include <iostream>
#include "country.h"
using namespace std;

class City {
public:
    string name;
    Country* country;
    int time_diff;

    City (string, Country*, int);
};

#endif