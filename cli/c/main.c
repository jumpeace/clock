#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define true 1
#define false 0
typedef int bool;

typedef struct
{
    bool is_exists;
    char name[64];
} Country;

Country Country__not_found()
{
    Country instance;
    instance.is_exists = false;
    return instance;
}

Country Country__new(const char name[64])
{
    Country instance = Country__not_found();

    strcpy(instance.name, name);

    instance.is_exists = true;
    return instance;
}

typedef struct
{
    bool is_exists;
    char k[32][16];
    Country v[32];
    int len;
} Map_Country;

Map_Country Map_Country__not_found()
{
    Map_Country instance;
    instance.is_exists = false;
    return instance;
}

Map_Country Map_Country__new()
{
    Map_Country instance = Map_Country__not_found();

    instance.len = 0;

    instance.is_exists = true;
    return instance;
}

bool Map_Country__add(Map_Country *instance, const char key[16], Country value)
{
    if (instance->len >= 64)
    {
        return true;
    }
    instance->len++;

    strcpy(instance->k[instance->len - 1], key);
    instance->v[instance->len - 1] = value;

    return false;
}

Country Map_Country__find(Map_Country *instance, const char key[16])
{
    for (int i = 0; i < instance->len; i++)
    {
        if (strcmp(instance->k[i], key) == 0)
        {
            return instance->v[i];
        }
    }

    return Country__not_found();
}

typedef struct
{
    bool is_exists;
    char name[64];
    Country country;
    int time_diff;
} City;

City City__not_found()
{
    City instance;
    instance.is_exists = false;
    return instance;
}

City City__new(const char name[64], Country country, int time_diff)
{
    City instance = City__not_found();

    instance.time_diff = time_diff;
    strcpy(instance.name, name);
    instance.country = country;

    instance.is_exists = true;
    return instance;
}

typedef struct
{
    bool is_exists;
    char k[32][16];
    City v[32];
    int len;
} Map_City;

Map_City Map_City__not_found()
{
    Map_City instance;
    instance.is_exists = false;
    return instance;
}

Map_City Map_City__new()
{
    Map_City instance = Map_City__not_found();

    instance.len = 0;

    instance.is_exists = true;
    return instance;
}

int Map_City__add(Map_City *instance, const char key[16], City value)
{
    if (instance->len >= 64)
    {
        return true;
    }
    instance->len++;

    strcpy(instance->k[instance->len - 1], key);
    instance->v[instance->len - 1] = value;

    return false;
}

City Map_City__find(Map_City *instance, const char key[16])
{
    for (int i = 0; i < instance->len; i++)
    {
        if (strcmp(instance->k[i], key) == 0)
        {
            return instance->v[i];
        }
    }

    return City__not_found();
}

typedef struct
{
    bool is_exists;
    int year;
    int mon;
    int mday;
    int wday;
    int hour;
    int min;
    int sec;
} Time;

Time Time__not_found()
{
    Time instance;
    instance.is_exists = false;
    return instance;
}

Time Time__new(int year, int mon, int mday, int wday, int hour, int min, int sec)
{
    Time instance = Time__not_found();

    instance.year = year;
    instance.mon = mon;
    instance.mday = mday;
    instance.wday = wday;
    instance.hour = hour;
    instance.min = min;
    instance.sec = sec;

    instance.is_exists = true;
    return instance;
}

void Time__get_wday(Time instance, char wday_str[64])
{
    char wday_str_list[7][20] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    strcpy(wday_str, wday_str_list[instance.wday]);
}

int Time__is_leap(Time instance)
{
    return instance.year % 400 == 0 || (!instance.year % 100 == 0 && instance.year % 4 == 0);
}

int Time__get_day_in_mon(Time instance)
{
    switch (instance.mon)
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
        return (Time__is_leap(instance)) ? 29 : 28;

    default:
        return -1;
    }
}

typedef struct
{
    bool is_exists;
    char year[16];
    char mon[16];
    char mday[16];
    char wday[64];
    char hour[16];
    char min[16];
    char sec[16];
} TimeStr;

TimeStr TimeStr__not_found()
{
    TimeStr instance;
    instance.is_exists = false;
    return instance;
}

TimeStr TimeStr__new(Time time)
{
    TimeStr instance = TimeStr__not_found();

    sprintf(instance.year, "%04d", time.year);
    sprintf(instance.mon, "%02d", time.mon);
    sprintf(instance.mday, "%02d", time.mday);
    Time__get_wday(time, instance.wday);
    sprintf(instance.hour, "%02d", time.hour);
    sprintf(instance.min, "%02d", time.min);
    sprintf(instance.sec, "%02d", time.sec);

    instance.is_exists = true;
    return instance;
}

