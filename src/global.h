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
    extern map<string, Country *> country_list;
    extern map<string, City *> city_list;
    extern vector<string> city_keys;
    extern Clock* clock;
    extern Draw* draw;
    extern drawPattern::Combobox* city_combobox;
    extern drawPattern::Textbox* date_textbox;
    extern map<string, Image*> images;
}

#endif