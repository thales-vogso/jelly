#include "AppDelegate.h"
#include "cocos2d.h"
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#include <android/log.h>
//#include "MobClickJniHelper.h"
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
#include "AndroidPurchase/AndroidSDKHelper.h"
#define  LOG_TAG    "main"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

using namespace cocos2d;

void cocos_android_app_init (JNIEnv* env, jobject thiz) {
    LOGD("cocos_android_app_init");
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
    void Java_org_cocos2dx_cpp_AppActivity_andGameDeliverProduct(JNIEnv* env, jobject thiz, jstring s)
    {
        const char *orderIdList = env->GetStringUTFChars(s, 0);
        LOGD("pay-deliverProduct = %s", orderIdList);

        PurchaseManager::getInstance()->addSuccessPayOrderIdStringForAndGame(orderIdList);
    }

    void Java_org_cocos2dx_cpp_AppActivity_payFaile(JNIEnv* env, jobject thiz)
    {

    PurchaseManager::getInstance()->purchaseFailed();
    }
    void Java_org_cocos2dx_cpp_AppActivity_setMusicEnabled(JNIEnv *env, jobject thiz, jboolean b)
    {
        AndroidSDKHelper::sharedHelper()->setMusicEnabled(b);
    }
    void Java_org_cocos2dx_cpp_MMIAPListener_validateOrderMM(JNIEnv* env, jobject thiz, jstring paycode, jstring orderID, jstring tradeID, jint orderType)
    {
    const char *pPayCode = env->GetStringUTFChars(paycode, 0);
    const char *pOrderID = env->GetStringUTFChars(orderID, 0);
    const char *pTradeID = env->GetStringUTFChars(tradeID, 0);
    CCLog("调用 JNI  validateOrder(paycode,order,trade,type) : %s,%s,%s,%d", pPayCode, pOrderID, pTradeID, orderType);
    PurchaseManager::getInstance()->validateResult(pPayCode, pOrderID, pTradeID, orderType);
    }

    void Java_org_cocos2dx_cpp_AppActivity_setPhoneNumber(JNIEnv *env, jobject thiz, jstring number)
    {
        const char *phoneNumber = env->GetStringUTFChars(number, 0);

        AndroidSDKHelper::sharedHelper()->setPhoneNumber(phoneNumber);
    }

}