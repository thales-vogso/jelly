/****************************************************************************
*	@       	       
*	@desc	道具ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/ItemUI.h
*	@modify	null
******************************************************************************/
#ifndef __ItemUI_H__
#define  __ItemUI_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/Game.h"
#include "data/Item.h"
#include "cache/music.h"
#include "data/User.h"
#include "cocos-ext.h" 
#include "data/Item.h"
#include "plat.h"
class ItemUI :public cocos2d::Layer
{

public:
	/*
	*	析构函数
	*/
	~ItemUI();
	/**
	*  UI的不同显示
	*/
	enum Type
	{
		MAINUI,
		GAMEUI
	};
	/**
	*  UI的不同显示
	*/
	enum Icon
	{
		shock = 6,
		bomb,
		magic		
	};
	/*
	*  初始化
	*/

	bool init(Type);
	/*
	*  create  方法
	*/
	static ItemUI* create(Type);
	/*
	*	添加按钮的点击
	*/
	void clickPlus(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*	改变道具的数量
	*/
	void ItemChange(cocos2d::EventCustom* e);
	/*  点击炸弹  */
	void clickBomb(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*  点击魔瓶  */
	void clickMagic(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*  点击雷电  */
	void clickShock(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*  根据道具的数量  */
	void setLength(int num, std::string str);
	/**
	*	cocostuido创造的暂停界面ui的名字
	*/
	std::string PANEL_NAME = "csb/game/item.csb";
	const std::string BG1 = "bg1";
	const std::string ITEMBOMB = "bomb";
	const std::string ITEMMAGIC = "magic";
	const std::string ITESHOCK = "shock";
	const std::string PLUSITEM = "plus";
	const std::string TEXT = "text1";
	const std::string TEXT2 = "text2";
	const std::string TEXT3 = "text3";
	const std::string TEXT4 = "text4";
	const std::string SHOCKBG = "shockbg";
	const std::string MAGICBG = "magicbg";
	const std::string SHOCKUI = "shock";
	const std::string BOMBUI = "bomb";
	const std::string MAGICUI = "magic";
	const std::string MAGICGRAY = "magicgray";
	/*  获取的ui  */
	cocos2d::ui::Widget* _panel;
	/*  炸弹ui  */
	cocos2d::Node* _bomb;
	/*  魔瓶ui  */
	cocos2d::Node* _magic;
	/*  雷电ui  */
	cocos2d::Node* _shock;


	cocos2d::ui::Widget*_bombmenu;
	cocos2d::ui::Widget*_magicmenu;
	cocos2d::ui::Widget*_shockmenu;
	cocos2d::ui::Widget* _plusmenu;
	cocos2d::ui::Widget*_ragegray;
	cocos2d::ui::Widget*_bg;
	cocos2d::ui::Widget*_text;
	cocos2d::ui::Widget*_text4;
	cocos2d::Node*_shockbg;
	cocos2d::Node*_magicbg;
	cocos2d::Node*_bombui;
	cocos2d::Node*_magicui;
	cocos2d::Node*_shockui;
	static const std::string ITEM_CLICK;
	//发送给主场景的点击事件..
	static const std::string MAINITEMUI;
	//发送给游戏场景的点击事件..
	static const std::string GAMEITEMUI;
	/*  根据道具的位置改变背景的大小  */
	void setBgSize();
	/**
	*	添加事件
	*/
	void addListener(const std::string &eventName, const std::function<void(cocos2d::EventCustom*)>& callback);
	/*
	*	道具使用倒计时
	*	@param time 倒计时 item 哪种道具开始倒计时
	*/
	void beginCountDown(int time, cocos2d::Node*item);
	/**
	*	事件分发器
	*/
	cocos2d::EventDispatcher* _evt;
	/**
	*	设置灰色
	*/

	void setGray();
	/**
	*	获得位置
	*/
	cocos2d::Vec2 getPos(int type);

	/**
	*	道具震动事件
	*/
	static const std::string ITEMSHOCK;
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _listener;
private:

};
#endif