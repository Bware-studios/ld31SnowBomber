//
//  SpriteEnemy.h
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#ifndef __ld31t1__SpriteEnemy__
#define __ld31t1__SpriteEnemy__

#include <stdio.h>
#include "SpriteMoveable.h"
#include "SpritePlayer.h"

class SpriteEnemy : public SpriteMoveable
{
public:
    bool init();
    CREATE_FUNC(SpriteEnemy);
    //void setPlayer(SpritePlayer *p);
    
    void start_moving();
    void decide_and_move();
    void event_move_end();
    void event_death();

    void update(float dt);
    
    static void clean_all();
    static void random_enemy(SpritePlayer *p);
    static void damage_check(SpriteInMap *explosionsprite);
private:
    static std::vector<SpriteEnemy *> enemy_list;
    int dir = 0;
    bool waiting = false;
    int frameswaiting=0;
    //SpritePlayer *theplayer = NULL;
    
};


#endif /* defined(__ld31t1__SpriteEnemy__) */
