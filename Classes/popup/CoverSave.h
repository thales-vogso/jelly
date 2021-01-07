/****************************************************************************
*	@       	       
*	@desc	覆盖存档确认界面
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	popup/CoverSave.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_COVERSAVE_H__
#define  __POPUP_COVERSAVE_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "data/Game.h"
#include "popup/PopBase.h"

namespace popup{
	class CoverSave :public PopBase
	{

	public:
		/*
		*  初始化
		*/
		bool init(int id);
		/*
		*  create  方法
		*/
		static CoverSave* create(int id);
		/*
		*  关闭
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
		const std::string PANEL_NAME = "csb/popup/coversave.csb";
		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;

		const std::string SAVEPANEL = "coverPanel";
		const std::string YES = "yes";
		const std::string NO = "no";

		const std::string BAR = "bar";
		const std::string SCORE_TEXT = "score";
		const std::string LEVEL_TEXT = "level";
		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/**
		*	存档花费
		*/
		const int SAVECOST = 5;
		/**
		*	覆盖的存档id
		*/
		int _ID;
	};
}
#endif