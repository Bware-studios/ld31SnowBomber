#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "SpritePlayer.h"
#include "SpriteEnemy.h"


class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    CREATE_FUNC(GameScene);
    virtual bool init();
    
    void load_map();
    
    void event_keypressed(cocos2d::EventKeyboard::KeyCode kcode,cocos2d::Event *e);
    void event_keyreleased(cocos2d::EventKeyboard::KeyCode kcode,cocos2d::Event *e);
    bool event_touchbegan(cocos2d::Touch* touch,cocos2d::Event *e);
    void event_touchended(cocos2d::Touch* touch,cocos2d::Event *e);
    
    void print_keys();

    void display_menu();
    void display_win();
    void display_loss();
    void enter_game();
    
    void win_detected();
    void loss_detected();

    void win_timeout();

    
    cocos2d::TMXTiledMap *themap = NULL;
    
    SpritePlayer *player;
    SpriteEnemy *e1;
    SpriteEnemy *e2;
    SpriteEnemy *e3;
    
    
    bool *key_is_pressed;
    
    static GameScene *thegamescene;

private:
    bool lost_game;
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    cocos2d::LayerColor *menulayer = NULL;
    cocos2d::LayerColor *winlayer = NULL;
    cocos2d::LayerColor *losslayer = NULL;
    
    //cocos2d::ParticleSnow *snow;
    
    bool displaying_menu = true;
    bool displaying_win = false;
    bool displaying_loss = false;
    bool ingame = false;
    
    bool touching = false; 
    
};

#endif // __GameScene_SCENE_H__
