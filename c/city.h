#ifndef _CITY_H_
#define _CITY_H_

#include <string.h>
#include "bool.h"
#include "country.h"

// 都市クラス
typedef struct
{
    bool is_exists;
    char name[64];
    Country country;
    int time_diff;
} City;

// 空のインスタンスを返すコンストラクタ
City City__not_found();
// 通常のコンストラクタ
City City__new(const char *, Country, int);

// 連想配列<都市>クラス
typedef struct
{
    bool is_exists;
    char k[32][16];
    City v[32];
    int len;
} Map_City;

// 空のインスタンスを返すコンストラクタ
Map_City Map_City__not_found();
// 通常のコンストラクタ
Map_City Map_City__new();

// 連想配列に都市クラスのインスタンスを追加する
bool Map_City__add(Map_City *, const char *, City);
// 連想配列から都市クラスのインスタンスを取得する
City Map_City__find(Map_City, const char *);

#endif