typedef struct
{
    bool is_exists;
    Map_City city_list;
    City now_city;
    Time utc_time;
    Time city_time;
} Clock;

Clock Clock__not_found()
{
    Clock instance;
    instance.is_exists = false;
    return instance;
}

bool Clock__set_city(Clock *instance, const char city_list_key[16])
{
    City now_city_tmp;
    now_city_tmp = Map_City__find(&instance->city_list, city_list_key);
    if (!now_city_tmp.is_exists)
        return false;

    instance->now_city = now_city_tmp;

    return true;
}

Clock Clock__new(Map_City city_list, const char city_list_key[16])
{
    Clock instance = Clock__not_found();

    instance.city_list = city_list;
    if (!Clock__set_city(&instance, city_list_key))
        return instance;

    instance.is_exists = true;
    return instance;
}

void Clock__record_now(Clock *instance)
{
    // 世界標準時の取得
    time_t tt;

    time(&tt);
    // 世界標準時で取得
    struct tm *ts = gmtime(&tt);

    instance->utc_time.year = ts->tm_year + 1900;
    instance->utc_time.mon = ts->tm_mon + 1;
    instance->utc_time.mday = ts->tm_mday;
    instance->utc_time.wday = ts->tm_wday;
    instance->utc_time.hour = ts->tm_hour;
    instance->utc_time.min = ts->tm_min;
    instance->utc_time.sec = ts->tm_sec;

    // 時差の計算
    int HOUR_IN_DAY = 24;
    int DAY_IN_WEEK = 7;
    int MON_IN_YEAR = 12;

    instance->city_time = instance->utc_time;

    instance->city_time.hour += instance->now_city.time_diff;
    instance->utc_time.hour, instance->city_time.hour, instance->now_city.time_diff;
    if (instance->city_time.hour < 0)
    {
        instance->city_time.wday--;
        if (instance->city_time.wday < 0)
        {
            instance->city_time.wday += DAY_IN_WEEK;
        }

        instance->city_time.mday--;
        if (instance->city_time.mday <= 0)
        {
            instance->city_time.mon--;
            if (instance->city_time.mon <= 0)
            {
                instance->city_time.year--;

                instance->city_time.mon += MON_IN_YEAR;
            }

            instance->city_time.mday += Time__get_day_in_mon(instance->city_time);
        }

        instance->city_time.hour += HOUR_IN_DAY;
    }
    else if (instance->city_time.hour >= HOUR_IN_DAY)
    {
        instance->city_time.wday++;
        if (instance->city_time.wday >= DAY_IN_WEEK)
        {
            instance->city_time.wday -= DAY_IN_WEEK;
        }

        instance->city_time.mday++;
        if (instance->city_time.mday > Time__get_day_in_mon(instance->city_time))
        {

            instance->city_time.mon++;
            if (instance->city_time.mon > MON_IN_YEAR)
            {
                instance->city_time.year++;

                instance->city_time.mon -= MON_IN_YEAR;
            }
            instance->city_time.mday -= Time__get_day_in_mon(instance->city_time);
        }

        instance->city_time.hour -= HOUR_IN_DAY;
    }
}

void display_clock(TimeStr time_str)
{
    printf("%s/%s/%s(%s) %s:%s:%s\n",
        time_str.year, time_str.mon, time_str.mday, time_str.wday,
        time_str.hour, time_str.min, time_str.sec);
}

int main(int argc, char const *argv[])
{
    Map_Country country_list = Map_Country__new();
    Country country;

    Map_Country__add(&country_list, "usa", Country__new("USA"));
    Map_Country__add(&country_list, "ingland", Country__new("Ingland"));
    Map_Country__add(&country_list, "japan", Country__new("Japan"));

    Map_City city_list = Map_City__new();
    Map_City__add(&city_list, "tokyo", City__new("Tokyo", Map_Country__find(&country_list, "japan"), 9));
    Map_City__add(&city_list, "london", City__new("London", Map_Country__find(&country_list, "ingland"), 0));
    Map_City__add(&city_list, "new-york", City__new("New York", Map_Country__find(&country_list, "usa"), -5));
    Map_City__add(&city_list, "san-francisco", City__new("San Francisco", Map_Country__find(&country_list, "usa"), -8));

    Clock clock = Clock__new(city_list, "new-york");
    if (!clock.is_exists)
        return -1;

    Clock__record_now(&clock);
    display_clock(TimeStr__new(clock.city_time));

    if (!Clock__set_city(&clock, "tokyo"))
        return -1;
    Clock__record_now(&clock);
    display_clock(TimeStr__new(clock.city_time));

    return 0;
}
