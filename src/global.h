#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <map>
#include <iostream>
using namespace std;

#include "cli/country.h"
#include "cli/city.h"
#include "cli/clock.h"
#include "gli/draw.h"

namespace global {
    map<string, Country *> countries;
    map<string, City *> cities;
    Clock* clock;
    Draw* draw;
}

#endif