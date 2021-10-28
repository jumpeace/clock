#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "cli/country.h"
#include "cli/city.h"
#include "cli/clock.h"
#include "gli/draw.h"
#include "gli/draw_pattern.h"

namespace global {
    extern map<string, Country *> countries;
    extern map<string, City *> cities;
    extern vector<string> city_keys;
    extern Clock* clock;
    extern Draw* draw;
    extern drawPattern::Combobox* city_combo;
}

#endif