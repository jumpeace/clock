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

class Clock
{
protected:
    vector<string> _wday_str_list = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    map<string, City *> _city_list;
    City *_now_city;

    // TODO 時差も加味する
    void record_now()
    {
        time_t tt;
        struct tm *ts;

        time(&tt);
        ts = localtime(&tt);

        _year = ts->tm_year + 1900;
        _mon = ts->tm_mon + 1;
        _mday = ts->tm_mday;
        _hour = ts->tm_hour;
        _min = ts->tm_min;
        _sec = ts->tm_sec;
        _wday = ts->tm_wday;
    }

    map<string, string> get_by_str_map()
    {
        map<string, string> str_map;

        str_map["country"] = _now_city->_country->_name;
        str_map["city"] = _now_city->_name;
        str_map["year"] = fill_by_zero(_year, 4);
        str_map["mon"] = fill_by_zero(_mon, 2);
        str_map["mday"] = fill_by_zero(_mday, 2);
        str_map["wday"] = _wday_str_list[_wday];
        str_map["hour"] = fill_by_zero(_hour, 2);
        str_map["min"] = fill_by_zero(_min, 2);
        str_map["sec"] = fill_by_zero(_sec, 2);

        return str_map;
    }

public:
    int _year;
    int _mon;
    int _mday;
    int _wday;
    int _hour;
    int _min;
    int _sec;

    Clock(map<string, City *> city_list, string city_list_key)
    {
        _city_list = city_list;
        _now_city = _city_list[city_list_key];

        record_now();
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

    map<string, string> get_now()
    {
        record_now();
        return get_by_str_map();
    }
};

void display_clock(map<string, string> clock_str_map)
{
    string clock_str = clock_str_map["country"] + ", " + clock_str_map["city"] + " | " + clock_str_map["year"] + "/" + clock_str_map["mon"] + "/" + clock_str_map["mday"] + "(" + clock_str_map["wday"] + ")" + clock_str_map["hour"] + ":" + clock_str_map["min"] + ":" + clock_str_map["sec"];
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

    display_clock(clock->get_now());

    if (clock->set_city("tokyo"))
    {
        display_clock(clock->get_now());
    }

    return 0;
}
