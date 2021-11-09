#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <iostream>
using namespace std;
#include "../base/dim.h"

class Window {
public:
    void(*display) (void);
    Window(int*, char **, string, Xy*, void(*) (void), int);
    void load();
    void init();
    void mainLoop();
};

#endif