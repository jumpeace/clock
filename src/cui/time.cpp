#include "time.h"
#include "../base/funcs.h"

Time::Time(int _year, int _mon, int _mday, int _wday, int _hour, int _min, int _sec)
{
    year = _year;
    mon = _mon;
    mday = _mday;
    wday = _wday;
    hour = _hour;
    min = _min;
    sec = _sec;
}

// 曜日を文字列(英語)で取得する
string Time::getWdayByStr()
{
    vector<string> wday_by_str_list = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return wday_by_str_list[wday];
}


// 閏年かどうかを判定する
bool Time::isLeap()
{
    return year % 400 == 0 || (!year % 100 == 0 && year % 4 == 0);
}

// 任意の月の日数を取得する
int Time::getDayInMon()
{
    switch (mon)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;

    case 4:
    case 6:
    case 9:
    case 11:
        return 30;

    case 2:
        return (isLeap()) ? 29 : 28;

    default:
        return -1;
    }
}

// 午前どうかを判定する
bool Time::isMorning() {
    return hour / 12 == 0;
}

// 文字列で日時の情報を取得する
map<string, string> Time::getByStrList()
{
    map<string, string> str_list;

    str_list["year"] = funcs::fillByZero(year, 4);
    str_list["mon"] = funcs::fillByZero(mon, 2);
    str_list["mday"] = funcs::fillByZero(mday, 2);
    str_list["wday"] = getWdayByStr();
    str_list["hour"] = funcs::fillByZero(hour, 2);
    str_list["min"] = funcs::fillByZero(min, 2);
    str_list["sec"] = funcs::fillByZero(sec, 2);

    return str_list;
}
