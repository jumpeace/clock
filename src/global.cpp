#include "global.h"

namespace global {
    Window* window;
    map<string, Country *> countries;
    map<string, City *> cities;
    vector<string> city_keys;
    Clock* clock;
    Draw* draw;
    drawPattern::Combobox* city_combo;
    map<string, Image*> images;
}