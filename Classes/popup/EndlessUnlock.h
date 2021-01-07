/****************************************************************************
*	@       	2015,青岛UMGame
*	@desc	
*	@date	2015-01-21
*	@author	120102
*	@       	       
*	@file	popup/EndlessUnlock.h
*	@modify	null
******************************************************************************/
#ifndef _ENDLESS_UNLOCK_H__
#define _ENDLESS_UNLOCK_H__
#include "cocos2d.h"
#include "data/User.h"
#include "popup/PopUp.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "main/Main.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "Purchase/IOSiAPBridge.h"
#include "Purchase/IOSiAP.h"
#endif
namespace  popup
{

	class EndlessUnlock :public PopBase
	{

	public:
		/*
		*	静态的create方法
		*/
		CREATE_FUNC(EndlessUnlock);
		/*
		* 初始化
		*/
		bool init();
		/*
		*	关闭
		*/
		void closePop() override;
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/wujin.csb";
		/*
		*	去广告界面ui
		*/
		cocos2d::Node*_panel;
		/*
		*	关闭ui
		*/
		cocos2d::ui::Widget*_closeBtn;
		/*
		*	购买的的ui
		*/
		cocos2d::ui::Widget*_buylabel;
		/*
		*	恢复购买的ui
		*/
		cocos2d::ui::Widget*_recoverBton;

		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		~EndlessUnlock();
		static const std::string ENDLESSBUYSCUUESS;
        bool m_bIsDiscount;
        void setTimeWithStr(int number);
        void updateTime(float dt);
        void showDiscountWithEndless();

        int m_nUpTime;
        bool m_bNotPushToColse;

	private:

		/**
		*	关闭按钮的点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	购买的点击
		*/
		void buyClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	恢复购买的点击
		*/
		void recoverClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);



	};
}


#endif