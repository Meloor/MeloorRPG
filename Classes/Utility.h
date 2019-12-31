
#ifndef __Utility_H__
#define __Utility_H__

#include "cocos2d.h"

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
////(ע�⣺�Թ����Ҽ�-> ���� -> ������ -> ���� -> ����������    ��Ŀ->�����и���ť������򿪣���һ�м���libiconv.lib������������һ�����libiconv.libҲ�У�
//#include "iconv\iconv.h" 
//#endif  

USING_NS_CC;
using namespace std;

class Utility
{       
public:  
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_WIN8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	//windows������������
//	static int GBKToUTF8(string &gbkStr,const char* toCode,const char* formCode);
//#endif  
//	//ͨ�õ�����������
//	static string generalString(string &str); 
//    static string generalString(const char* str);

	static void clearAnimate(const char *plist); //���plist���ɵ�֡����
	static ActionInterval* createAnimate(const char *plist); //����plist����֡������plist�ṹ��ʵ���ļ�����
    
	static ActionInterval* createAnimate(Texture2D* texture, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops);
    static ActionInterval* createAnimate(const char* fileimage, int xNum, int yNum, vector<int> frameIndces, float delay, bool loops);
    static Array* createSpriteFrames(Texture2D* texture, int xNum, int yNum);
    static Array* createSpriteFrames(const char* fileimage, int xNum, int yNum);  
};

#endif /*#define __Utility_H__ */
