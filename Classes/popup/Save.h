/****************************************************************************
*	@       	       
*	@desc	存档界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	popup/Save.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_SAVE_H__
#define  __POPUP_SAVE_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "data/Game.h"
#include "popup/EmptySave.h"
#include "popup/CoverSave.h"
#include "popup/PopBase.h"

namespace popup{
	class Save :public PopBase
	{

	public:
		/*
		* 初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(Save);
		/*
		* 关闭
		*/
		void closePop() override;
	private:
		/**
		*	刷新存档条目
		*/
		void refreshSave();
		/**
		*	回到主菜单点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	商品点击
		*/
		void goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/save.csb";

		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;
		/**
		*	滚动层
		*/
		cocos2d::ui::ListView* _listView;
		/**
		*	场景
		*/
		Node* _panel;

		const std::string CLOSE = "close";
		const std::string BAR = "bar";
		const std::string BARLIST = "barlist";
		const std::string EMPTYBAR = "emptybar";
		const std::string SCROLLVIEW = "ScrollView";
		const std::string SAVEPANEL = "savePanel";
		const std::string SCORE_TEXT = "score";
		const std::string LEVEL_TEXT = "level";

		cocos2d::Vec2 startPos = cocos2d::Vec2(74, 548);

		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
	};
}
#endif