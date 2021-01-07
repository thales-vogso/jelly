/****************************************************************************
*	@       	       
*	@desc	空存档确认界面
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	popup/EmptySave.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_EMPTYSAVE_H__
#define  __POPUP_EMPTYSAVE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "data/Game.h"
#include "popup/GoldShop.h"
#include "popup/PopBase.h"

namespace popup{
	class EmptySave :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(EmptySave);
		/*
		* 关闭
		*/
		void closePop() override;

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
		const std::string PANEL_NAME = "csb/popup/emptysave.csb";

		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;

		const std::string SAVEPANEL = "emptyPanel";
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