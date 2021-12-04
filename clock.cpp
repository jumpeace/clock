#include "clock.h"
#include "funcs.h"

Time_::Time_(int _year, int _mon, int _mday, int _wday, int _hour, int _min, int _sec)
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
string Time_::getWdayByStr()
{
    vector<string> wday_by_str_list = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    return wday_by_str_list[wday];
}


// 閏年かどうかを判定する
bool Time_::isLeap()
{
    return year % 400 == 0 || (!year % 100 == 0 && year % 4 == 0);
}

// 任意の月の日数を取得する
int Time_::getDayInMon()
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
bool Time_::isMorning() {
    return hour / 12 == 0;
}

// 文字列で日時の情報を取得する
map<string, string> Time_::getByStrList()
{
    map<string, string> str_list;

    str_list["year"] = funcs::fillByZero(year, 4);
    str_list["mon"] = funcs::fillByZero(mon, 2);
    str_list["mday"] = funcs::fillByZero(mday, 2);
    str_list["wday"] = getWdayByStr();
    str_list["hour"] = funcs::fillByZero(hour, 2);
    str_list["min"] = funcs::fillByZero(min, 2);
    str_list["sec"] = funcs::fillByZero(sec, 2);

    return str_list;
}

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
City* Clock::getNowIdxCity() {
    return now_city;
}

// 現在時刻を記録する
void Clock::recordNow()
{
    // --- 世界標準時で取得するゾーン ---
    time_t tt;

    time(&tt);
    struct tm *ts = gmtime(&tt);

    utc_time = new Time_(
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
map<string, string> Clock::getCityTime_ByStrList() {
    return city_time->getByStrList();
}
