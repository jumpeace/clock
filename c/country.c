#include "bool.h"
#include "country.h"

// 空のインスタンスを返すコンストラクタ
Country Country__not_found()
{
    Country instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
Country Country__new(const char name[64])
{
    Country instance = Country__not_found();

    strcpy(instance.name, name);

    instance.is_exists = true;
    return instance;
}


// 空のインスタンスを返すコンストラクタ
Map_Country Map_Country__not_found()
{
    Map_Country instance;
    instance.is_exists = false;
    return instance;
}

// 通常のコンストラクタ
Map_Country Map_Country__new()
{
    Map_Country instance = Map_Country__not_found();

    instance.len = 0;

    instance.is_exists = true;
    return instance;
}

// 連想配列に国クラスのインスタンスを追加する
bool Map_Country__add(Map_Country *instance, const char key[16], Country value)
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

// 連想配列から国クラスのインスタンスを取得する
Country Map_Country__find(Map_Country instance, const char key[16])
{
    for (int i = 0; i < instance.len; i++)
    {
        if (strcmp(instance.k[i], key) == 0)
        {
            return instance.v[i];
        }
    }

    return Country__not_found();
}
