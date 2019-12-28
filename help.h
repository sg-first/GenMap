#pragma once
#include <stdlib.h>
#include <time.h>

typedef unsigned int uint;

class Rand
{
public:
    static bool rand01()
    {
        return rand()%2;
    }

    static uint randRange(uint range)
    {
        return rand()%range;
    }

    static void initRand()
    {
        srand(time(0));
    }
};
