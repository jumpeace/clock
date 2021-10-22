#include "bool.h"
#include "country.h"
#include "city.h"

// 空のインスタンスを返すコンストラクタ
City City__not_found()
{
    City instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
City City__new(const char name[64], Country country, int time_diff)
{
    City instance = City__not_found();

    instance.time_diff = time_diff;
    strcpy(instance.name, name);
    instance.country = country;

    instance.is_exists = true;
    return instance;
}

// 空のインスタンスを返すコンストラクタ
Map_City Map_City__not_found()
{
    Map_City instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
Map_City Map_City__new()
{
    Map_City instance = Map_City__not_found();

    instance.len = 0;

    instance.is_exists = true;
    return instance;
}

// 連想配列に都市クラスのインスタンスを追加する
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

// 連想配列から都市クラスのインスタンスを取得する
City Map_City__find(Map_City instance, const char key[16])
{
    for (int i = 0; i < instance.len; i++)
    {
        if (strcmp(instance.k[i], key) == 0)
        {
            return instance.v[i];
        }
    }

    return City__not_found();
}
