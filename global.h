// 18411 川原隼平

#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include <map>
#include <vector>
#include <iostream>
using namespace std;

#include "country.h"
#include "city.h"
#include "clock.h"
#include "draw.h"
#include "draw_pattern.h"
#include "window.h"

namespace global {
    extern Window* window;
    extern map<string, Country *> country_list;
    extern map<string, City *> city_list;
    extern vector<string> city_keys;
    extern Clock* clock;
    extern Draw* draw;
    extern drawPattern::Combobox* city_combobox;
    extern drawPattern::Textbox* date_textbox;
}

#endif