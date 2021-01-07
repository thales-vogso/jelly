//
//  ShareEditView.h
//  PocketFishing
//
//

#ifndef __PocketFishing__ShareEditLayer__
#define __PocketFishing__ShareEditLayer__


class ShareEditLayerDelegate
{
public:
    virtual void shareEditLayerDidEditEnd(const char *text) = 0;
    virtual void shareEditLayerDidEditBegin(const char *text){};

};

class MaskLayer;
class ShareEditLayer : public cocos2d::Layer {
public:
    static ShareEditLayer* create(const char* defaultText);
    bool init(const char* defaultText);
//    static ShareEditLayer* createLabel(cocos2d::CCRect frame);
//    bool initLabel(cocos2d::CCRect frame);
    void editDidBegin(const char* text);

    void editDidEnd(const char* text);
    bool shouldEditChange(int allcount);
    void editDidChange(int count);
    static void removeUIview();
    void setDelegate(ShareEditLayerDelegate *pDelegate);
    int m_MaxCount;
    int m_count;
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    void beginEdit();
    void endEdit();
//#endif
    
private:
    ShareEditLayerDelegate* m_pDelegate;
    
    


//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    std::string m_text;
//#endif
    
};

#endif
