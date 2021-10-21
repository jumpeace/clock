#include <stdio.h>
#include <time.h>
#include <string.h>


void get_wday(char wday_key[20], int wday_num) {
    char wday_keys[7][20] = {"日", "月", "火", "水", "木", "金", "土"};
    strcpy(wday_key, wday_keys[wday_num]);
}

int main(int argc, char const *argv[])
{
    time_t tt;
    struct tm* ts;
    char wday_key[20];

    // 現在時刻を取得
    time(&tt);
    // time_t --> struct tm
    ts = localtime(&tt);

    get_wday(wday_key, ts->tm_wday);

    printf("%4d/%2d/%2d(%s) %02d:%02d:%02d\n" 
        ,ts->tm_year + 1900, ts->tm_mon + 1, ts->tm_mday, wday_key, ts->tm_hour, ts->tm_min, ts->tm_sec);

    return 0;
}
