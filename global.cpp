#include "global.h"

namespace global {
    Window* window;
    map<string, Country *> country_list;
    map<string, City *> city_list;
    vector<string> city_keys;
    Clock* clock;
    Draw* draw;
    drawPattern::Combobox* city_combobox;
    drawPattern::Textbox* date_textbox;
}