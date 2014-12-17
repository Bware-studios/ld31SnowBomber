//
//  SpriteExplosion.cpp
//  ld31t1
//
//  Created by Mikel on 8/12/14.
//
//

#include "SpriteExplosion.h"
#include "SpriteEnemy.h"

USING_NS_CC;

cocos2d::Animation *SpriteExplosion::anim_bomb_explosion = NULL;
cocos2d::Animation *SpriteExplosion::anim_free_explosion = NULL;



bool SpriteExplosion::init()
{
    if (!SpriteInMap::init()) return false;
    
    setDisplayFrame(SpriteFrame::create("sprites.png", Rect(5*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
    
    if (!anim_free_explosion) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(5*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(6*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(7*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(0*sprite_tile_size,5*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        
        anim_free_explosion=Animation::createWithSpriteFrames(frames);
        anim_free_explosion->setDelayPerUnit(0.1);
        anim_free_explosion->setRestoreOriginalFrame(false);
        anim_free_explosion->retain();
    }
    
    if (!anim_bomb_explosion) {
        Vector<SpriteFrame*> frames;
        //        frames.pushBack(SpriteFrame::create("sprites.png", Rect(0*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(1*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(2*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(3*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(4*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        
        anim_bomb_explosion=Animation::createWithSpriteFrames(frames);
        anim_bomb_explosion->setDelayPerUnit(0.1);
        anim_bomb_explosion->setRestoreOriginalFrame(false);
        anim_bomb_explosion->retain();
    }

    return true;
}

void SpriteExplosion::setIsBombExplosion(bool isbomb)
{
    isbombexplosion=isbomb;
}

void SpriteExplosion::explode()
{
    
    Sequence *explodeandcall = Sequence::createWithTwoActions(
        Animate::create(isbombexplosion?anim_bomb_explosion:anim_free_explosion),
        CallFunc::create(CC_CALLBACK_0(SpriteExplosion::event_explosion_ends, this))
    );
    runAction(explodeandcall);
    scheduleUpdate();
}


void SpriteExplosion::event_explosion_ends()
{
    removeFromParent();
}

void SpriteExplosion::update(float dt)
{
    SpriteEnemy::damage_check(this);
    if (SpritePlayer::theplayer) {
        if (SpritePlayer::theplayer->collidesWith(this)) {
            SpritePlayer::theplayer->die();
        }
    }
}



