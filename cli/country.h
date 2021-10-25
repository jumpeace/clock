#ifndef _COUNTRY_H_
#define _COUNTRY_H_

#include <string.h>
#include "bool.h"

// 国クラス
typedef struct
{
    bool is_exists;
    char name[64];
} Country;

// 空のインスタンスを返すコンストラクタ
Country Country__not_found();
// 通常のコンストラクタ
Country Country__new(const char *);

// 連想配列<国>クラス
typedef struct
{
    bool is_exists;
    char k[32][16];
    Country v[32];
    int len;
} Map_Country;

// 空のインスタンスを返すコンストラクタ
Map_Country Map_Country__not_found();
// 通常のコンストラクタ
Map_Country Map_Country__new();

// 連想配列に国クラスのインスタンスを追加する
bool Map_Country__add(Map_Country *, const char *, Country);
// 連想配列から国クラスのインスタンスを取得する
Country Map_Country__find(Map_Country , const char *);

#endif
