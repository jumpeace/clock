#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

string fill_by_zero(int src, int zero_num)
{
    std::ostringstream s_out;
    s_out << setfill('0') << setw(zero_num) << src;
    return s_out.str();
}

class Country
{
public:
    string _name;

    Country(string name)
    {
        _name = name;
    }
};

class City
{
public:
    string _name;
    Country *_country;
    bool _is_summer_time;
    int _time_diff;

    City(string name, Country *country, bool is_summer_time, int time_diff)
    {
        _name = name;
        _country = country;
        _is_summer_time = is_summer_time;
        _time_diff = time_diff;
    }
};

typedef struct {
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;
} Time;

int is_leap(int year) {
    return year % 400 == 0 || (!year % 100 == 0 && year % 4 == 0);
}

int get_day_in_mon(int year, int month) {
    switch (month)
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
        return (is_leap(year)) ? 29 : 28;
    default:
        return -1;
    }
}

class Clock
{
protected:
    vector<string> _wday_str_list = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    map<string, City *> _city_list;
    City *_now_city;

public:
    Time _utc_time;
    Time _city_time;

    Clock(map<string, City *> city_list, string city_list_key)
    {
        _city_list = city_list;
        _now_city = _city_list[city_list_key];

        record_utc_now();
    }

    bool set_city(string key)
    {
        if (_city_list.count(key) == 0)
        {
            return false;
        };

        _now_city = _city_list[key];

        return true;
    }


    // TODO 時差も加味する
    void record_utc_now()
    {
        time_t tt;

        time(&tt);
        // 世界標準時で取得
        auto ts = gmtime(&tt);

        _utc_time.year = ts->tm_year + 1900;
        _utc_time.mon = ts->tm_mon + 1;
        _utc_time.mday = ts->tm_mday;
        _utc_time.wday = ts->tm_wday;
        _utc_time.hour = ts->tm_hour;
        _utc_time.min = ts->tm_min;
        _utc_time.sec = ts->tm_sec;
    }

    void record_city_now() {
        record_utc_now();

        // 未テスト
        auto HOUR_IN_DAY = 24;
        auto DAY_IN_WEEK = 7;
        auto MON_IN_YEAR = 12;

        _city_time = _utc_time;

        _city_time.hour += _now_city->_time_diff;
        if (_city_time.hour < 0) {
            _city_time.wday--;
            if (_city_time.wday < 0) {
                _city_time.wday += DAY_IN_WEEK;
            }

            _city_time.mday--;
            if (_city_time.mday <= 0) {
                _city_time.mon--;
                if (_city_time.mon <= 0) {
                    _city_time.year--;

                    _city_time.mon += MON_IN_YEAR;
                }

                _city_time.mday += get_day_in_mon(_city_time.year, _city_time.mon);
            }

            _city_time.hour += HOUR_IN_DAY;
        }
        else if (_city_time.hour >= HOUR_IN_DAY) {
            _city_time.wday++;
            if (_city_time.wday >= DAY_IN_WEEK) {
                _city_time.wday -= DAY_IN_WEEK;
            }

            _city_time.mday++;
            if (_city_time.mday > get_day_in_mon(_city_time.year, _city_time.mon)) {

                _city_time.mon++;
                if (_city_time.mon > MON_IN_YEAR) {
                    _city_time.year++;

                    _city_time.mon -= MON_IN_YEAR;
                }
                _city_time.mday -= get_day_in_mon(_city_time.year, _city_time.mon);
            }

            _city_time.hour -= HOUR_IN_DAY;
        }
    }

    map<string, string> get_by_str_map()
    {
        map<string, string> str_map;

        str_map["country"] = _now_city->_country->_name;
        str_map["city"] = _now_city->_name;
        str_map["year"] = fill_by_zero(_city_time.year, 4);
        str_map["mon"] = fill_by_zero(_city_time.mon, 2);
        str_map["mday"] = fill_by_zero(_city_time.mday, 2);
        str_map["wday"] = _wday_str_list[_city_time.wday];
        str_map["hour"] = fill_by_zero(_city_time.hour, 2);
        str_map["min"] = fill_by_zero(_city_time.min, 2);
        str_map["sec"] = fill_by_zero(_city_time.sec, 2);

        return str_map;
    }

    map<string, int> get_by_int_map()
    {
        map<string, int> int_map;

        int_map["year"] = _city_time.year;
        int_map["mon"] = _city_time.mon;
        int_map["mday"] = _city_time.mday;
        int_map["wday"] = _city_time.wday;
        int_map["hour"] = _city_time.hour;
        int_map["min"] = _city_time.min;
        int_map["sec"] = _city_time.sec;

        return int_map;
    }
};


void display_clock(map<string, string> clock_str_map)
{
    auto clock_str = clock_str_map["country"] + ", " + clock_str_map["city"] + " | " + clock_str_map["year"] + "/" + clock_str_map["mon"] + "/" + clock_str_map["mday"] + "(" + clock_str_map["wday"] + ")" + clock_str_map["hour"] + ":" + clock_str_map["min"] + ":" + clock_str_map["sec"];
    cout << clock_str << endl;
}

int main(int argc, char *argv[])
{
    map<string, Country *> country_list;
    country_list["usa"] = new Country("USA");
    country_list["ingland"] = new Country("Ingland");
    country_list["japan"] = new Country("Japan");

    map<string, City *> city_list;
    city_list["tokyo"] = new City("Tokyo", country_list["japan"], false, 9);
    city_list["london"] = new City("London", country_list["usa"], false, 0);
    city_list["new-york"] = new City("New York", country_list["usa"], false, -5);
    city_list["san-francisco"] = new City("San Francisco", country_list["usa"], false, -8);

    Clock *clock = new Clock(city_list, "new-york");

    clock->record_city_now();
    display_clock(clock->get_by_str_map());

    if (clock->set_city("tokyo"))
    {
        clock->record_city_now();
        display_clock(clock->get_by_str_map());
    }

    return 0;
}
