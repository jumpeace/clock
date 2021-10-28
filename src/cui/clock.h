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

public:
    Time *utc_time;
    Time *city_time;
    Clock(map<string, City*>, string);

    bool set_city(string);
    City* get_now_city();

    void record_now();

    map<string, string> get_city_time_by_str_map();
};

#endif