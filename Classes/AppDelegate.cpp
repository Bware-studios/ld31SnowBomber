#include <iostream>
#include "AppDelegate.h"
#include "GameScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}


bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Fred");
        
        Size fs=glview->getFrameSize();
        std::cout<<fs.width<<" x "<<fs.height<<"\n";
        //glview->setFrameSize(1000, 800);
        
        director->setOpenGLView(glview);
    } else {
        Size fs=glview->getFrameSize();
        std::cout<<fs.width<<" x "<<fs.height<<"\n";

    }
    
    std::vector<std::string> searchPaths;
    searchPaths.push_back("assets");
    FileUtils::getInstance()->setSearchPaths(searchPaths);
    

    glview->setDesignResolutionSize(960,640,ResolutionPolicy::SHOW_ALL);
    
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = GameScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
