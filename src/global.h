#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "cui/country.h"
#include "cui/city.h"
#include "cui/clock.h"
#include "gui/draw.h"
#include "gui/draw_pattern.h"
#include "gui/image.h"
#include "gui/window.h"

namespace global {
    extern Window* window;
    extern map<string, Country *> countries;
    extern map<string, City *> cities;
    extern vector<string> city_keys;
    extern Clock* clock;
    extern Draw* draw;
    extern drawPattern::Combobox* city_combo;
    extern map<string, Image*> images;
}

#endif