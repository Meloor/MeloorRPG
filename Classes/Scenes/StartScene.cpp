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

#include "Scenes/StartScene.h"
#include "Scenes/MapScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartScene::createScene()
{
	auto scene = Scene::create();
	auto layer = StartScene::create();
	scene->addChild(layer);
	return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in StartSceneScene.cpp\n");
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin =  Director::getInstance()->getVisibleOrigin();
	Vec2 center = Vec2(visibleSize.width / 2, visibleSize.height / 2);
    /////////////////////////////
	//±³¾°1
	bg1 = Sprite::create("start_bg.png");//2195x768	
	bg1->setAnchorPoint(Vec2(0, 0));
	bg1->setPosition(Vec2(0,0));	
	this->addChild(bg1);
	//±³¾°2
	bg2 = Sprite::create("start_bg.png");//2195x768	
	bg2->setAnchorPoint(Vec2(0, 0));
	bg2->setPosition(Vec2(bg1->getContentSize().width, 0));	
	this->addChild(bg2);
	//²Ëµ¥
	MenuItemFont* item[4];		
	MenuItemFont::setFontName("Arial");
	MenuItemFont::setFontSize(40);
	auto dic = Dictionary::createWithContentsOfFile("fonts/chinese.xml");
	for (int i = 0; i < 4; i++) {
		auto str_en = String::createWithFormat("ch1_%d", i);
		auto str_ch = (String*)(dic->objectForKey(str_en->getCString()));
		item[i] = MenuItemFont::create(str_ch->getCString(),
			CC_CALLBACK_1(StartScene::menuCallback, this));
		item[i]->setTag(START+i);
	}
	auto menu = Menu::create(item[0], item[1], item[2], item[3], NULL);
	menu->alignItemsVertically();
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height/ 4));
	this->addChild(menu);
	return true;
}
void StartScene::onEnter() {
	Layer::onEnter();
	this->scheduleUpdate();
}
void StartScene::update(float dt) {
	//ÊµÏÖ±³¾°¹ö¶¯,Á½¸ö±³¾°Í¼½»Ìæ³öÏÖ
	float x1 = bg1->getPositionX() - 3.0f;//Ïò×óÒÆ¶¯
	float x2 = bg2->getPositionX() - 3.0f;
	bg1->setPositionX(x1);
	bg2->setPositionX(x2);
	//ÅÐ¶Ï±³¾°Í¼Æ¬ÊÇ·ñ³¬³ö±ß½ç
	if (x1 < -bg1->getContentSize().width) {
		bg1->setPositionX(bg2->getPositionX() + bg2->getContentSize().width - 2.0f);
	}
	else if (x2 < -bg2->getContentSize().width) {
		bg2->setPositionX(bg1->getPositionX() + bg1->getContentSize().width - 2.0f);
	}
}

void StartScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
	/*To navigate back to native iOS screen(if present) without quitting the application  ,
	do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a
	custom event created in RootViewController.mm as below*/
	EventCustom customEndEvent("game_scene_close_event");
	_eventDispatcher->dispatchEvent(&customEndEvent);
}
void StartScene::menuCallback(Ref* pSender) {
	auto menuItem = (MenuItemFont*)pSender;
	switch (menuItem->getTag())
	{
	case START:
		Director::getInstance()->pushScene(TransitionFadeTR::create(0.5, MapScene::createScene()));
		break;
	case READ:
		break;
	case SETTINGS:
		break;
	case EXIT:
		//CC_CALLBACK_1(StartScene::menuCloseCallback, menuItem);
		menuCloseCallback(menuItem);
	default:
		break;
	}
}



