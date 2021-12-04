// 18411 川原隼平

#ifndef _CLOCK_H_
#define _CLOCK_H_

#include <iostream>
#include <map>
#include <vector>
using namespace std;

#include "city.h"

class Time_
{
public:
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;

    Time_(int, int, int, int, int, int, int);
    // 曜日を文字列(英語)で取得する
    string getWdayByStr();
    // 閏年かどうかを判定する
    bool isLeap();
    // 任意の月の日数を取得する
    int getDayInMon();
    // 午前かどうかを判定する
    bool isMorning();
    // 文字列で日時の情報を取得する
    map<string, string> getByStrList();
};


class Clock
{
protected:
    map<string, City *> city_list;
    City *now_city;

public:
    Time_ *utc_time;
    Time_ *city_time;
    
    Clock(map<string, City*>, string);
    // 時刻を取得する都市を変更する。
    bool setCity(string);
    // 現在の都市を取得する
    City* getNowIdxCity();
    // 現在時刻を記録する
    void recordNow();
    // 文字列で都市の時刻を取得する
    map<string, string> getCityTime_ByStrList();
};

#endif