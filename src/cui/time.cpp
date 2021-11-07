#include "time.h"

string fill_by_zero(int src, int zero_num)
{
    std::ostringstream s_out;
    s_out << setfill('0') << setw(zero_num) << src;
    return s_out.str();
}

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
    map<string, string> str_map;

    str_map["year"] = fill_by_zero(year, 4);
    str_map["mon"] = fill_by_zero(mon, 2);
    str_map["mday"] = fill_by_zero(mday, 2);
    str_map["wday"] = getWdayByStr();
    str_map["hour"] = fill_by_zero(hour, 2);
    str_map["min"] = fill_by_zero(min, 2);
    str_map["sec"] = fill_by_zero(sec, 2);

    return str_map;
}
