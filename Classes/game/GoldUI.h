/****************************************************************************
*	@       	       
*	@desc	金币ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/GoldUI.h
*	@modify	null
******************************************************************************/
#ifndef __GOLDUI_H__
#define  __GOLDUI_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cache/music.h"
#include "data/User.h"
//#include "data/Game.h"
#include "plat.h"

class GoldUI :public cocos2d::Layer
{

public:
	~GoldUI();
	/*
	*  初始化
	*/
	bool init();
	/*
	*  create  方法
	*/
	CREATE_FUNC(GoldUI);
	/*
	*	添加按钮的点击
	*/
	void clickPlus(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*	改变金币的数量
	*/
	void changeGold(int num);
	/*
	*	金币增加
	*/
	void goldPlus(int num);
	/**
	*	cocostuido创造的暂停界面ui的名字
	*/
	std::string PANEL_NAME = "csb/game/gold.csb";
	const std::string GOLDMENU = "goldbtn";
	const std::string GOLDNUMS = "goldnum";
	const std::string GOLDMENUS = "goldmenu";
	/*
	*	金币数量
	*/
	cocos2d::ui::Widget* _num;

	//发送给主场景的点击事件..
	static const std::string MAINGOLDUI;
	//发送给游戏场景的点击事件..
	static const std::string GAMEGOLDUI;
	//金币增加事件..
	static const std::string GOLDPLUS;
	//金币震动事件..
	static const std::string GOLDSHOCK;
	/*
	*	金币商店的按钮
	*/
	cocos2d::ui::Widget*_plus;
	/*
	*	金币商店的按钮
	*/
	cocos2d::ui::Widget*_goldlabel;
	/*
	*	监听器
	*/
	cocos2d::EventListenerCustom* _goldChangeListener;
	cocos2d::EventListenerCustom* _goldPlusListener;
	cocos2d::EventListenerCustom* _goldShockListener;
	/*
	*	获得金币图标的位置
	*/
	cocos2d::Vec2 getIconPos();
	/*
	*	金币UI
	*/
	cocos2d::Node*_panel;
private:

};
#endif