#ifndef _DRAW_H_
#define _DRAW_H_

#include "../cli/clock.h"

class Draw {
public:
    Clock* clock;
    Draw(Clock*);
    void background();
    void clock_needles();
};

#endif