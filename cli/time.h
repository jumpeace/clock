#ifndef _TIME_H_
#define _TIME_H_

#include <string.h>
#include "bool.h"

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
Time Time__not_found();
// 通常のコンストラクタ
Time Time__new(int, int, int, int, int, int, int);
// 曜日を文字列(英語)で取得する
void Time__get_wday_by_str(Time, char*);
// 閏年かどうか判定する
int Time__is_leap(Time);
// 任意の月の日数を取得する
int Time__get_day_in_mon(Time);

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
Str_Time Str_Time__not_found();
// 通常のコンストラクタ
Str_Time Str_Time__new(Time);

#endif