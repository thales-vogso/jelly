LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libcocos2dcpp

MY_CPP_LIST := $(wildcard $(LOCAL_PATH)/hellocpp/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/db/*.c)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/db/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/Cocos2dx/Android/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/Cocos2dx/ShareButton/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/Cocos2dx/Common/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/data/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/cache/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/guide/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/main/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/game/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/popup/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/loading/*.cpp)
MY_CPP_LIST += $(wildcard $(LOCAL_PATH)/../../Classes/AndroidPurchase/*.cpp)

LOCAL_SRC_FILES := $(MY_CPP_LIST:$(LOCAL_PATH)/%=%)

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

LOCAL_STATIC_LIBRARIES := cocos2dx_static
LOCAL_SHARED_LIBRARIES := mobclickcpp_shared
include $(BUILD_SHARED_LIBRARY)

$(call import-module,./prebuilt-mk)
#$(call import-module,cocos2dx)
$(call import-module,libmobclickcpp)