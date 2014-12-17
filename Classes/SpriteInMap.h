//
//  SpriteInMap.h
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#ifndef __ld31t1__SpriteInMap__
#define __ld31t1__SpriteInMap__

#include <stdio.h>
#include "cocos2d.h"

extern const int sprite_tile_size;


class SpriteInMap : public cocos2d::Sprite
{
public:
    bool init();
    CREATE_FUNC(SpriteInMap);
    static void setMap(cocos2d::TMXTiledMap *amap);
    static cocos2d::Vec2 coordsInMapFromNode(const cocos2d::Vec2 &pos);
    static cocos2d::Vec2 coordsNodeFromInMap(const cocos2d::Vec2 &pos);
    
    void setPositionInMap(int x, int y);
    void setPositionInMap(const cocos2d::Vec2 &p);
    void setPosition(float x, float y);
    void setPosition(const cocos2d::Vec2 &pos);
    
    cocos2d::Vec2 getPositionInMap();
    
//    bool tryToMoveTo(int deltax, int deltay, float duration, cocos2d::Animation *move_animation);
    bool freeToMoveTo(int deltax, int deltay);
    static cocos2d::Vec2 freeRandomPosition();
    
    bool collidesWith(SpriteInMap *s);

    std::vector<cocos2d::Vec2> findPath(cocos2d::Vec2 src, cocos2d::Vec2 dst);

    
protected:
    cocos2d::Vec2 map_position;
    static cocos2d::TMXTiledMap *themap;
    static float tile_size;
    static cocos2d::Size map_isize;


private:
    static cocos2d::Size map_size;
    

};


#endif /* defined(__ld31t1__SpriteInMap__) */
