//
//  MapRoleSprite.cpp
//  OzgGameRPG
//
//  Created by ozg on 14-3-18.
//
//

#include "MapRoleSprite.h"
#include "Utility.h"

#define MOVE_ACT 0.25 //行走动画的下一帧时间

MapRoleSprite::~MapRoleSprite()
{
    if(this->m_roleSpriteFrames) this->m_roleSpriteFrames->release();
    this->m_name->release();
   
    log("MapRoleSprite 释放");
}

bool MapRoleSprite::init(String *roleTexture, String* name, bool isPlayer, int defaultSpriteFrameIndex)
{
	//精灵帧图是4x4的
    this->m_roleSpriteFrames = Utility::createSpriteFrames(roleTexture->getCString(), 4, 4);
    this->m_roleSpriteFrames->retain();
    
    this->m_name = name;
    this->m_name->retain();
    
    this->m_isPlayer = isPlayer;
    
    if(Sprite::initWithSpriteFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(defaultSpriteFrameIndex)))
    {
        CCLabelTTF *nameLab = CCLabelTTF::create(this->m_name->getCString(), "Arial", 15, CCSizeMake(this->getContentSize().width * 3.0, 20), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        nameLab->setPosition(ccp(15, 45));
        
        if(this->m_isPlayer)
            nameLab->setColor(ccc3(255, 50, 40));
        else
            nameLab->setColor(ccc3(0, 0, 0));
        
        this->addChild(nameLab);
        
        this->m_direction = kMapRoleSpriteDirectionNone;
        
        return true;
    }
    
    this->m_roleSpriteFrames->release();
    return false;
}

//static
MapRoleSprite* MapRoleSprite::create(String *roleTexture, String* name, bool isPlayer, int defaultSpriteFrameIndex)
{
    MapRoleSprite *obj = new MapRoleSprite();
    if(obj && obj->init(roleTexture, name, isPlayer, defaultSpriteFrameIndex))
    {
        obj->autorelease();
        return obj;
    }
    CC_SAFE_DELETE(obj);
    return NULL;
}

////private
void MapRoleSprite::startMove(MapRoleSpriteMoveActTag actTag)
{
    if(this->m_isMoving && this->m_currMoveActTag != actTag)
    {
        this->stopActionByTag(this->m_currMoveActTag);
        this->m_isMoving = false;
    }
    
    if(!this->m_isMoving)
    {
        //Array *spriteFrames = Array::create();
		Vector<SpriteFrame*> spriteFrames;
        switch (actTag)
        {
            case kMapRoleSpriteMoveActTagUp:
            {
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(8));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(9));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(10));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(11));
                
                this->m_direction = kMapRoleSpriteDirectionUp;
            }
                break;
            case kMapRoleSpriteMoveActTagDown:
            {
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(0));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(1));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(2));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(3));
                
                this->m_direction = kMapRoleSpriteDirectionDown;
            }
                break;
            case kMapRoleSpriteMoveActTagLeft:
            {            
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(4));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(5));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(6));
                spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(7));
                this->m_direction = kMapRoleSpriteDirectionLeft;
            }
                break;
            case kMapRoleSpriteMoveActTagRight:
            {             
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(12));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(13));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(14));
				spriteFrames.pushBack((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(15));
                this->m_direction = kMapRoleSpriteDirectionRight;
            }
                break;
            default:
                break;
        }
        
        Animation *animation = Animation::createWithSpriteFrames(spriteFrames, MOVE_ACT);
        RepeatForever *animate = RepeatForever::create(Animate::create(animation));
        animate->setTag(actTag);
        this->m_currMoveActTag = actTag;
        
        this->runAction(animate);
        
        this->m_isMoving = true;
    }
}

void MapRoleSprite::startMoveUp()
{
    this->startMove(kMapRoleSpriteMoveActTagUp);
    
}

void MapRoleSprite::startMoveDown()
{
    this->startMove(kMapRoleSpriteMoveActTagDown);
    
}

void MapRoleSprite::startMoveLeft()
{
    this->startMove(kMapRoleSpriteMoveActTagLeft);
    
}

void MapRoleSprite::startMoveRight()
{
    this->startMove(kMapRoleSpriteMoveActTagRight);
    
}

void MapRoleSprite::stopMove()
{
    if(!this->m_isMoving)
        return;
    
    switch (this->m_currMoveActTag)
    {
        case kMapRoleSpriteMoveActTagUp:
        {
            this->stopActionByTag(kMapRoleSpriteMoveActTagUp);
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(8));
        }
            break;
        case kMapRoleSpriteMoveActTagDown:
        {
            this->stopActionByTag(kMapRoleSpriteMoveActTagDown);
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(0));
        }
            break;
        case kMapRoleSpriteMoveActTagLeft:
        {
            this->stopActionByTag(kMapRoleSpriteMoveActTagLeft);
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(4));
        }
            break;
        case kMapRoleSpriteMoveActTagRight:
        {
            this->stopActionByTag(kMapRoleSpriteMoveActTagRight);
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(12));
        }
            break;
        default:
            break;
    }
    
    this->m_isMoving = false;
}

void MapRoleSprite::setDirection(MapRoleSpriteDirection direction)
{
    this->m_direction = direction;
    
    switch (this->m_direction)
    {
        case kMapRoleSpriteDirectionUp:
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(8));
            break;
        case kMapRoleSpriteDirectionDown:
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(0));
            break;
        case kMapRoleSpriteDirectionLeft:
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(4));
            break;
        case kMapRoleSpriteDirectionRight:
            this->setDisplayFrame((SpriteFrame*)this->m_roleSpriteFrames->objectAtIndex(12));
            break;
        default:
            break;
    }
    
}
