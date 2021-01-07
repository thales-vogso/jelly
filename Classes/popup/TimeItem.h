/****************************************************************************
*	@       	       
*	@desc	时间道具ui
*	@date	2014-11-7
*	@author	120102
*	@       	       
*	@file	popup/TimeItem.h
*	@modify	2014-11-12 by 120101
******************************************************************************/
#ifndef __POPUP_TimeItem_H__
#define  __POPUP_TimeItem_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/Game.h"
#include "data/Item.h"
#include "popup/Fail.h"

namespace popup{
	class TimeItem :public PopBase
	{

	public:
		/*
		*  初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(TimeItem);
		/*  时间按钮  */
		void clickTime(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/time.csb";
		const std::string TIME = "time";
		const std::string FAIL = "fail";
		const std::string GOLDPANEL = "gold";
		const std::string TEXTLABEL = "Label_15";
		const std::string GOLDIMAGE = "Image_17";
		const std::string GOLDTEXT = "Label_18";
		const std::string LABELTEXT = "Image_13";
		const std::string TIMELABEL = "Label_14";
		const std::string LINELABEL = "Image_10";
		const std::string GUIDELABEL = "guidetext";
		
		/*  获取的ui  */
		cocos2d::ui::Widget* _panel;

		/**
		*	失败按钮
		*/
		static const std::string FAILGAME;
		/**
		*	时间道具 按钮
		*/
		static const std::string TIMEPLUS;
		~TimeItem();
		/*  失败按钮   */
		void clickFail(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		* 关闭
		*/
		void closePop() override;
		/*  金币的ui  */
		cocos2d::ui::Widget* _gold;
		cocos2d::ui::Widget* _gold_image;
		cocos2d::ui::Widget* _gold_text;
		/*  失败的ui  */
		cocos2d::ui::Widget*_fail;
		cocos2d::ui::Widget*_text;

		void onEnter();
		/*  是否是第一次玩游戏  */
		bool _isFirst;
		/*
		*	时间的ui
		*/
		cocos2d::ui::Widget*_time;
		cocos2d::ui::Widget*_labeltext;
		cocos2d::ui::Widget*_timelabel;
		cocos2d::ui::Widget*_linelabel;
		cocos2d::ui::Widget*_guidelabel;
	private:


	};
}
#endif