//
//  SpritePlayer.cpp
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#include <iostream>
#include <SimpleAudioEngine.h>
#include "GameScene.h"

#include "SpritePlayer.h"
#include "SpriteBomb.h"


USING_NS_CC;

using namespace std;

SpritePlayer *SpritePlayer::theplayer = NULL;


bool SpritePlayer::init()
{
    offset_iy=0;
    if (!SpriteMoveable::init()) return false;
    theplayer=this;
    
    return true;
}


void SpritePlayer::event_move_end() {
    check_touch_move();

    SpriteMoveable::event_move_end();
    keys_state_changed();
    bomb=false;
}

void SpritePlayer::event_target_selfmove()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("snow_steps.mp3");    
}

void SpritePlayer::event_death() {
    SpriteMoveable::event_death();
    clearTarget();
    Sequence *waitandcall;
    waitandcall=Sequence::createWithTwoActions(DelayTime::create(2), CallFunc::create(CC_CALLBACK_0(SpritePlayer::event_timeout_after_death, this)));
    runAction(waitandcall);
}

void SpritePlayer::event_timeout_after_death() {
    GameScene::thegamescene->loss_detected();
    SpritePlayer::theplayer=NULL;
    removeFromParent();
}

void SpritePlayer::place_bomb()
{
    if (!moving && !bomb) {
        bomb = true;
        Vec2 mypos = getPositionInMap();
        SpriteBomb *abomb = SpriteBomb::create();
        abomb->setPositionInMap(mypos);
        themap->addChild(abomb);
    }
}

void SpritePlayer::set_keys_state(bool *keystates)
{
    key_is_pressed=keystates;
}


void SpritePlayer::touched(cocos2d::Vec2 p)
{
    if (dead) return;
    Vec2 pos = themap->convertToNodeSpace(p);
    //cout << "InMap : ("<<pos.x<<","<<pos.y<<")\n";
    Vec2 ipos = coordsInMapFromNode(pos);
    //cout << "InMap : ("<<ipos.x<<","<<ipos.y<<")\n";
    touch_move_ready=true;
    touch_move_point=ipos;
    if (!moving) {
        check_touch_move();
    }
}

void SpritePlayer::check_touch_move()
{
    if (touch_move_ready) {
        Vec2 myposinmap = getPositionInMap();
        //cout<<"i am in "<<myposinmap.x<<","<<myposinmap.y<<"\n";
        if (abs(myposinmap.x-touch_move_point.x)<0.5 &&abs(myposinmap.y-touch_move_point.y)<0.5 ) {
            place_bomb();
        } else {
            setTarget(touch_move_point);
        }
        touch_move_ready=false;
    }
}


void SpritePlayer::keys_state_changed()
{
    bool snow_step=false;
    if (key_is_pressed[4]) { // first check bomb
        place_bomb();
    } else if ( key_is_pressed[0] ) {
        snow_step=true;
        move_up();
    } else if (key_is_pressed[1]) {
        snow_step=true;
        move_down();
    } else if (key_is_pressed[2]) {
        snow_step=true;
        move_left();
    } else if (key_is_pressed[3]) {
        snow_step=true;
        move_right();
    }
    if (snow_step) {
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("snow_steps.mp3");
    }
}
