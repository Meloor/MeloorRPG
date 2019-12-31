
#ifndef __Utility_H__
#define __Utility_H__

#include "cocos2d.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
////(注意：对工程右键-> 属性 -> 连接器 -> 输入 -> 附加依赖项    栏目->后面有个按钮，点击打开，换一行加入libiconv.lib，或者在最后空一格加上libiconv.lib也行）
//#include "iconv\iconv.h" 
//#endif  

USING_NS_CC;
using namespace std;

class Utility
{       
public:  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	//windows的乱码解决方案
//	static int GBKToUTF8(string &gbkStr,const char* toCode,const char* formCode);
//#endif  
//	//通用的乱码解决方案
//	static string generalString(string &str); 
//    static string generalString(const char* str);

	static void clearAnimate(const char *plist); //清空plist生成的帧动画
	static ActionInterval* createAnimate(const char *plist); //利用plist生成帧动画，plist结构在实现文件里面
    
	static ActionInterval* createAnimate(Texture2D* texture, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops);
    static ActionInterval* createAnimate(const char* fileimage, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops);
    static Array* createSpriteFrames(Texture2D* texture, int xNum, int yNum);
    static Array* createSpriteFrames(const char* fileimage, int xNum, int yNum);  
};

#endif /*#define __Utility_H__ */
