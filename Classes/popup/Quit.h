/****************************************************************************
*	@       	       
*	@desc	退出确认界面
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	popup/Quit.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_QUIT_H__
#define  __POPUP_QUIT_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "popup/PopBase.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
namespace popup{
	class Quit :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(Quit);
		/*
		* 关闭
		*/
		void closePop() override;

		static const std::string MOVEIN;
		static const std::string MOVEOUT;
	private:
		/**
		*	确认点击
		*/
		void yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	取消点击
		*/
		void noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/quit.csb";

		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;

		const std::string SAVEPANEL = "replay";
		const std::string YES = "yes";
		const std::string NO = "no";
		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/**
		*	存档花费
		*/
		const int SAVECOST = 5;
	};
}
#endif