//
//  AndroidSDKHelper.cpp
//  PocketFishing
//
//  Created by 110102 on 14-5-16.
//

#include "AndroidSDKHelper.h"
#include "data/User.h"
#include "cache/Music.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"


using namespace cocos2d;
using namespace std;
static std::string m_sTelePhoneNnmber = "";
AndroidSDKHelper *AndroidSDKHelper::s_pSharedHelper = NULL;
AndroidSDKHelper *AndroidSDKHelper::sharedHelper()
{
    if(NULL == s_pSharedHelper)
    {
        s_pSharedHelper = new AndroidSDKHelper();
        s_pSharedHelper->init();
    }
    return s_pSharedHelper;
}

bool AndroidSDKHelper::init()
{
    //
    return true;
}

AndroidSDKHelper::AndroidSDKHelper()
{
    //
}

AndroidSDKHelper::~AndroidSDKHelper()
{
    delete s_pSharedHelper;
    s_pSharedHelper = NULL;
}


void AndroidSDKHelper::setMusicEnabled(bool enabled)
{
    data::User::getInstance()->setBGM(enabled);

    data::User::getInstance()->setSoundEffect(enabled);

    if (enabled){
//        cache::Music::getInstance()->playBGM(cache::Music::BGMName::GATEWAY);
    }else{
        cache::Music::getInstance()->pauseBGM();
    }
}

void AndroidSDKHelper::openMoreGameLayer()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    
    bool isExist = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "openMoreGameLayer", "()V");
    if(instance && isExist)
    {
        info.env->CallVoidMethod(instance, info.methodID);
        info.env->DeleteLocalRef(info.classID);
    }
#endif
}

void AndroidSDKHelper::openQuitLayer()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    
    bool isExist = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "openQuitLayer", "()V");
    if(instance && isExist)
    {
        info.env->CallVoidMethod(instance, info.methodID);
        info.env->DeleteLocalRef(info.classID);
    }
#endif
}

bool AndroidSDKHelper::isReachable()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    bool isExist = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "isReachable", "()Z");
    
    jboolean ret = 0;
    if(isExist && instance)
    {
        ret = info.env->CallBooleanMethod(instance, info.methodID);
    }
    
    log("%s", ret ? "yes":"no");
    if(ret) return true;
    else return false;
#else
    return true;
#endif

}

int AndroidSDKHelper::getSPCode()
{

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    int code = kBuyMethodAndGame;
    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    bool isExist = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "getSPCode", "()I");
    if(instance && isExist)
    {
        code = info.env->CallIntMethod(instance, info.methodID);
    }
    return code;
#else
    return kBuyMethodAndGame;// iOS用不到....
#endif
}

void AndroidSDKHelper::sendPzPayWoSMS(std::string phoneNumber,std::string message)
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    
    bool isExist = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "sendSMS", "(Ljava/lang/String;Ljava/lang/String;)V");
    if(instance && isExist)
    {
        jstring phoneNumberStr = info.env->NewStringUTF(phoneNumber.c_str());
        jstring messageStr = info.env->NewStringUTF(message.c_str());

        info.env->CallVoidMethod(instance, info.methodID,phoneNumberStr,messageStr);
        info.env->DeleteLocalRef(info.classID);
    }
#endif
}

void AndroidSDKHelper::setPhoneNumber(const char *number)
{
    if (number) {
        m_sTelePhoneNnmber = number;
    }
    
}

std::string AndroidSDKHelper::getPhoneNumber()
{
    return m_sTelePhoneNnmber;
}

