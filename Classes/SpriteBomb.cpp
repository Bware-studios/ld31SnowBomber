//
//  SpriteBomb.cpp
//  ld31t1
//
//  Created by Mikel on 8/12/14.
//
//

#include <SimpleAudioEngine.h>
#include "SpriteBomb.h"
#include "SpriteExplosion.h"
#include "SpriteEnemy.h"

USING_NS_CC;

float bomb_delay = 5.0;

bool SpriteBomb::init()
{
    if (!SpriteInMap::init()) return false;
    
    setDisplayFrame(SpriteFrame::create("sprites.png", Rect(0*sprite_tile_size,4*sprite_tile_size, sprite_tile_size, sprite_tile_size)));
    

    Sequence *waitandcall = Sequence::createWithTwoActions(
            DelayTime::create(4.5*0 + 2),
            CallFunc::create(CC_CALLBACK_0(SpriteBomb::event_time_ends, this))
        );
    runAction(waitandcall);
    timer_sound_id=CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("bomba_450msec.mp3");

    return true;
}

void SpriteBomb::check_explosion_propagation(int deltax, int deltay)
{
    Vec2 mypos = getPositionInMap();
    Vec2 explosionpos = Vec2(mypos.x+deltax,mypos.y+deltay);
    SpriteExplosion *ex;
    ex=SpriteExplosion::create();
    ex->setIsBombExplosion( (deltax==0)&&(deltay==0) );
    ex->setPositionInMap(explosionpos);
    themap->addChild(ex,50);
    ex->explode();
    
    TMXLayer *mainlayer =themap->getLayer("main");
    TMXLayer *backgroundlayer =themap->getLayer("background");
    int tilegid = mainlayer->getTileGIDAt(explosionpos);
    //printf("tilegid: %d\n",tilegid);
    if (tilegid==11) {
        backgroundlayer->setTileGID(13, explosionpos);
        mainlayer->setTileGID(0, explosionpos);
    }
    if (tilegid==10) mainlayer->setTileGID(12, explosionpos);
    if (tilegid>=2 && tilegid<=9) mainlayer->setTileGID(12, explosionpos);
}

void SpriteBomb::event_time_ends()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect(timer_sound_id);
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("explosion.mp3");
    themap->getLayer("main")->setTileGID(0, getPositionInMap());
    check_explosion_propagation(0, 0);
    check_explosion_propagation(0, 1);
    check_explosion_propagation(0, -1);
    check_explosion_propagation(-1, 0);
    check_explosion_propagation(1, 0);
    removeFromParent();
}

