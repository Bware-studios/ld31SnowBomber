#include <iostream>
#include <SimpleAudioEngine.h>
#include "utilities.h"
#include "GameScene.h"


USING_NS_CC;

using namespace std;


// to add a key increase this and list
int n_keys = 5;
EventKeyboard::KeyCode keys[]={
    EventKeyboard::KeyCode::KEY_UP_ARROW,
    EventKeyboard::KeyCode::KEY_DOWN_ARROW,
    EventKeyboard::KeyCode::KEY_LEFT_ARROW,
    EventKeyboard::KeyCode::KEY_RIGHT_ARROW,
    EventKeyboard::KeyCode::KEY_SPACE,
};

int n_rocks_min=15;
int n_rocks_max=20;

int n_enemies_min=4;
int n_enemies_max=8;



GameScene *GameScene::thegamescene = NULL;

void GameScene::print_keys() {
    cout << "keys : ";
    for (int i=0;i<n_keys;i++) {
        cout << key_is_pressed[i] << " ";
    }
    cout<<"\n";
}

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    thegamescene=this;
    
    CocosDenshion::SimpleAudioEngine *ae;
    ae=CocosDenshion::SimpleAudioEngine::getInstance();
    ae->preloadBackgroundMusic("theme_ver3.mp3");
    ae->preloadEffect("Youwin.mp3");
    ae->preloadEffect("Youlose.mp3");
    ae->preloadEffect("snow_steps.mp3");
    ae->preloadEffect("catch.mp3");
    ae->preloadEffect("explosion.mp3");
    ae->preloadEffect("bomba_450msec.mp3");
    ae->setBackgroundMusicVolume(0.9);
    ae->setEffectsVolume(0.9);
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    cout<<"visible size: "<<visibleSize.width<<" x "<<visibleSize.height<<"\n";
    //cout<<"origin: "<<origin.x<<" x "<<origin.y<<"\n";
    

    key_is_pressed = new bool[n_keys];
    
    load_map();
    
    
    
//    player=SpritePlayer::create();
//    player->setPositionInMap(3,3);
//    themap->addChild(player,20);
//    player->set_keys_state(key_is_pressed);

    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);
    SpriteEnemy::random_enemy(NULL);

    
//    e1=SpriteEnemy::create();
//    e1->setPositionInMap(7,3);
//    themap->addChild(e1,20);
//    e2=SpriteEnemy::create();
//    e2->setPositionInMap(9,5);
//    themap->addChild(e2,20);
//    e3=SpriteEnemy::create();
//    e3->setPositionInMap(11,1);
//    themap->addChild(e3,20);

//    TMXLayer *l1= themap->getLayer("main");
//    int gid=l1->getTileGIDAt(Vec2(4,6));
//    printf("gid = %d\n",gid);
    
//    l1->setTileGID(10, Vec2(0,0));
    
//    e1->start_moving();
//    e2->start_moving();
//    e3->start_moving();
//    player->move_down();
//    e1->move_right();
//    e2->move_up();
    

