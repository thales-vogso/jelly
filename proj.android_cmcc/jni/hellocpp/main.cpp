#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
//#include "MobClickJniHelper.h"
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"

#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init_demo");
    AppDelegate *pAppDelegate = new AppDelegate();
}
extern "C"
{
    void Java_org_cocos2dx_cpp_AppActivity_deliverProduct(JNIEnv* env, jobject thiz, jstring s)
    {
        const char *orderIdList = env->GetStringUTFChars(s, 0);
        LOGD("pay-deliverProduct = %s", orderIdList);

        PurchaseManager::getInstance()->addSuccessPayOrderIdString(orderIdList);
    }

    void Java_org_cocos2dx_cpp_AppActivity_payFaile(JNIEnv* env, jobject thiz)
        {
        PurchaseManager::getInstance()->purchaseFailed();
        }
}