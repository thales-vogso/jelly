/****************************************************************************
*	@       	       
*	@desc	新手教程暂停界面的ui
*	@date	2014-12-15
*	@author	120102
*	@       	       
*	@file	popup/TeachPause.h
*	@modify	null
******************************************************************************/
#ifndef __TEACH_PAUSE_H__
#define  __TEACH_PAUSE_H__
#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "popup/PopBase.h"
namespace popup
{
	class TeachPause :public PopBase
	{
	public:
		/*
		*	初始化
		*/
		bool init();
		/*
		*	静态的create 方法
		*/
		CREATE_FUNC(TeachPause);
	
		/*
		*	回到游戏按钮
		*/
		void clickReback(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	跳过教程
		*/
		void clickSkipTeach(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	重新开始
		*/
		void clickResume(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PAUSE_NAME = "csb/popup/teachpause.csb";
		/*
		*	继续游戏
		*/
		const std::string BACK_GAME = "backgame";
		/*
		*	跳过教程
		*/
		const std::string BACK_MENU = "Button_1";
		/*
		*	重新开始
		*/
		const std::string RESUME = "resume";

		/*
		* 关闭
		*/
		void closePop() override;
		/*
		*	返回游戏的事件
		*/
		static const std::string BACKGAME;
		/*
		*	重玩的事件
		*/
		static const std::string RESUMETEACH;
		/*
		*	跳过教程
		*/
		static const std::string SKIPTEACH;
	private:





	};
}


#endif