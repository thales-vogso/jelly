/****************************************************************************
*	@       	       
*	@desc	重玩确认界面
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	popup/Replay.cpp
*	@modify	null
******************************************************************************/
#ifndef __POPUP_REPLAY_H__
#define  __POPUP_REPLAY_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "data/Game.h"
#include "popup/PopBase.h"

namespace popup{
	class Replay :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(Replay);
		/*
		* 关闭
		*/
		void closePop() override;
		/**
		*	重新开始游戏
		*/
		static const std::string RESUMEGAME;
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
		const std::string PANEL_NAME = "csb/popup/replay.csb";

		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;

		const std::string SAVEPANEL = "replayPanel";
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