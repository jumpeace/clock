#include <stdio.h>
#include "country.h"
#include "city.h"
#include "time.h"
#include "clock.h"

void display_clock(Str_Time time_str)
{
    printf("%s/%s/%s(%s) %s:%s:%s\n",
           time_str.year, time_str.mon, time_str.mday, time_str.wday,
           time_str.hour, time_str.min, time_str.sec);
}

int main(int argc, char const *argv[])
{
    Map_Country country_list = Map_Country__new();

    Map_Country__add(&country_list, "usa", Country__new("USA"));
    Map_Country__add(&country_list, "ingland", Country__new("Ingland"));
    Map_Country__add(&country_list, "japan", Country__new("Japan"));

    Map_City city_list = Map_City__new();
    Map_City__add(&city_list, "tokyo", City__new("Tokyo", Map_Country__find(country_list, "japan"), 9));
    Map_City__add(&city_list, "london", City__new("London", Map_Country__find(country_list, "ingland"), 0));
    Map_City__add(&city_list, "new-york", City__new("New York", Map_Country__find(country_list, "usa"), -5));
    Map_City__add(&city_list, "san-francisco", City__new("San Francisco", Map_Country__find(country_list, "usa"), -8));

    Clock clock = Clock__new(city_list, "new-york");
    if (!clock.is_exists)
        return -1;

    Clock__record_now(&clock);
    display_clock(Str_Time__new(clock.city_time));

    if (!Clock__set_city(&clock, "tokyo"))
        return -1;
    Clock__record_now(&clock);
    display_clock(Str_Time__new(clock.city_time));

    return 0;
}
