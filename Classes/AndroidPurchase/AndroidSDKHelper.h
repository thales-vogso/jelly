//
//  AndroidSDKHelper.h
//  PocketFishing
//
//  Created by 110102 on 14-5-16.
//

#ifndef __jelly3_5__AndroidSDKHelper__
#define __jelly3_5__AndroidSDKHelper__

#include "cocos2d.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
class AndroidSDKHelper
{
public:
    static AndroidSDKHelper *sharedHelper();
    
#pragma mark - 友盟推送...
    void setMusicEnabled(bool enabled);
    void openMoreGameLayer();
    void openQuitLayer();
    void setPhoneNumber(const char *number);
    std::string getPhoneNumber();
    bool isReachable();
    void sendPzPayWoSMS(std::string phoneNumber,std::string message);
    int getSPCode();
private:
    static AndroidSDKHelper *s_pSharedHelper;
    
    AndroidSDKHelper();
    virtual ~AndroidSDKHelper();
    bool init();
    
};

#endif /* defined(__PocketFishing__AndroidSDKHelper__) */
