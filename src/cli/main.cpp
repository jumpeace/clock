#include <iostream>
#include <map>
using namespace std;

#include "country.h"
#include "city.h"
#include "time.h"
#include "clock.h"


void display_clock(map<string, string> time_str_map)
{
    auto clock_str = time_str_map["year"] + "/" + time_str_map["mon"] + "/" + time_str_map["mday"] + "(" + time_str_map["wday"] + ")" + time_str_map["hour"] + ":" + time_str_map["min"] + ":" + time_str_map["sec"];
    cout << clock_str << endl;
}

int main(int argc, char *argv[])
{
    map<string, Country*> country_map;

    country_map["usa"] = new Country("USA");
    country_map["ingland"] = new Country("Ingland");
    country_map["japan"] = new Country("Japan");

    map<string, City*> city_map;

    city_map["tokyo"] = new City("Tokyo", country_map["japan"], 9);
    city_map["london"] = new City("London", country_map["ingland"], 0);
    city_map["new-york"] = new City("New York", country_map["usa"], -5);
    city_map["san-francisco"] = new City("San Francisco", country_map["usa"], -8);

    Clock* clock = new Clock(city_map, "new-york");

    clock->record_now();

    display_clock(clock->get_city_time_by_str_map());

    if (!clock->set_city("tokyo"))
        return -1;
    clock->record_now();
    display_clock(clock->get_city_time_by_str_map());

    return 0;
}
