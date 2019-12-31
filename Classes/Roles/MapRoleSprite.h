//
//  MapRoleSprite.h
//  OzgGameRPG
//
//  Created by ozg on 14-3-18.
//
//

#ifndef __MapRoleSprite__H__
#define __MapRoleSprite__H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

enum MapRoleSpriteMoveActTag
{
    kMapRoleSpriteMoveActTagUp = 1,
    kMapRoleSpriteMoveActTagDown = 2,
    kMapRoleSpriteMoveActTagLeft = 3,
    kMapRoleSpriteMoveActTagRight = 4
};

enum MapRoleSpriteDirection
{
    kMapRoleSpriteDirectionNone = 0,
    kMapRoleSpriteDirectionUp = 1,
    kMapRoleSpriteDirectionDown = 2,
    kMapRoleSpriteDirectionLeft = 3,
    kMapRoleSpriteDirectionRight = 4
};

enum MapRoleSpriteType
{
    kMapRoleSpriteTypePlayer = 1,
    kMapRoleSpriteTypeNPC = 2
};

class MapRoleSprite : public Sprite
{      
	//命名加了m_表示自己定义的变量，有利于变量查找
private:   
    MapRoleSpriteMoveActTag m_currMoveActTag;
    Array* m_roleSpriteFrames;//存精灵帧
	//Vector<SpriteFrame*> m_roleSpriteFrames;
    bool m_isMoving;
    String* m_name;
public:  
    MapRoleSpriteDirection m_direction; //该对象向着哪个方向 
    MapRoleSpriteType m_type;
    bool m_isPlayer;
private: 
    void startMove(MapRoleSpriteMoveActTag actTag);
public:   
    virtual ~MapRoleSprite();
    bool init(String *roleTexture, String* name, bool isPlayer, int defaultSpriteFrameIndex);
    static MapRoleSprite* create(String *roleTexture, String* name, bool isPlayer, int defaultSpriteFrameIndex);
    
    void startMoveUp();
    void startMoveDown();
    void startMoveLeft();
    void startMoveRight();
    
    void stopMove();
    
    void setDirection(MapRoleSpriteDirection direction);
};

#endif /* defined(__OzgGameRPG__MapRoleSprite__) */
