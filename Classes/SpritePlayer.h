//
//  SpritePlayer.h
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#ifndef __ld31t1__SpritePlayer__
#define __ld31t1__SpritePlayer__

#include <stdio.h>
#include "SpriteMoveable.h"

class SpritePlayer : public SpriteMoveable
{
public:
    bool init();
    CREATE_FUNC(SpritePlayer);
    
    void event_move_end();
    void event_target_selfmove();
    void event_death();
    void event_timeout_after_death();

    void place_bomb();
    
    void set_keys_state(bool *keystates);
    void check_touch_move();
    void keys_state_changed();
    void touched(cocos2d::Vec2 p);
    
    static SpritePlayer *theplayer;
private:
    bool bomb = false;
    bool *key_is_pressed;
    bool touch_move_ready=false;
    cocos2d::Vec2 touch_move_point;
};

#endif /* defined(__ld31t1__SpritePlayer__) */
