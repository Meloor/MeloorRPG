
#include "Utility.h"



//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
////windows的乱码解决方案
//
////字符转换，使cocos2d-x在win32平台支持中文显示  
//int Utility::GBKToUTF8(string &gbkStr, const char* toCode, const char* formCode)  
//{  
//    iconv_t iconvH;  
//    iconvH = iconv_open(formCode, toCode);  
//    if(iconvH == 0)  
//    {  
//        return -1;  
//    }  
//  
//    const char* strChar = gbkStr.c_str();  
//    const char** pin = &strChar;  
//  
//    size_t strLength = gbkStr.length();  
//    char* outbuf = (char*)malloc(strLength * 4);  
//    char* pBuff = outbuf;  
//    memset(outbuf, 0, strLength * 4);  
//    size_t outLength = strLength * 4;  
//    if(-1 == iconv(iconvH, pin, &strLength, &outbuf, &outLength))  
//    {  
//        iconv_close(iconvH);  
//        return -1;  
//    }  
//  
//    gbkStr = pBuff;  
//    iconv_close(iconvH);  
//    return 0;  
//}  
//#endif  

//string Utility::generalString(std::string &str)
//{  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	Utility::GBKToUTF8(str, "gbk", "utf-8"); //后面两个参数就默认了,免得后面再传参麻烦  
//	return str;  
//#else 
//	return str;
//#endif  
//
//}

//string Utility::generalString(const char* str)
//{
//    std::string s(str);
//    return Utility::generalString(s);
//}


void Utility::clearAnimate(const char *plist)
{
	Dictionary *root = Dictionary::createWithContentsOfFile(plist);
	Array *frames = (Array*)root->objectForKey("frames");
	Ref *item = NULL;
	CCARRAY_FOREACH(frames, item)
	{
		String *itemStr = (String*)item;
		TextureCache::sharedTextureCache()->removeTextureForKey(itemStr->getCString());
	}
}

ActionInterval* Utility::createAnimate(const char *plist)
{
	//plist的根节点为Root(Dictionary)
	//plist的结构为frames(Array<String*>),loop(Number),delay(Number),rect(Dictionary)里面有x(Number),y(Number),width(Number),height(Number)

	//loop为循环次数，-1为无限次
	//delay为每帧的时间间隔
	//rect帧的范围，一般为0, 0, 图片宽, 图片高
	//frames帧的路径

	//Array *spriteFrames = Array::create();
	Vector<SpriteFrame*> spriteFrames;
	Dictionary *root = Dictionary::createWithContentsOfFile(plist);

	unsigned int loops = ((String*)root->objectForKey("loop"))->intValue();
	float delay = ((String*)root->objectForKey("delay"))->floatValue();
	Array *frames = (Array*)root->objectForKey("frames");
	Dictionary *rectDict = (Dictionary*)root->objectForKey("rect");
	float rectX = ((String*)rectDict->objectForKey("x"))->floatValue();
	float rectY = ((String*)rectDict->objectForKey("y"))->floatValue();
	float rectWidth = ((String*)rectDict->objectForKey("width"))->floatValue();
	float rectHeight = ((String*)rectDict->objectForKey("height"))->floatValue();
	Rect rect = Rect(rectX, rectY, rectWidth, rectHeight);

	Ref *item = NULL;
	CCARRAY_FOREACH(frames, item)
	{
		String *itemStr = (String*)item;

		SpriteFrame *spriteFrame = SpriteFrame::create(itemStr->getCString(), rect);
		spriteFrames.pushBack(spriteFrame);
	}
	
	Animation *animation = Animation::createWithSpriteFrames(spriteFrames, delay);
	Animate *animate = Animate::create(animation);

	if (loops)
		return RepeatForever::create(animate);
	else
		return animate;

}

ActionInterval* Utility::createAnimate(cocos2d::Texture2D *texture, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops)
{
    Array *frames = Utility::createSpriteFrames(texture, xNum, yNum);
    
    //Array *useFrames = Array::create();
	Vector<SpriteFrame*> useFrames;
	for (int i = 0; i < (int)frameIndces.size(); i++) {
		auto spriteFrame = (SpriteFrame*)frames->objectAtIndex(frameIndces[i]);
		useFrames.pushBack(spriteFrame);
	}
        
    
    Animation *animation = Animation::createWithSpriteFrames(useFrames, delay);
    animation->setLoops(loops);
    Animate *animate = Animate::create(animation);
    
    if(loops)
        return RepeatForever::create(animate);
    else
        return animate;
}

ActionInterval* Utility::createAnimate(const char *fileimage, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops)
{
    Array *frames = Utility::createSpriteFrames(fileimage, xNum, yNum);
    
    //Array *useFrames = Array::create();  
    //for (int i = 0; i < (int)frameIndces.size(); i++)
    //    useFrames->addObject(frames->objectAtIndex(frameIndces[i]));
	Vector<SpriteFrame*> useFrames;
	for (int i = 0; i < (int)frameIndces.size(); i++) {
		auto spriteFrame = (SpriteFrame*)frames->objectAtIndex(frameIndces[i]);
		useFrames.pushBack(spriteFrame);
	}

    Animation *animation = Animation::createWithSpriteFrames(useFrames, delay);
    Animate *animate = Animate::create(animation);
    
    if(loops)
        return RepeatForever::create(animate);
    else
        return animate;
}

Array* Utility::createSpriteFrames(cocos2d::Texture2D *texture, int xNum, int yNum)
{
    Array *frames = Array::create();
    
    float itemWidth = texture->getContentSizeInPixels().width / (float)xNum;
    float itemHeight = texture->getContentSizeInPixels().height / (float)yNum;
    
    for (int i = 0; i < yNum; i++)
    {
        for (int j = 0; j < xNum; j++)
        {
//            log("%f %f %f %f", (float)j * itemWidth, (float)i * itemHeight, itemWidth, itemHeight);
            
            SpriteFrame *s = SpriteFrame::createWithTexture(texture, Rect((float)j * itemWidth, (float)i * itemHeight, itemWidth, itemHeight));
            frames->addObject(s);
            
        }
        
    }
    
    return frames;
}

Array* Utility::createSpriteFrames(const char *fileimage, int xNum, int yNum)
{
    return Utility::createSpriteFrames(TextureCache::sharedTextureCache()->addImage(fileimage), xNum, yNum);
}
