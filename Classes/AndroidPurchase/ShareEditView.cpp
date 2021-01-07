//
//  ShareEditView.cpp
//  PocketFishing
//
//
#include "cocos2d.h"
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)

#include "ShareEditView.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
#endif

#define SHARE_MAX_LENGTH 120

using namespace cocos2d;
ShareEditLayer* ShareEditLayer::create(const char *defaultText)
{
    ShareEditLayer* layer = new ShareEditLayer();
    if (layer && layer->init(defaultText)) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        layer = NULL;
        return NULL;
    }
}

bool ShareEditLayer::init(const char *defaultText)
{
    if (!CCLayer::init()) {
        return false;
    }
    
    m_MaxCount = 0;
    m_text = defaultText;
    

    
        
    return true;
}

void ShareEditLayer::setDelegate(ShareEditLayerDelegate *pDelegate)
{
    m_pDelegate = pDelegate;
}

bool ShareEditLayer::shouldEditChange(int allcount)
{
    // android 无需实现
    return true;
}

void ShareEditLayer::editDidChange(int count)
{
    // android 无需实现
}

void ShareEditLayer::editDidEnd(const char *text)
{
    m_text = text;
}

static void editTextDialogCallback(const char* text, void* context)
{
    ShareEditLayer* thiz = (ShareEditLayer *)context;
    thiz->editDidEnd(text);
    // auto end, and remove self
    thiz->endEdit();
    CCLOG("editTextDialogCallback = %s",text);
}

#pragma mark - 触摸


void ShareEditLayer::beginEdit()
{
    // 调用 android 输入
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    showEditTextDialogJNI(NULL,
                          m_text.c_str(),
                          0,
                          1,
                          2,
                          m_MaxCount,
                          editTextDialogCallback,
                          (void *)this);
#endif

}

void ShareEditLayer::endEdit()
{
    if (m_pDelegate) {
        m_pDelegate->shareEditLayerDidEditEnd(m_text.c_str());
    }
    this->removeFromParentAndCleanup(true);
}

//#endif
