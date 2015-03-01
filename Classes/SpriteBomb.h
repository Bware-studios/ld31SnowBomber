//
//  SpriteBomb.h
//  ld31t1
//
//  Created by Mikel on 8/12/14.
//
//

#ifndef __ld31t1__SpriteBomb__
#define __ld31t1__SpriteBomb__

#include <stdio.h>
#include "SpriteInMap.h"


class SpriteBomb : public SpriteInMap
{
public:
    bool init();
    CREATE_FUNC(SpriteBomb);

    void check_explosion_propagation(int deltax, int deltay);
    
    void event_time_ends();
    
private:
    int timer_sound_id;
    
};



#endif /* defined(__ld31t1__SpriteBomb__) */
