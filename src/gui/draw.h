#ifndef _DRAW_H_
#define _DRAW_H_

#include "../base/dim.h"
#include "../cui/clock.h"

class Draw {
public:
    Clock* clock;
    Draw(Clock*);
    void background();
    void clock_needles();
    void hour_texts();
};

#endif