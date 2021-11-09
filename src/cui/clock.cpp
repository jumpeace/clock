#include "clock.h"

Clock::Clock(map<string, City*> _city_list, string init_city_key)
{
    city_list = _city_list;
    if (!setCity(init_city_key)) {
        return;
    }
}

// 時刻を取得する都市を変更する。
bool Clock::setCity(string city_key)
{
    if (city_list.count(city_key) == 0)
    {
        return false;
    }
    now_city = city_list[city_key];

    return true;
}

// 現在の都市を取得する
City* Clock::getNowCity() {
    return now_city;
}

// 現在時刻を記録する
void Clock::recordNow()
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
    int MIN_IN_HOUR = 60; // 1時間が何分か
    int HOUR_IN_DAY = 24; // 1日が何時間か
    int DAY_IN_WEEK = 7;  // 1週間が何日か
    int MON_IN_YEAR = 12; // 1ヶ月が何日か

    // とりあえず世界標準時の時間をディープコピー
    city_time = utc_time;

    // min に時差を反映
    city_time->min += (int)((now_city->time_diff - (int)now_city->time_diff) * 60);
    if (city_time->min < 0) {
        city_time->hour--;
        city_time->min += MIN_IN_HOUR;
    }
    else if (city_time->min >= MIN_IN_HOUR) {
        city_time->hour++;
        city_time->min -= MIN_IN_HOUR;
    }

    // hour に時差を反映

    city_time->hour += (int)now_city->time_diff;

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

            city_time->mday += city_time->getDayInMon();
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
        if (city_time->mday > city_time->getDayInMon())
        {

            city_time->mon++;
            if (city_time->mon > MON_IN_YEAR)
            {
                city_time->year++;

                city_time->mon -= MON_IN_YEAR;
            }
            city_time->mday -= city_time->getDayInMon();
        }

        city_time->hour -= HOUR_IN_DAY;
    }
}

// 文字列で都市の時刻を取得する
map<string, string> Clock::getCityTimeByStrList() {
    return city_time->getByStrList();
}
