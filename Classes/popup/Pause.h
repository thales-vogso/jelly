/****************************************************************************
*	@       	       
*	@desc	游戏暂停界面
*	@date	2014-10-22
*	@author	120102
*	@       	       
*	@file	popup/Pause.h
*	@modify	2014-11-12 by 120101
******************************************************************************/
#ifndef __POPUP_PAUSE_H__
#define  __POPUP_PAUSE_H__
#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "popup/PopBase.h"

namespace popup{
	class Pause :public PopBase
	{

	public:
		/*
		*  初始化
		*/
		bool init(bool);
		/*
		*  create  方法
		*/
		static Pause* create(bool = false);
		/*
		*  重新开始按钮
		*/
		void clickGiveup(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		 * 回到游戏按钮
		 */
		void clickReback(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		 *	返回主界面按钮
		 */
		void clickMainMenu(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	重新开始无尽模式
		*/
		void clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PAUSE_NAME = "csb/popup/pause.csb";

		const std::string BACK_GAME = "backgame";
		const std::string BACK_MENU = "backmenu";
		const std::string RESUME = "resume";
		const std::string GIVEUPGAME = "giveup";
		const std::string RESUMELABEL = "resumelabel";
		const std::string GIVEUPLABEL = "giveuplabel";
		static const std::string GIVEUP;
		/*
		*	返回到游戏中
		*/
		static const std::string BACK_YOUXI;
		/*
		*	重新开始无尽模式
		*/
		static const std::string RESUMEENDLESS;

		/*
		* 关闭
		*/
		void closePop() override;

	private:
	
	};
}
#endif