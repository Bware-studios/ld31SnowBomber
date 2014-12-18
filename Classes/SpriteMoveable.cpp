//
//  SpriteMoveable.cpp
//  ld31t1
//
//  Created by Mikel on 6/12/14.
//
//

#include <iostream>

#include <SimpleAudioEngine.h>
#include "SpriteMoveable.h"

USING_NS_CC;
using namespace std;

float anim_dely_unit = 0.1;
float move_dely = 0.3;

bool SpriteMoveable::init()
{
    if (!SpriteInMap::init()) return false;
    
    int offset_y = offset_iy*sprite_tile_size;
        
    this->setDisplayFrame(SpriteFrame::create("sprites.png", Rect(6*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
    
    if (!anim_walk_right) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(0*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(1*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(2*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        anim_walk_right=Animation::createWithSpriteFrames(frames);
        anim_walk_right->setDelayPerUnit(anim_dely_unit);
        anim_walk_right->setRestoreOriginalFrame(true);
        anim_walk_right->retain();
    }

    if (!anim_walk_left) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(3*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(4*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(5*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        anim_walk_left=Animation::createWithSpriteFrames(frames);
        anim_walk_left->setDelayPerUnit(anim_dely_unit);
        anim_walk_left->setRestoreOriginalFrame(true);
        anim_walk_left->retain();
    }

    
    if (!anim_walk_down) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(6*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(7*sprite_tile_size,offset_y, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(0*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        anim_walk_down=Animation::createWithSpriteFrames(frames);
        anim_walk_down->setDelayPerUnit(anim_dely_unit);
        anim_walk_down->setRestoreOriginalFrame(true);
        anim_walk_down->retain();
    }
    
    if (!anim_walk_up) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(1*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(2*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(3*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        anim_walk_up=Animation::createWithSpriteFrames(frames);
        anim_walk_up->setDelayPerUnit(anim_dely_unit);
        anim_walk_up->setRestoreOriginalFrame(true);
        anim_walk_up->retain();
    }
    
    if (!anim_die) {
        Vector<SpriteFrame*> frames;
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(4*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(5*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(6*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        frames.pushBack(SpriteFrame::create("sprites.png", Rect(7*sprite_tile_size,offset_y+sprite_tile_size, sprite_tile_size, sprite_tile_size)));
        anim_die=Animation::createWithSpriteFrames(frames);
        anim_die->setDelayPerUnit(anim_dely_unit);
        anim_die->setRestoreOriginalFrame(false);
        anim_die->retain();
    }
    
    
    return true;

}

void SpriteMoveable::die()
{
    if (dead) return;
    stopAllActions();
    Animate *a;
    a=Animate::create(anim_die);
    moving=true;
    dead=true;
    
    Sequence *dieandcall;
    dieandcall = Sequence::createWithTwoActions(a, CallFunc::create(CC_CALLBACK_0(SpriteMoveable::event_death, this)));
    
    if (offset_iy<1)
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("catch.mp3");

    
    runAction(dieandcall);
}

void SpriteMoveable::move_up()
{
    move_to(0, -1, move_dely, anim_walk_up);
}

void SpriteMoveable::move_down()
{
    move_to(0, 1, move_dely, anim_walk_down);
}

void SpriteMoveable::move_left()
{
    move_to(-1, 0, move_dely, anim_walk_left);
}

void SpriteMoveable::move_right()
{
    move_to(1, 0, move_dely, anim_walk_right);
}


void SpriteMoveable::move_to(int deltax, int deltay, float duration, cocos2d::Animation *move_animation)
{
    if (moving) return;
    if ( !freeToMoveTo(deltax, deltay) ) return;
    moving=true;
    Vec2 topos;
    topos.x=map_position.x+deltax;
    topos.y=map_position.y+deltay;
    Spawn *twoactions;
    MoveTo *move_action;
    move_action=MoveTo::create(duration, coordsNodeFromInMap(topos));
    twoactions=Spawn::createWithTwoActions(
        move_action,
        Animate::create(move_animation)
    );
    this->runAction(Sequence::createWithTwoActions(twoactions, CallFunc::create(CC_CALLBACK_0(SpriteMoveable::event_move_end, this))));
}

void SpriteMoveable::event_move_end() {
    moving=false;
    if (has_target) {
        Vec2 n =path_to_target.back();
        path_to_target.pop_back();
        themap->getLayer("selection")->setTileGID(0, n);
        checkNextTargetStep();
    }
}

void SpriteMoveable::event_target_selfmove()
{
    
}

void SpriteMoveable::event_death() {

}



void SpriteMoveable::clearTarget()
{
    if (has_target) {
        TMXLayer *selectionlayer = themap->getLayer("selection");
        for ( auto i=path_to_target.begin() ; i!=path_to_target.end() ; i++ ) {
            selectionlayer->setTileGID(0,*i);
        }
    }
    path_to_target.clear();
    has_target=false;
}

void SpriteMoveable::setTarget(cocos2d::Vec2 t)
{
    clearTarget();
    path_to_target=findPath(map_position,t);
    if (path_to_target.empty()) {
        // sonido de no ?
        return;
    }
    has_target=true;
    target=t;
    
    TMXLayer *selectionlayer = themap->getLayer("selection");
    
    for ( auto i=path_to_target.begin() ; i!=path_to_target.end() ; i++ ) {
        //cout << "("<< i->x <<","<< i->y <<")\n" ;
        selectionlayer->setTileGID(15,*i);
    }
    selectionlayer->setTileGID(14,t);
    //cout<<"----------\n";
    if (!moving) {
        checkNextTargetStep();
    } else {
        // un poco apaño pero... si esta llamando a setTarget al acabar un movimiento lo primero que va a hacer es quitar el nodo en el que esta por lo que hay que añadir uno para compensar
        path_to_target.push_back(Vec2(map_position));
    }
}

bool SpriteMoveable::checkNextTargetStep()
{
    if (!has_target) return false;
    if (path_to_target.empty()) {has_target=false; return false;}
    
    Vec2 n = path_to_target.back();
//    path_to_target.pop_back();
//    themap->getLayer("selection")->setTileGID(0, n);
    int deltax = n.x-map_position.x;
    int deltay = n.y-map_position.y;
    

    bool following_path=false;
    if (deltax>0) {
        move_right();
        following_path=true;
    } else if (deltax<0) {
        move_left();
        following_path=true;
    } else if (deltay>0) {
        move_down();
        following_path=true;
    } else if (deltay<0) {
        move_up();
        following_path=true;
    }
    if (following_path) {
        event_target_selfmove();
    } else {
        cout<<"WARNING path driving problem!!!\n";
    }
    return following_path;
}




