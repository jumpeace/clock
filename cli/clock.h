#ifndef _CLOCK_H_
#define _CLOCK_H_

#include "bool.h"
#include "city.h"
#include "country.h"
#include "time.h"

// 時計クラス
typedef struct
{
    bool is_exists;
    Map_City city_list;
    City now_city;
    Time utc_time;
    Time city_time;
} Clock;


// 空のインスタンスを返すコンストラクタ
Clock Clock__not_found();
// 通常のコンストラクタ
Clock Clock__new(Map_City, const char*);
// 時刻を取得する都市を変更する
bool Clock__set_city(Clock *, const char*);
// 現在時刻を記録する（取得したい都市に合わせて時差を計算）
void Clock__record_now(Clock *);

#endif