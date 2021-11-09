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
    map<string, City *> city_list;
    City *now_city;

public:
    Time *utc_time;
    Time *city_time;
    
    Clock(map<string, City*>, string);
    // 時刻を取得する都市を変更する。
    bool setCity(string);
    // 現在の都市を取得する
    City* getNowIdxCity();
    // 現在時刻を記録する
    void recordNow();
    // 文字列で都市の時刻を取得する
    map<string, string> getCityTimeByStrList();
};

#endif