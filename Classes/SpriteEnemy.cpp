//
//  SpriteEnemy.cpp
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#include <vector>
#include <SimpleAudioEngine.h>
#include "SpriteEnemy.h"
#include "utilities.h"
#include "GameScene.h"

USING_NS_CC;

using namespace std;

float p_keep_dir = 0.90;

int sin_dir[] = {0,-1,0,1};
int cos_dir[] = {1,0,-1,0};


std::vector<SpriteEnemy *> SpriteEnemy::enemy_list;



bool SpriteEnemy::init()
{
    offset_iy=2;
    if (!SpriteMoveable::init()) return false;
    
    scheduleUpdate();
    return true;
}

//void SpriteEnemy::setPlayer(SpritePlayer *p)
//{
//    theplayer=p;
//}

void SpriteEnemy::start_moving() {
    decide_and_move();
}

void SpriteEnemy::decide_and_move() {
    int newdir;
    float r = random_u();
    if (r<p_keep_dir) {
        newdir=dir;
    } else {
        newdir=(dir+1+random_i(3))%4;
    }
    int i,trydir;
    int dx,dy;
    waiting=true;
    for (i=0 ; i<4; i++) {
        // prueba con newdir+i
        trydir=(newdir+i)%4;
        dx=cos_dir[trydir];
        dy=sin_dir[trydir];
        if ( this->freeToMoveTo(dx, dy) ) {
            switch (trydir) {
                case 0:
                    waiting=false;
                    move_right();
                    break;
                case 1:
                    waiting=false;
                    move_up();
                    break;
                case 2:
                    waiting=false;
                    move_left();
                    break;
                case 3:
                    waiting=false;
                    move_down();
                    break;
            }
            dir=trydir;
            break;
        }
    }
}

void SpriteEnemy::event_move_end()
{
    SpriteMoveable::event_move_end();
    decide_and_move();
}

void SpriteEnemy::event_death() {
    removeFromParent();
    enemy_list.erase(remove(enemy_list.begin(),enemy_list.end(),this));
    
    if (enemy_list.size()==0) {
        GameScene::thegamescene->win_detected();
    }
}

void SpriteEnemy::update(float dt)
{
    SpritePlayer *currentplayer = SpritePlayer::theplayer;
    if (currentplayer) {
        if (this->collidesWith(currentplayer)) {
            currentplayer->die();
        }
    }
    if (waiting) {
        frameswaiting++;
        if (frameswaiting>60) {
            frameswaiting=0;
            decide_and_move();
        }
    }
}

void SpriteEnemy::clean_all()
{
    vector<SpriteEnemy*>::iterator i;
    for (i=enemy_list.begin() ; i!=enemy_list.end() ; i++) {
        (*i)->removeFromParent();
    }
    enemy_list.clear();
}

void SpriteEnemy::random_enemy(SpritePlayer *p)
{
    SpriteEnemy *e;
    e=SpriteEnemy::create();
    Vec2 pos;
    Vec2 playerpos;
    if (p) playerpos = p->getPositionInMap();
    float dist;
    do {
        pos=SpriteInMap::freeRandomPosition();
        if (p) {
            dist=(playerpos.x-pos.x)*(playerpos.x-pos.x)+(playerpos.y-pos.y)*(playerpos.y-pos.y);
        } else {
            dist=1000;
        }
    } while (dist<16);
    e->setPositionInMap(pos);
    //e->setPlayer(p);
    themap->addChild(e,60);
    Sequence *actions;
    actions=Sequence::createWithTwoActions(DelayTime::create(random_u()*2),CallFunc::create(CC_CALLBACK_0(SpriteEnemy::start_moving,e)));
    e->runAction(actions);
    
    enemy_list.push_back(e);
}

void SpriteEnemy::damage_check(SpriteInMap *explosionsprite)
{
//    enemy_list.erase();
//    vector<SpriteEnemy*>::iterator toremove;
//    for (toremove=std::remove_if(enemy_list.begin(), enemy_list.end(), CC_CALLBACK_1(SpriteInMap::collidesWith,explosionsprite)) ; toremove!=enemy_list.end() ; toremove++ ) {
//        
//    }
    vector<SpriteEnemy*>::iterator i;
    for (i=enemy_list.begin() ; i!=enemy_list.end() ; i++) {
        if ((*i)->collidesWith(explosionsprite)) {
            (*i)->die();
        }
    }

}

