#ifndef TUPLE
#define TUPLE

#include <stdlib.h>
#include <list>

struct Tuple {
    int firstPos;
    int lastPos;
    bool color;
    int heuristic;
    Tuple* movement_register;
};

#endif