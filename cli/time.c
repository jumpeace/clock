
// 時刻管理クラス（数値バージョン）
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

// 空のインスタンスを返すコンストラクタ
Time Time__not_found()
{
    Time instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
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

// 曜日を文字列(英語)で取得する
void Time__get_wday_by_str(Time instance, char wday_by_str[64])
{
    char wday_by_str_list[7][20] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    strcpy(wday_by_str, wday_by_str_list[instance.wday]);
}

// 閏年かどうか判定する
int Time__is_leap(Time instance)
{
    return instance.year % 400 == 0 || (!instance.year % 100 == 0 && instance.year % 4 == 0);
}

// 任意の月の日数を取得する
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

// 時刻管理クラス（文字バージョン）
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
} Str_Time;

// 空のインスタンスを返すコンストラクタ
Str_Time Str_Time__not_found()
{
    Str_Time instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
Str_Time Str_Time__new(Time time)
{
    Str_Time instance = Str_Time__not_found();

    sprintf(instance.year, "%04d", time.year);
    sprintf(instance.mon, "%02d", time.mon);
    sprintf(instance.mday, "%02d", time.mday);
    Time__get_wday_by_str(time, instance.wday);
    sprintf(instance.hour, "%02d", time.hour);
    sprintf(instance.min, "%02d", time.min);
    sprintf(instance.sec, "%02d", time.sec);

    instance.is_exists = true;
    return instance;
}
