#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
using namespace std;
#include "../base/dim.h"

namespace window {
    void init(int*, char **, string, Xy*, void(*) (void), int);
}

#endif