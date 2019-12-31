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

#include "MapScene.h"
#include "GameGlobalConfig.h"
#include "Roles\MapRoleSprite.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MapScene::createScene()
{
	auto scene = Scene::create();
	auto layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in MapSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool MapScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
	m_playerMoveSpeed = GAME_PLAYER_MOVESPEED;
	//m_isMoving = false;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
	//��ȡ��Ƭ��ͼ
	bgMap = TMXTiledMap::create("tiledmaps/world_map01.tmx");
	//��ȡ��Ƭ��ͼ�ϰ���
	obstacleLayer = bgMap->getLayer("obstacle");//collider
	this->addChild(bgMap);
	//��ȡ����
	TMXObjectGroup* objects = bgMap->getObjectGroup("object");//ͨ�����������ö������󼯺�
	ValueMap player = objects->getObject("player");//ͨ����������ö���
	ValueMap originPoint = objects->getObject("originPoint");//ͨ����������ö���

	//���õ�ͼƫ��
	//��ö����ڵ�ͼ�ϵ�opengl����
	//���ö�������½���map�е�opengl����
	float ox = originPoint["x"].asFloat();
	float oy = originPoint["y"].asFloat();
	log("originPoint(%f,%f)", ox, oy);
	//�ƶ��㣬��������û�б�ģ����ϵĵ�ͼ�;��������ƶ�
	this->setPosition(-ox, -oy);

	////����player����λ�����þ���λ��
	///*
	//���ڶ����λ�ã�tiledmap����ʾ������UI���꣨ԭ�������Ͻǣ���ê��Ҳ�ڶ�������Ͻ�
	//���뵽cocos�л�ȡ����������opengl���꣨ԭ�������½ǣ���ê��Ҳ�ڶ�������½�
	//*/
	float x = player["x"].asFloat();//��ö����x������
	float y = player["y"].asFloat();//��ö����y������
	//								log("player(x=%f,y=%f)\n", x, y);
	//playerSprite = Sprite::create("roles/player.png");//�����з��þ���
	//playerSprite->setPosition(Vec2(x, y));//�����λ�÷ŵ������λ��
	//									  //�����λ���������½ǣ����Ծ����ê��ҲӦ�����ó����½�
	//playerSprite->setAnchorPoint(Vec2(0, 1));
	////playerSprite->setAnchorPoint(Vec2(0.5, 0.5));
	////playerSprite->setAnchorPoint(Vec2(0, 0));
	//this->addChild(playerSprite);

	playerSprite = MapRoleSprite::create(String::create("roles/DQV_19_slm.png"), String::create("Player"), true, kMapRoleSpriteDirectionDown);
	//player->setPosition(ccp(this->m_mapData.playerToX * GAME_TMX_ROLE_WIDTH, this->m_mapData.playerToY * GAME_TMX_ROLE_HEIGHT));
	//player->setTag(kRPGMapSceneLayerTagPlayer);
	playerSprite->setAnchorPoint(Vec2(0, 1));
	playerSprite->setPosition(Vec2(x, y));
	playerSprite->m_type = kMapRoleSpriteTypePlayer;
	this->addChild(playerSprite);


	this->setTouchEnabled(true);//�����㴥������
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	return true;
}
//������λ�ú�playerSpriteλ�ý��бȽ�
bool MapScene::onTouchBegan(Touch* touch, Event* envent) {
	Vec2 touchp = touch->getLocation();//��ȡ�������opengl��Ļ����
	Vec2 touchInLayer = touchp - this->getPosition();//�������ڲ��ϵ�opengl����
													 //log("touch pos(%f,%f)", touchp.x, touchp.y);
	Vec2 playerp = playerSprite->getPosition();//�����ڲ��ϵ�opengl����
											   //log("player pos(%f,%f)", playerp.x, playerp.y);
	Vec2 diff = touchInLayer - playerp;//�������ɫ֮��ľ����
	offset = Vec2(0, 0);//ÿ���ƶ���ƫ��ֵ�����û���ƶ�����0
	if (abs(diff.x) > abs(diff.y)) {
		if (diff.x > 0) {
			log("go right");
			offset.x = bgMap->getTileSize().width;//ÿ��ֻ�ƶ�һ��

			playerSprite->startMoveRight();
			//playerSprite->runAction(FlipX::create(FALSE));
		}
		else {
			log("go left");
			offset.x = -bgMap->getTileSize().width;
			playerSprite->startMoveLeft();
			//playerSprite->runAction(FlipX::create(TRUE));
		}
	}
	else {
		if (diff.y > 0) {
			offset.y = bgMap->getTileSize().height;

			playerSprite->startMoveUp();
			log("go up");
		}
		else {
			offset.y = -bgMap->getTileSize().height;

			playerSprite->startMoveDown();
			log("go down");
		}
	}
	if (this->isColliding(playerSprite->getPosition()+offset)==false){
		this->m_playerMoveAct = MoveBy::create(this->m_playerMoveSpeed, offset);
		this->m_playerMoveAct->setTag(kMapSceneActTagPlayerMove);

		playerSprite->runAction(Sequence::create(this->m_playerMoveAct,
			CallFunc::create(CC_CALLBACK_0(MapScene::playerMoveEnd,this)),NULL));
	}
	return true;
}
void   MapScene::onTouchEnded(Touch* touch, Event* envent) {
	//this->unschedule(SEL_SCHEDULE(&MapScene::movePlayerSprite));
}
//��������ڲ��ϵ�opengl��������ת������Ƭ����
//posΪ�����ê��(���½�)�ڲ��ϵ�opengl���꣬��ԭ��Ϊ���ԭ��
Vec2 MapScene::tileCoordFromPosition(Vec2 pos)
{
	//��ͼy����Ƭ��������ÿ����Ƭ�ĸ߶ȵõ���ͼ��y���ܸ߶�
	int mpy = bgMap->getMapSize().height * bgMap->getTileSize().height;

	//ת�����ڵ�ͼ��opengl�������ꡣ���ڲ��ԭ��Ҳ�ǵ�ͼ��openglԭ�㡣
	Vec2 posInMap = Vec2(pos.x, pos.y);
	//ת�����ڵ�ͼ��UI�������꣨ԭ�������Ͻǣ�
	Vec2 posInMapUI = Vec2(pos.x, mpy - pos.y);

	//ת������Ƭ����
	int x = posInMapUI.x / bgMap->getTileSize().width;
	int y = posInMapUI.y / bgMap->getTileSize().height;
	return Vec2(x, y);
}

