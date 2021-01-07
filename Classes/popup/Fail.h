/****************************************************************************
*	@       	       
*	@desc	游戏失败界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	popup/Fail.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_FAILPOP_H__
#define  __POPUP_FAILPOP_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "cache/Music.h"
#include "popup/GoldShop.h"
#include "popup/PopBase.h"

namespace popup{
	class Fail :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(Fail);
		/*
		*  重新开始按钮
		*/
		void clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		 *	返回主界面按钮
		 */
		void clickMainMenu(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/fail.csb";

		const std::string FAIL = "fail";
		const std::string REPLAYBTN = "replayBtn";
		const std::string CLOSEBTN = "closeBtn";
		const std::string GOLDPANEL = "Panel_26";
		const std::string RESUMELABEL = "Text_1";

		static const std::string RESUMEGAME;
		static const std::string ENDGAMETOMAIN;
		/*
		* 关闭
		*/
		void closePop() override;
		/*  金币的ui  */
		cocos2d::Node*_goldpanel;
		void onEnter();
		/*
		*	关闭ui
		*/
		cocos2d::ui::Widget*_closeBtn;
		/*
		*	引导的ui
		*/
		cocos2d::ui::Widget*_guidelabel;
		/*
		*	重新挑战的ui
		*/
		cocos2d::ui::Widget*_replayBton;
		/*
		*	重新挑战的引导ui
		*/
		cocos2d::ui::Widget*_replayBtonCopy;
		/*
		*	线的ui
		*/
		cocos2d::ui::Widget*_line;
	private:


	};
}
#endif