/****************************************************************************
*	@       	       
*	@desc	ios去广告的付费界面
*	@date	2015-01-16
*	@author	120102
*	@       	       
*	@file	popup/AdBlock.cpp
*	@modify	null
******************************************************************************/
#ifndef _AD_BLOCK_H__
#define _AD_BLOCK_H__
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

	class AdBlock :public PopBase
	{

	public:
		
		/*
		*	静态的create方法
		*/
		CREATE_FUNC(AdBlock);
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
		const std::string PANEL_NAME = "csb/popup/adoff.csb";
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
		~AdBlock();
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