bool MapScene::isColliding(Vec2 pos) {
	//ת������Ƭ�����Է����ж�
	Vec2 tilePos = this->tileCoordFromPosition(pos);
	int tileGid = obstacleLayer->getTileGIDAt(tilePos);
	if (tileGid > 0) {
		Value prop = bgMap->getPropertiesForGID(tileGid);//���gid������
		ValueMap propMap = prop.asValueMap();//ǿ������ת��
		if (propMap["collidable"].asBool()) {//���û��Ĭ��ֵ��Ӧ����false
			//SimpleAudioEngine::getInstance()->playEffect("empty.wav");
			return true;
		}
		
	}
	return false;
}

//void MapScene::movePlayerSprite(float dt) {
//	auto nextPos = playerSprite->getPosition() + offset;
//	if (this->isColliding(nextPos)==false) {//���û�з�����ײ
//		auto moveAction = MoveBy::create(this->m_playerMoveSpeed, offset);
//		auto callFunc = CallFunc::create(CC_CALLBACK_0(MapScene::changeMovingFlag, this));
//		//auto callfunc = CallFunc::create([this](Ref* pSender) {
//		//	this->m_isMoving = false;//�ƶ���������Ϊfalse
//		//});
//		playerSprite->runAction(Sequence::create(callFunc,moveAction,callFunc,NULL));
//		this->moveViewPointToCenter();
//	}
//}

//void MapScene::changeMovingFlag() {
//
//}
void MapScene::playerMoveEnd() {
	playerSprite->stopMove();
	playerSprite->stopActionByTag(kMapSceneActTagPlayerMove);
	this->m_playerMoveAct = NULL;
}
//�ƶ�Layer��֤player����λ����Ļ����
void MapScene::moveViewPointToCenter()//pos�Ǿ����ڲ��ϵ�opengl����
{
	//��ͼy����Ƭ��������ÿ����Ƭ�ĸ߶ȵõ���ͼ��y���ܸ߶�
	int mpy = bgMap->getMapSize().height * bgMap->getTileSize().height;
	int mpx = bgMap->getMapSize().width * bgMap->getTileSize().width;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 layerNextPos = this->getPosition() - offset;//����ƶ�����;�����ƶ������෴

													 //��ֹ���ֺڱ�
	if (layerNextPos.x > 0)//������ƫ�ƣ���ô��߾ͻ��кڱ�
		layerNextPos.x = 0;
	if (layerNextPos.x < -mpx + visibleSize.width)//������ƫ�ƣ�Ҫ����һ������Ļ���
		layerNextPos.x = -mpx + visibleSize.width;
	if (layerNextPos.y > 0)//������ƫ�ƣ���ô����ͻ��кڱ�
		layerNextPos.y = 0;
	if (layerNextPos.y < -mpy + visibleSize.height)//������ƫ�ƣ�Ҫ����һ������Ļ�߶�
		layerNextPos.y = -mpy + visibleSize.height;

	//����߽��Ҫ���ƶ�1/2��Ļ�ľ����ٹ�����Ļ
	float px = playerSprite->getPositionX();
	float py = playerSprite->getPositionY();
	if (px <= visibleSize.width / 2)
		layerNextPos.x = 0;
	if (px >= mpx - visibleSize.width / 2)
		layerNextPos.x = -mpx + visibleSize.width;
	if (py <= visibleSize.height / 2)
		layerNextPos.y = 0;
	if (py >= mpy - visibleSize.height / 2)
		layerNextPos.y = -mpy + visibleSize.height;

	auto moveAction = MoveBy::create(this->m_playerMoveSpeed, -offset);
	this->runAction(moveAction);
	//this->setPosition(layerNextPos);//���õ���Layer��λ��,�ƶ�����൱���ƶ���ͼ
}



