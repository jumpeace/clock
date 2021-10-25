#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <iostream>
#include <map>
using namespace std;

#include "city.h"
#include "time.h"


class Clock
{
protected:
    map<string, City *> cities;
    City *now_city;
    Time *utc_time;
    Time *city_time;

public:
    Clock(map<string, City*>, string);

    bool set_city(string);

    void record_now();

    map<string, int> get_city_time_by_int_map();
    map<string, string> get_city_time_by_str_map();
};

#endif