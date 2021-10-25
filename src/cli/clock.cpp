#include "clock.h"

Clock::Clock(map<string, City*> _cities, string init_city_key)
{
    cities = _cities;
    if (!set_city(init_city_key)) {
        return;
    }
}

bool Clock::set_city(string city_key)
{
    if (cities.count(city_key) == 0)
    {
        return false;
    }
    now_city = cities[city_key];

    return true;
}

void Clock::record_now()
{ 
    // --- 世界標準時で取得するゾーン ---
    time_t tt;

    time(&tt);
    struct tm *ts = gmtime(&tt);

    utc_time = new Time(
        ts->tm_year + 1900,
        ts->tm_mon + 1,
        ts->tm_mday,
        ts->tm_wday,
        ts->tm_hour,
        ts->tm_min,
        ts->tm_sec
    );

    // --- 時差を計算するゾーン ---
    int HOUR_IN_DAY = 24; // 1日の時間
    int DAY_IN_WEEK = 7;  // 1週間の日数
    int MON_IN_YEAR = 12; // 1ヶ月の日数

    // とりあえず世界標準時の時間をディープコピー
    city_time = utc_time;

    // 時間だけに時差を反映
    city_time->hour += now_city->time_diff;

    // 時間を変更したことによって、日にち,曜日,月,年が変わる場合は修正
    if (city_time->hour < 0)
    {
        city_time->wday--;
        if (city_time->wday < 0)
        {
            city_time->wday += DAY_IN_WEEK;
        }

        city_time->mday--;
        if (city_time->mday <= 0)
        {
            city_time->mon--;
            if (city_time->mon <= 0)
            {
                city_time->year--;

                city_time->mon += MON_IN_YEAR;
            }

            city_time->mday += city_time->get_day_in_mon();
        }

        city_time->hour += HOUR_IN_DAY;
    }
    else if (city_time->hour >= HOUR_IN_DAY)
    {
        city_time->wday++;
        if (city_time->wday >= DAY_IN_WEEK)
        {
            city_time->wday -= DAY_IN_WEEK;
        }

        city_time->mday++;
        if (city_time->mday > city_time->get_day_in_mon())
        {

            city_time->mon++;
            if (city_time->mon > MON_IN_YEAR)
            {
                city_time->year++;

                city_time->mon -= MON_IN_YEAR;
            }
            city_time->mday -= city_time->get_day_in_mon();
        }

        city_time->hour -= HOUR_IN_DAY;
    }
}

map<string, int> Clock::get_city_time_by_int_map() {
    return city_time->get_by_int_map();
}

map<string, string> Clock::get_city_time_by_str_map() {
    return city_time->get_by_str_map();
}
