//
//  utilities.cpp
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#include <sys/time.h>
#include <stdlib.h>

#include "utilities.h"

bool seeded=false;

void random_autoseed()
{
    struct timeval paraeltimes;
    gettimeofday(&paraeltimes, NULL);
    srandom(paraeltimes.tv_sec+paraeltimes.tv_usec);
    seeded=true;
}

float random_u()
{
    if (!seeded) random_autoseed();
    float u;
    u=random()*1.0/RAND_MAX;
    return u;
}

int random_i(int max)
{
    if (!seeded) random_autoseed();
    float u;
    int i;
    u=random()*1.0/RAND_MAX;
    i=(int)(u*max);
    return i;
}

