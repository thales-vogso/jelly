/****************************************************************************
*	@       	       
*	@desc	退出当前游戏界面
*	@date	2014-11-10
*	@author	120102
*	@       	       
*	@file	popup/QuitGame.h
*	@modify	2014-11-11 by 120101
******************************************************************************/
#ifndef __POPUP_QUITGAME_H__
#define  __POPUP_QUITGAME_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

namespace popup{
	class QuitGame :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(QuitGame);
		/**
		*	确认点击
		*/
		void yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	取消点击
		*/
		void noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*  暂停事件  触发暂停界面  */
		static const std::string FUNCPAUSE;
		/*  记录返回主菜单的方式，不同于游戏中直接返回主菜单  */
		static const std::string ENDGAMETOMAIN;
		/*
		*  关闭
		*/
		void closePop() override;

	private:

		/**
		*	cocostuido创建的退出游戏的界面
		*/
		const std::string PANEL_NAME = "csb/popup/quitgame.csb";

		const std::string YES = "yes";
		const std::string NO = "no";

		/**
		*	面板
		*/
		cocos2d::ui::Widget* _panel;

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