//
//  SpriteInMap.cpp
//  ld31t1
//
//  Created by Mikel on 7/12/14.
//
//

#include <iostream>
#include <queue>
#include "utilities.h"
#include "SpriteInMap.h"

USING_NS_CC;
using namespace std;


const int sprite_tile_size = 64;


TMXTiledMap *SpriteInMap::themap=NULL;
float SpriteInMap::tile_size;
cocos2d::Size SpriteInMap::map_size;
cocos2d::Size SpriteInMap::map_isize;


bool SpriteInMap::init()
{
    if (!Sprite::init()) return false;
    
    map_position.x=0;
    map_position.y=0;
    
    setAnchorPoint(Vec2(0.5,0.5));
    return true;
}

void SpriteInMap::setMap(cocos2d::TMXTiledMap *amap)
{
    themap=amap;
    Size tilesize = amap->getTileSize();
    tile_size=tilesize.width;
    map_isize=amap->getMapSize();
    map_size.width=tile_size*map_isize.width;
    map_size.height=tile_size*map_isize.height;
    
    // std::cout<<"map set [";
    // std::cout<<tile_size<<"("<<tilesize.height<<") ";
    // std::cout<<" "<<map_isize.width<<","<<map_isize.height<<" "<<map_size.width<<","<<map_size.height<<"\n";
    
}

cocos2d::Vec2 SpriteInMap::coordsInMapFromNode(const cocos2d::Vec2 &pos)
{
    Vec2 inmappos;
    inmappos.x=(int)(pos.x/tile_size);
    inmappos.y=(int)((map_size.height-pos.y)/tile_size);
    return inmappos;
}

cocos2d::Vec2 SpriteInMap::coordsNodeFromInMap(const cocos2d::Vec2 &pos)
{
    Vec2 nodepos;
    nodepos.x=pos.x*tile_size+.5*tile_size;
    nodepos.y=map_size.height-(pos.y+1)*tile_size+.5*tile_size;
    return nodepos;
}

void SpriteInMap::setPositionInMap(int x, int y)
{
    map_position.x=x;
    map_position.y=y;
    setPosition(coordsNodeFromInMap(map_position));
// set position
}

void SpriteInMap::setPosition(float x, float y)
{
    Sprite::setPosition(x,y);
    map_position=coordsInMapFromNode(Vec2(x,y));
}

void SpriteInMap::setPosition(const cocos2d::Vec2 &pos)
{
    Sprite::setPosition(pos);
    map_position=coordsInMapFromNode(pos);
}

void SpriteInMap::setPositionInMap(const cocos2d::Vec2 &p)
{
    setPositionInMap(p.x, p.y);
}

cocos2d::Vec2 SpriteInMap::getPositionInMap()
{
    return map_position;
}



//bool SpriteInMap::tryToMoveTo(int deltax, int deltay, float duration, cocos2d::Animation *move_animation)
//{
//    Vec2 topos;
//    topos.x = map_position.x+deltax;
//    topos.y = map_position.y+deltay;
//    int dest_gid = themap->getLayer("main")->getTileGIDAt(topos);
//    if ( dest_gid!= 0) return false;
//    Spawn *twoactions;
//    twoactions=Spawn::createWithTwoActions(
//        MoveTo::create(duration, coordsNodeFromInMap(topos)),
//        Animate::create(move_animation)
//    );
//    this->runAction(twoactions);
//    return true;
//}

bool SpriteInMap::freeToMoveTo(int deltax, int deltay)
{
    Vec2 topos;
    topos.x = map_position.x+deltax;
    topos.y = map_position.y+deltay;
    int dest_gid = themap->getLayer("main")->getTileGIDAt(topos);
    if ( dest_gid!= 0) return false;
    return true;
}

cocos2d::Vec2 SpriteInMap::freeRandomPosition()
{
    Vec2 pos;
    int dest_gid;
    do {
        pos.x=random_i(map_isize.width);
        pos.y=random_i(map_isize.height);
        dest_gid=themap->getLayer("main")->getTileGIDAt(pos);
    } while (dest_gid!=0);
    return pos;
}

