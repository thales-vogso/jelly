/****************************************************************************
*	@       	       
*	@desc	游戏胜利界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	popup/Success.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_SUCCESS_H__
#define  __POPUP_SUCCESS_H__
#include "cocos2d.h"
#include "main/Main.h"
#include "popup/Save.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "game/Game.h"
#include "data/Game.h"
#include "popup/Replay.h"
#include "popup/PopBase.h"

namespace popup{
	class Success :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(Success);
		/*
		*  重新开始按钮
		*/
		void clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		 * 下一关按钮
		 */
		void clickReback(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		 *	存档按钮
		 */
		void clickSave(Ref* ref, cocos2d::ui::Widget::TouchEventType e);

		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/success.csb";

		const std::string SUCCESS = "success";
		const std::string NEXTBTN = "nextBtn";
		const std::string SAVEBTN = "saveBtn";
		const std::string REPLAYBTN = "replayBtn";


		/**
		*	下一关事件
		*/
		static const std::string NEXTLEVEL;
		/**
		*	重新开始游戏
		*/
		static const std::string RESUMEGAME;
		/*
		*  关闭
		*/
		void closePop() override;

	private:

	};
}
#endif