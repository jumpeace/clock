#include "bool.h"
#include "city.h"
#include "country.h"
#include "time.h"
#include "clock.h"
#include <time.h>


// 空のインスタンスを返すコンストラクタ
Clock Clock__not_found()
{
    Clock instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
Clock Clock__new(Map_City city_list, const char city_list_key[16])
{
    Clock instance = Clock__not_found();

    instance.city_list = city_list;
    if (!Clock__set_city(&instance, city_list_key))
        return instance;

    instance.is_exists = true;
    return instance;
}

// 時刻を取得する都市を変更する
bool Clock__set_city(Clock *instance, const char city_list_key[16])
{
    City now_city_tmp;
    now_city_tmp = Map_City__find(instance->city_list, city_list_key);
    if (!now_city_tmp.is_exists)
        return false;

    instance->now_city = now_city_tmp;

    return true;
}


// 現在時刻を記録する（取得したい都市に合わせて時差を計算）
void Clock__record_now(Clock *instance)
{
    // --- 世界標準時で取得するゾーン ---
    time_t tt;

    time(&tt);
    struct tm *ts = gmtime(&tt);

    instance->utc_time.year = ts->tm_year + 1900;
    instance->utc_time.mon = ts->tm_mon + 1;
    instance->utc_time.mday = ts->tm_mday;
    instance->utc_time.wday = ts->tm_wday;
    instance->utc_time.hour = ts->tm_hour;
    instance->utc_time.min = ts->tm_min;
    instance->utc_time.sec = ts->tm_sec;

    // --- 時差を計算するゾーン ---
    int HOUR_IN_DAY = 24; // 1日の時間
    int DAY_IN_WEEK = 7;  // 1週間の日数
    int MON_IN_YEAR = 12; // 1ヶ月の日数

    // とりあえず世界標準時の時間をディープコピー
    instance->city_time = instance->utc_time;

    // 時間だけに時差を反映
    instance->city_time.hour += instance->now_city.time_diff;

    // 時間を変更したことによって、日にち,曜日,月,年が変わる場合は修正
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
