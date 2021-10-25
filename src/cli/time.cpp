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

string Time::get_wday_by_str()
{
    vector<string> wday_by_str_list = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return wday_by_str_list[wday];
}


// 閏年かどうか判定する
int Time::is_leap()
{
    return year % 400 == 0 || (!year % 100 == 0 && year % 4 == 0);
}

// 任意の月の日数を取得する
int Time::get_day_in_mon()
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
        return (is_leap()) ? 29 : 28;

    default:
        return -1;
    }
}

map<string, int> Time::get_by_int_map()
{
    map<string, int> str_map;

    str_map["year"] = year;
    str_map["mon"] = mon;
    str_map["mday"] = mday;
    str_map["wday"] = wday;
    str_map["hour"] = hour;
    str_map["min"] = min;
    str_map["sec"] = sec;

    return str_map;
}

map<string, string> Time::get_by_str_map()
{
    map<string, string> str_map;

    str_map["year"] = fill_by_zero(year, 4);
    str_map["mon"] = fill_by_zero(mon, 2);
    str_map["mday"] = fill_by_zero(mday, 2);
    str_map["wday"] = get_wday_by_str();
    str_map["hour"] = fill_by_zero(hour, 2);
    str_map["min"] = fill_by_zero(min, 2);
    str_map["sec"] = fill_by_zero(sec, 2);

    return str_map;
}
