//
//  SpriteMoveable.h
//  ld31t1
//
//  Created by Mikel on 6/12/14.
//
//

#ifndef __ld31t1__SpriteMoveable__
#define __ld31t1__SpriteMoveable__

#include <stdio.h>
#include "SpriteInMap.h"



class SpriteMoveable : public SpriteInMap
{
public:
    bool init();
    CREATE_FUNC(SpriteMoveable);
    

    void die();
    void move_up();
    void move_down();
    void move_left();
    void move_right();
    void move_to(int deltax, int deltay, float duration, cocos2d::Animation *move_animation);
    virtual void event_move_end();
    virtual void event_target_selfmove();
    virtual void event_death();

    void clearTarget();
    void setTarget(cocos2d::Vec2 t);
    bool checkNextTargetStep();
    
protected:
    int offset_iy;
    bool moving = false;
    bool dead = false;
    
private:
    cocos2d::Animation *anim_walk_left = NULL;
    cocos2d::Animation *anim_walk_right = NULL;
    cocos2d::Animation *anim_walk_up = NULL;
    cocos2d::Animation *anim_walk_down = NULL;
    cocos2d::Animation *anim_die = NULL;
    
    
    bool has_target = false;
    cocos2d::Vec2 target;
    std::vector<cocos2d::Vec2> path_to_target;

    
};


#endif /* defined(__ld31t1__SpriteMoveable__) */
