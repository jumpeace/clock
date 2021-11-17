#ifndef _TIME_H_
#define _TIME_H_

#include <iostream>
#include <map>
#include <vector>
using namespace std;

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

#endif