/****************************************************************************
*	@       	       
*	@desc	暂停和时间ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/TimeUI.h
*	@modify	null
******************************************************************************/
#ifndef __TimeUI_H__
#define  __TimeUI_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/Game.h"
#include "data/Item.h"

class TimeUI :public cocos2d::Layer
{

public:
	~TimeUI();
	/*
	*  初始化
	*/

	bool init();
	/*
	*  create  方法
	*/
	CREATE_FUNC(TimeUI);

	/*
	*	改变时间
	*/
	void TimeChange(cocos2d::EventCustom* e);

	/**
	*	cocostuido创造的暂停界面ui的名字
	*/
	const std::string PANEL_NAME = "csb/game/timeui.csb";
	const std::string PAUSES = "pausebtn";
	const std::string MINUTE = "minute";
	const std::string SECOND = "second";
	const std::string MINUTEZERO = "minutezero";
	const std::string SECONDZERO = "secondzero";
	const std::string ENDLESS = "endless";
	const std::string COLON = "colon";
	const std::string ADBLOCK = "adbutton";

	/*  暂停界面  */
	void clickPause(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*  更改时间
	*/
	void timeChange(cocos2d::EventCustom*e);

	/*  获取的ui  */
	cocos2d::ui::Widget* _panel;

	/*  无尽模式  默认不是  */
	void setEndless(bool =false);
	//发送给主场景的点击事件..
	static const std::string TIMEUISHOCK;
	//去除广告的UI。。
	cocos2d::ui::Widget*_adblockui;
private:


};
#endif