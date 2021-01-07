/****************************************************************************
*	@       	       
*	@desc	开始界面
*	@date	2014-10-29
*	@author	120101
*	@       	       
*	@file	gateway/Gateway.h
*	@modify	null
******************************************************************************/
#ifndef __GATEWAY_H__
#define __GATEWAY_H__

#include "cocos2d.h"
#include "main/Setting.h"
#include "guide/Guide.h"
#include "game/Game.h"
#include "data/Game.h"
#include "popup/LoadSave.h"
#include "game/UmGameUI.h"
#include "game/ItemUI.h"
#include "game/GoldUI.h"
#include "loading/TinyLoadingPop.h"
#include "popup/PopUp.h"
#include "guide/TeachGame.h"
#include "guide/TeachEntity.h"
#include "plat.h"
#include "popup/EndlessUnlock.h"
#include "game/SpecialOfferLayer.h"
#include "game/PaymentLayer.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
void shareCallback(int platform, int stCode, std::string& errorMsg);
class Gateway : public cocos2d::Layer
{
public:
	/*
	*  析构函数
	*/
	~Gateway();
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
	CREATE_FUNC(Gateway);
	/*
	*  移入屏幕效果
	*/
	void moveIn();
	/*
	*  移出屏幕效果
	*/
	void moveOut();
	/*  无尽模式事件  */
	static const std::string ENDLESSGAME;
    void showEndlessLayer();
private:
	/**
	*	存档点击
	*/
	void saveClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	*	设置点击
	*/
	void settingBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
    /**
     *	更多点击
     */
    void moreButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);

    
	/**
	*	帮助点击
	*/
	void helpBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
    void infoBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);

	/*
	*  开始游戏点击
	*/
	void startBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*  无尽模式点击
	*/
	void endlessBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
    /**
     *  礼包按钮点击
     *
     *  @param ref
     *  @param e
     */
    void libaoBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);

//#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//    /*
//    *   获取和显示广告
//    */
//    void menuBannerCallback();
//    /*
//    *   隐藏广告
//    */
//    void hiddenBannerCallback();
//#endif
	//----------------------------
	/**
	*	获取cocostuido创造的ui
	*/
	Node* getPanel();
	/**
	*	从面板获取元素
	*/
	Node* getWidgetFromPanel(std::string name);
	cocos2d::ui::Widget* getWidgetFromPanel(int id);
	/**
	*	通过枚举获取按纽名称
	*/
	std::string getWidgetNameByEnum(int id);
	/**
	*	通过枚举获取按纽元素名称
	*/
	std::string getWidgetElementByEnum(int id);
	/**
	*	新手引导步骤
	*/
	int _guide;
	/**
	*	cocostuido创造的ui
	*/
	Node* _panel;
	/**
	*	cocostuido创造的ui的名字
	*/
	std::string PANEL_NAME = "csb/main/gateway.csb";
	/**
	*	进入延迟延迟系数
	*/
	const float MOVEINDELAYTIME = 0.6f;
	/**
	*	延迟系数
	*/
	const float DELAYTIME = 0.2f;
	/**
	*	经过时间
	*/
	const float DELTATIME = 0.5f;
	/**
	*	按纽名字
	*/
	enum WidgetName{
		BUTTON_START,
		BUTTON_ENDLESS,
		BUTTON_SETTING,
		BUTTON_HELP,
        BUTTON_MOREGAME,
        BUTTON_INFO,
        BUTTON_LIBAO,
		TEXT_START,
		TEXT_ENDLESS,
		TEXT_SAVE,
		TEXT_STARTON,
		TEXT_GOON,
		TEXT_GUIDE,
        IMAGE_41,
        BLACK
	};

	/*  道具ui  */
	ItemUI*__itemUI;
	/*  金币ui  */
	GoldUI*__goldUI;
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _goldUIListener;
	cocos2d::EventListenerCustom* _itemUIListener;
	cocos2d::EventListenerCustom* _tinyLoadinglistener;
    
//    void testMenuclick(cocos2d::Ref *item);
    
    std::string DISCOUNTENDLESS_ISOVER = "Discount_WithEndless_IsOver";
    std::string OVER_TIMES = "over_times";

    void showDiscountWithEndless();
    void showSpecialOffer();

    void setTimeWithStr(int number);
    int m_nUpTime;
    void updateTime(float dt);
    void setTitleDisPlay(float dt);
};

#endif // #define __GATEWAY_H__

