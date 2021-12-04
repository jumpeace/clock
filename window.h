// 18411 川原隼平

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
using namespace std;
#include "dim.h"

class Window {
public:
    void(*display) (void);
    Window(int*, char **, string, Xy*, void(*) (void), int);
    void init();
    void mainLoop();
};

#endif