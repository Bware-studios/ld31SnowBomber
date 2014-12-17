//
//  SpriteExplosion.h
//  ld31t1
//
//  Created by Mikel on 8/12/14.
//
//

#ifndef __ld31t1__SpriteExplosion__
#define __ld31t1__SpriteExplosion__

#include <stdio.h>
#include "SpriteInMap.h"


class SpriteExplosion : public SpriteInMap
{
public:
    bool init();
    CREATE_FUNC(SpriteExplosion);
    void setIsBombExplosion(bool isbomb);
    void explode();
    void event_explosion_ends();
    void update(float dt);
    
private:
    static cocos2d::Animation *anim_bomb_explosion;
    static cocos2d::Animation *anim_free_explosion;
    bool isbombexplosion = false;
    
};



#endif /* defined(__ld31t1__SpriteExplosion__) */
