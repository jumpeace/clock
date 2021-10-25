#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>
#include <map>
#include <vector>
#include <iomanip>
using namespace std;

string fill_by_zero(int, int);

class Time
{
public:
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;

    Time(int, int, int, int, int, int, int);
    // 曜日を文字列(英語)で取得する
    string get_wday_by_str();
    // 閏年かどうか判定する
    int is_leap();
    // 任意の月の日数を取得する
    int get_day_in_mon();
    map<string, int> get_by_int_map();
    map<string, string> get_by_str_map();
};

#endif