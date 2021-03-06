/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#ifndef __MapScene_H__
#define __MapScene_H__

#include "cocos2d.h"
#include "Roles\MapRoleSprite.h"
USING_NS_CC;
enum MapSceneActTag
{
	kMapSceneActTagPlayerMove = 20
};
class MapScene : public cocos2d::Layer
{
private:
	TMXTiledMap* bgMap;
	//Sprite* playerSprite;
	MapRoleSprite *playerSprite;//精灵
	TMXLayer* obstacleLayer;//碰撞层
	Vec2 offset;//每次移动的偏移值，如果没有移动就是0

	MoveBy *m_playerMoveAct;
	float m_playerMoveSpeed; //player移动的速度
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
	//层触摸回调函数
	virtual bool  onTouchBegan(Touch* touch, Event* envent);
	virtual void  onTouchEnded(Touch* touch, Event* envent);
	
	Vec2 tileCoordFromPosition(Vec2 pos);//触摸点在层上的opengl坐标坐标转换成瓦片坐标
	bool isColliding(Vec2 pos);//碰撞检测
	/*设置视点（屏幕的中心点），
	说白了就是移动Layer保证player尽量位于屏幕中心*/
	void moveViewPointToCenter();
	//void movePlayerSprite(float dt);
	//void changeMovingFlag();
	void playerMoveEnd();
    // implement the "static create()" method manually
    CREATE_FUNC(MapScene);
};

#endif // __MapScene_SCENE_H__
