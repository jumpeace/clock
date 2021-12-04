#ifndef _DRAW_H_
#define _DRAW_H_

#include "dim.h"
#include "clock.h"

class Draw {
public:
    Clock* clock;
    Draw(Clock*);
    void background();
    void clockNeedles();
};

#endif