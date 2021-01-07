#include "AppDelegate.h"
#include "loading/Loading.h"
#include "loading/Logo.h"
#include "AndroidPurchase/PurchaseManager.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//#include "protcols/android/PluginJniHelper.h"
//using namespace anysdk::framework;
#endif
USING_NS_CC;
const std::string AppDelegate::GAMEPAUSE = "app_game_pause";
const std::string AppDelegate::GAMERESUME = "app_game_resume";
AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}
void AppDelegate::initGLContextAttrs()
{
	//set OpenGL context attributions,now can only set six attributions:
	//red,green,blue,alpha,depth,stencil
	GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };

	GLView::setGLContextAttrs(glContextAttrs);
}
bool AppDelegate::applicationDidFinishLaunching() {

//#if(CC_TARGET_PLATFORM!=CC_PLATFORM_WIN32)
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("546c65a4fd98c52d32001daf", "2");
#else
 #if TARGET_CHANNEL == TTARGET_CHANNE_PZPAY
//#define TARGET_PZ10018
//#define TARGET_PZ10020
//#define TARGET_PZ10021
//#define TARGET_PZ10022
	#if TARGET_PZCHANNEL == TARGET_PZ10018
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("546c65a4fd98c52d32001daf", "2");
	#elif TARGET_PZCHANNEL == TARGET_PZ10019
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5608b69167e58e898b0010b8", "2");

	#elif TARGET_PZCHANNEL == TARGET_PZ10020
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5608b5cce0f55a4367000b19", "2");

	#elif TARGET_PZCHANNEL == TARGET_PZ10021
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5608b64de0f55a26640023b5", "2");

	#elif TARGET_PZCHANNEL == TARGET_PZ10022
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5608b67067e58e7d1a001ed6", "2");

	#endif

#elif TARGET_CHANNEL == TARGET_CHANNE_AND_GAME
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("55fa6ac5e0f55a19e90027d7", "2");
#elif TARGET_CHANNEL == TARGET_CHANNE_CMCC
    
#elif TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("56175c1ce0f55aff720029b4", "2");
#elif TARGET_CHANNEL == TARGET_CHANNE_EGAME
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("561df58367e58ec25100468e", "2");
#elif TARGET_CHANNEL == TARGET_CHANNE_UNIPAY
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("56284905e0f55ad8ee001910", "2");
    
#elif TARGET_CHANNEL == TARGET_CHANNE_SWSDK
    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("5636c620e0f55a3f97001e12", "2");
#elif TARGET_CHANNEL == TARGET_CHANNE_TIANYI
	MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL("564e85f6e0f55acb51008605", "2");
#endif
    
#endif
//#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	umeng::MobClickCpp::updateOnlineConfig();
#endif
	

//#endif
//#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//	std::string appKey = "BC26F841-OOOO-OOOO-OOOO-OOOOOOOOOOOO";
//	std::string appSecret = "1dff378a8f254ecOOOOOOOOOOOOO";
//	std::string privateKey = "696064B29E9A0OOOOOOOOOOOOO";
//	std::string oauthLoginServer = "http://oauth.anysdk.com/api/OauthLoginDemo/Login.php";
//
//	AgentManager::getInstance()->init(appKey, appSecret, privateKey, oauthLoginServer);
//	AgentManager::getInstance()->loadALLPlugin();
//#endif


//#ifdef TEST
//	int time1 = time(NULL);
//	
//#if (CC_TARGET_PLATFORM!=CC_PLATFORM_WIN32)
//	std::string value = umeng::MobClickCpp::getConfigParam("day");
//    CCLOG("umgame_value = %s",value.c_str());
//    std::string test = umeng::MobClickCpp::getConfigParam("test");
//    CCLOG("umgame_test = %s",test.c_str());
//
//	int n = std::atoi(value.c_str());
//	int timenow = 1421747394-18*60*60;
//	if(n==0)
//	{
//		n=300;
//	}
//	if (time1 > timenow && time1 < timenow + 86400*n)
//	{
//
//	}
//	else
//	{
////#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
////		umeng::MobClickCpp::end();
////#endif
////		Director::getInstance()->end();
////#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////		exit(0);
////#endif
//	}
//#endif
//#endif

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
		glview = GLViewImpl::create("Jelly");
        director->setOpenGLView(glview);
		glview->setFrameSize(1300, 621);
    }
	glview->setDesignResolutionSize(2208, 1242, ResolutionPolicy::FIXED_HEIGHT);
#ifdef TEST
    // turn on display FPS
   //director->setDisplayStats(true);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
	director->setProjection(kCCDirectorProjection2D);
	Texture2D::PVRImagesHavePremultipliedAlpha(true);
    // create a scene. it's an autorelease object
	auto scene = Logo::createScene();
    // run
    director->runWithScene(scene);
    CCLOG("PurchaseManager::getInstance");
    PurchaseManager::getInstance();
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
	
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	umeng::MobClickCpp::applicationDidEnterBackground();
#endif
	//pause
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GAMEPAUSE, nullptr);
	
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	umeng::MobClickCpp::applicationWillEnterForeground();
#endif
	//resume
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GAMERESUME, nullptr);
}