//    snow = ParticleSnow::create();
//    themap->addChild(snow,100);
//    snow->setPosition(Vec2(visibleSize.width/2,visibleSize.height));
//    snow->setStartColor(Color4F(.5,.5,.8,1));
//    snow->setEndColor(Color4F(.3,.3,.6,1));
//    snow->setStartSize(20);
//    snow->setGravity(Vec2(0,-100));
//    snow->resetSystem();

    
    EventListenerKeyboard *kl = EventListenerKeyboard::create();
    kl->onKeyPressed=CC_CALLBACK_2(GameScene::event_keypressed,this);
    kl->onKeyReleased=CC_CALLBACK_2(GameScene::event_keyreleased,this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(kl, this);

    EventListenerTouchOneByOne *tl = EventListenerTouchOneByOne::create();
    tl->setSwallowTouches(true);
    tl->onTouchBegan=CC_CALLBACK_2(GameScene::event_touchbegan, this);
    tl->onTouchEnded=CC_CALLBACK_2(GameScene::event_touchended, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(tl, 1000);
    
//    CocosDenshion::SimpleAudioEngine *ae;
//    ae->getInstance()->playBackgroundMusic("fondo.wav",true);
//    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("theme_ver3.mp3",true);

    display_menu();
    
    return true;
}

void GameScene::load_map()
{
    if (themap) {
        SpriteEnemy::clean_all();
        themap->removeFromParent();
    }
    themap = TMXTiledMap::create("map2.tmx");
    SpriteInMap::setMap(themap);
    themap->setAnchorPoint(Vec2(.5,.5));
    themap->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
    this->addChild(themap);

    Vec2 rockpos;
    Vec2 avoid = Vec2(7,1);
    int dist;
    int n_rocks = n_rocks_min + random_i(n_rocks_max-n_rocks_min+1);
    
    TMXLayer *mainlayer = themap->getLayer("main");
    for (int i=0; i<n_rocks; i++) {
        do {
            rockpos=SpriteInMap::freeRandomPosition();
            dist=(rockpos.x-avoid.x)*(rockpos.x-avoid.x)+(rockpos.y-avoid.y)*(rockpos.y-avoid.y);
        } while (dist<=9);
        mainlayer->setTileGID(11, rockpos);
    }
    
//    //snow
//    if (snow) snow->removeFromParent();
//    themap->addChild(snow);
}

void GameScene::event_keypressed(cocos2d::EventKeyboard::KeyCode kcode,cocos2d::Event *e)
{
    if (!ingame) return;
    int i;
    for (i=0; i<n_keys ; i++) {
        if (kcode==keys[i]) {
            key_is_pressed[i]=true;
        }
    }
//    print_keys();
    SpritePlayer *currentplayer = SpritePlayer::theplayer;
    if ( currentplayer ) currentplayer->keys_state_changed();
}

void GameScene::event_keyreleased(cocos2d::EventKeyboard::KeyCode kcode,cocos2d::Event *e)
{
    if (!ingame) {
        if (displaying_win)
            display_menu();
        else if (displaying_loss)
            display_menu();
        else if (displaying_menu)
            enter_game();
        return;
    }
    
    int i;
    for (i=0; i<n_keys ; i++) {
        if (kcode==keys[i]) {
            key_is_pressed[i]=false;
        }
    }
//    print_keys();
    SpritePlayer *currentplayer = SpritePlayer::theplayer;
    if ( currentplayer ) currentplayer->keys_state_changed();
}

bool GameScene::event_touchbegan(cocos2d::Touch* touch,cocos2d::Event *e)
{
    if (touching) return false;
    return true;
}

void GameScene::event_touchended(cocos2d::Touch* touch,cocos2d::Event *e)
{
    if (!ingame) {
        if (displaying_win)
            display_menu();
        else if (displaying_loss)
            display_menu();
        else if (displaying_menu)
            enter_game();
        return;
    }

    Vec2 loc=touch->getLocation();
    //cout << "Tl : ("<<loc.x<<","<<loc.y<<")\n";
    SpritePlayer::theplayer->touched(loc);
}



void GameScene::display_menu()
{
    if (!menulayer) {
        menulayer = LayerColor::create(Color4B(255,255,255,220));
        menulayer->setPosition(Vec2(0,0));
        Menu *m1=Menu::create();
        m1->setPosition(visibleSize.width/2,visibleSize.height/2);
        menulayer->addChild(m1);
    
        MenuItemImage *im1;

        char * infotxt_filename = "info.png";
        char * playtxt_filename = "play.png";
        Application::Platform platform = Application::getInstance()->getTargetPlatform();
        if ( platform == Application::Platform::OS_ANDROID || platform == Application::Platform::OS_IPHONE || platform == Application::Platform::OS_IPAD ) {
            infotxt_filename = "mobile/info.png";
            playtxt_filename = "mobile/play.png";
        }
        
        
        im1=MenuItemImage::create("titulo.png","titulo.png");
        im1->setEnabled(false);
        im1->setPosition(Vec2(0,150));
        m1->addChild(im1);
    
        im1=MenuItemImage::create(infotxt_filename,infotxt_filename);
        im1->setEnabled(false);
        im1->setPosition(Vec2(0,0));
        m1->addChild(im1);
    
        im1=MenuItemImage::create(playtxt_filename,playtxt_filename);
        im1->setEnabled(false);
        im1->setPosition(Vec2(0,-130));
        m1->addChild(im1);
        menulayer->retain();
    }
    
    if (winlayer && displaying_win) winlayer->removeFromParent();
    if (losslayer && displaying_loss) losslayer->removeFromParent();
    addChild(menulayer,1000);

    displaying_menu=true;
    displaying_win=false;
    displaying_loss=false;
    ingame=false;


    CocosDenshion::SimpleAudioEngine *ae;
    ae = CocosDenshion::SimpleAudioEngine::getInstance();
    ae->playBackgroundMusic("theme_ver3.mp3",true);
    ae->setBackgroundMusicVolume(0.9);

}


void GameScene::display_win()
{
    CocosDenshion::SimpleAudioEngine *ae;
    ae = CocosDenshion::SimpleAudioEngine::getInstance();
    ae->stopBackgroundMusic();
    ae->playEffect("Youwin.mp3");

    if (!winlayer) {
        winlayer = LayerColor::create(Color4B(255,255,255,220));
        winlayer->setPosition(Vec2(0,0));
    
        Menu *m1=Menu::create();
        m1->setPosition(visibleSize.width/2,visibleSize.height/2);
        winlayer->addChild(m1);
    
        MenuItemImage *im1;
    
        im1=MenuItemImage::create("youwin.png","youwin.png");
        im1->setEnabled(false);
        im1->setPosition(Vec2(0,0));
        m1->addChild(im1);
        winlayer->retain();
    }
    
    if (menulayer) menulayer->removeFromParent();
    addChild(winlayer,1000);
        
    displaying_menu=false;
    displaying_win=true;
    displaying_loss=false;
    ingame=false;
}


void GameScene::display_loss()
{
    CocosDenshion::SimpleAudioEngine *ae;
    ae = CocosDenshion::SimpleAudioEngine::getInstance();
    ae->stopBackgroundMusic();
    ae->playEffect("Youlose.mp3");

    
    if (!losslayer) {
        losslayer = LayerColor::create(Color4B(255,255,255,220));
        losslayer->setPosition(Vec2(0,0));
        
        Menu *m1=Menu::create();
        m1->setPosition(visibleSize.width/2,visibleSize.height/2);
        losslayer->addChild(m1);
    
        MenuItemImage *im1;
    
        im1=MenuItemImage::create("gameover.png","gameover.png");
        im1->setEnabled(false);
        im1->setPosition(Vec2(0,0));
        m1->addChild(im1);
        losslayer->retain();
    }

    if (menulayer) menulayer->removeFromParent();
    addChild(losslayer,1000);

    displaying_menu=false;
    displaying_win=false;
    displaying_loss=true;
    ingame=false;
}

void GameScene::enter_game()
{
    load_map();
    CocosDenshion::SimpleAudioEngine *ae;
    ae = CocosDenshion::SimpleAudioEngine::getInstance();
    //ae->playBackgroundMusic("theme_ver3.mp3",true);
    ae->setBackgroundMusicVolume(0.5);

    player=SpritePlayer::create();
    player->setPositionInMap(7,1);
    themap->addChild(player,20);
    player->set_keys_state(key_is_pressed);
    
    
    //player->setTarget(Vec2(1,5));
    
    int n_enemies = n_enemies_min+random_i(n_enemies_max+1-n_enemies_min);
    for (int i=0; i<n_enemies ; i++) {
        SpriteEnemy::random_enemy(player);
    }
    
    menulayer->removeFromParent();
    
    displaying_menu=false;
    displaying_win=false;
    displaying_loss=false;
    ingame=true;
    
    lost_game=false;
}

void GameScene::win_detected()
{
    Sequence *waitforwin;
    waitforwin = Sequence::createWithTwoActions(DelayTime::create(2.0), CallFunc::create(CC_CALLBACK_0(GameScene::win_timeout, this)));
    runAction(waitforwin);
}

void GameScene::loss_detected()
{
    lost_game=true;
    display_loss();
}

void GameScene::win_timeout()
{
    if (!lost_game) {
        display_win();
    }
}