bool SpriteInMap::collidesWith(SpriteInMap *s)
{
    Vec2 p1 = this->getPosition();
    Vec2 p2 = s->getPosition();
    float deltax,deltay;
    deltax = p1.x - p2.x;
    deltax=deltax>0?deltax:-deltax;
    deltax-=sprite_tile_size*.8;
    deltay = p1.y - p2.y;
    deltay=deltay>0?deltay:-deltay;
    deltay-=sprite_tile_size*.8;
    
    if (deltax<0 && deltay<0) return true;
    
    return false;
}

std::vector<cocos2d::Vec2> SpriteInMap::findPath(cocos2d::Vec2 src, cocos2d::Vec2 dst)
{
    int iter_sin[]={0,1,0,-1};
    int iter_cos[]={1,0,-1,0};
    struct path_element {
        int x,y;
        float f,g;
        int prev_x,prev_y;
        bool closedset;
        bool openset;
    };
    //    int prev[(int)map_isize.width][(int)map_isize.height][3]; // 0 prev_x 1 prev_y 2 cost
    path_element mapa[(int)map_isize.width][(int)map_isize.height];
    for (int i=0;i<(int)map_isize.width;i++)
        for (int j=0;j<(int)map_isize.height;j++) {
            mapa[i][j].closedset=false;
            mapa[i][j].openset=false;
        }
    
    //vector<path_element> closed;
    priority_queue<path_element*,vector<path_element*>,function<bool(path_element*,path_element*)> > openq( [] (path_element *a, path_element *b) {
        return (a->f > b->f);
    });
    
    TMXLayer *maplayer = themap->getLayer("main");
    
    //themap->getLayer("selection")->setTileGID(13,Vec2(0,0));
    
    int sx=src.x;
    int sy=src.y;
    path_element *start = &mapa[sx][sy];
    start->x=src.x;
    start->y=src.y;
    start->g=0;
    start->f=0+abs(src.x-dst.x)+abs(src.y-dst.y);
    start->openset=true;
    openq.push(start);
    
    vector<Vec2> reverse_path;
    reverse_path.clear();
    
    while ( !openq.empty() ) {
        //cout << "openqueue size: " <<openq.size() <<"\n";
        path_element *current = openq.top(); openq.pop();
        //cout << "selected ("<<current->x<<","<<current->y<<")\n";
        if ( abs(current->x-dst.x)<0.5 && abs(current->y-dst.y)<0.5 ) {
            //cout<<"found\n";
            path_element *e = current;
            do {
                reverse_path.push_back(Vec2(e->x,e->y));
                e=&mapa[e->prev_x][e->prev_y];
            } while (e!=start);
            return reverse_path;
        }
        int cx=(int)current->x;
        int cy=(int)current->y;
        mapa[cx][cy].closedset=true;
        mapa[cx][cy].openset=false;
        for (int i=0;i<4;i++) {
            int nx=cx+iter_cos[i];
            int ny=cy+iter_sin[i];
            if (maplayer->getTileGIDAt(Vec2(nx,ny))!=0) continue;
            path_element *nb = &mapa[nx][ny];
            //cout << "n ("<<nx<<","<<ny<<")\n";
            if (nb->closedset) continue;
            if (nx<0 || ny<0 || nx>map_isize.width-1 || ny>map_isize.height-1) continue;
            if ( (!nb->openset) || (1+current->g<nb->g) ) {
                //cout << "changed\n";
                nb->x=nx;
                nb->y=ny;
                nb->g=1+current->g;
                nb->f=nb->g+abs(nb->x-dst.x)+abs(nb->y-dst.y);
                nb->prev_x=cx;
                nb->prev_y=cy;
                if (!nb->openset) openq.push(nb);
                nb->openset=true;
                // cout<<"f: "<<nb->g<<" g: "<<nb->f<<" \n";
            }
        }
    }
    return reverse_path;
}




