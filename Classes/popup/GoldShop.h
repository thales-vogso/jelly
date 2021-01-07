/****************************************************************************
*	@       	       
*	@desc	金币商店
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	shop/GoldShop.h
*	@modify	null
******************************************************************************/
#ifndef __GOLDSHOP_H__
#define  __GOLDSHOP_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
#include "data/Shop.h"
#include "data/Item.h"
#include "data/User.h"
#include "popup/PopBase.h"
#include "popup/HintInfo.h"
namespace popup{
	class GoldShop :public PopBase
	{

	public:		
		static GoldShop* create(bool libao = false);
		/*
		* 初始化
		*/
		bool init();
		/*  继续游戏的事件  */
		static const std::string GAMESUME;
		/*  析构函数  */
		~GoldShop();
		/*
		*  关闭
		*/
		void closePop() override;

	private:
		/**
		*	是否是礼包
		*/
		bool _blibao;
		/**
		*	礼包层
		*/
		cocos2d::ui::Widget* _libao;
		/**
		*	商品层
		*/
		cocos2d::ui::Widget* _scrollView;
		/**
		*	回到主菜单点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	商品点击
		*/
		void goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/goldshop.csb";
		/**
		*	自定义监听
		*/
		cocos2d::EventListenerCustom* _goldlistener;
		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _goldPanel;
		/**
		*	左上金币显示窗口
		*/
		cocos2d::ui::Widget* _goldTip;

		const std::string CLOSE = "close";
		const std::string BAR = "bar";
		const std::string SCROLLVIEW = "ScrollView";
		const std::string GOLDPANEL = "goldPanel";
		const std::string TIP = "tip";

		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/**
		*	金币飞行
		*/
		void coinFly(cocos2d::ui::Widget* ref);
		
	};
}
#endif