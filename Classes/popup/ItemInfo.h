/****************************************************************************
*	@       	2015,青岛UMGame
*	@desc	道具使用说明
*	@date	2015-1-12
*	@author	120102
*	@       	       
*	@file	popup/ItemInfo.h
*	@modify	null
******************************************************************************/
#ifndef _ITEM_INFO_H__
#define  _ITEM_INFO_H__
#include "cocos2d.h"
#include "data/User.h"
#include "popup/PopUp.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "main/Main.h"
namespace  popup
{

	class ItemInfo :public PopBase
	{

	public:
		/*
		*	道具介绍的种类
		*/
		enum ItemType
		{
			BOMB,
			SHOCK,
			RAGE
		};
		/*
		*	静态的create 方法
		*/
		static ItemInfo* create(ItemType type);
		
		/*
		* 初始化
		*/
		bool init(ItemType type);
		/*
		*	关闭
		*/
		void closePop() override;

		/*
		*	获取道具介绍的类型
		*/
		ItemType getType();
		/*
		*	返回游戏的事件。。
		*/
		static const std::string BACK_GAME;
		/*
		*	使用道具并返回游戏的事件。。
		*/
		static const std::string USEITEM_BACK_GAME;
	private:
		/*
		*	道具的类型
		*/
		ItemType _type;
		/*
		*	根据道具的类型确定具体的UI
		*/
		void setItemUI(ItemType type);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/

		const std::string PANEL_NAME = "csb/popup/goldshopcu.csb";

		/**
		*	回到主菜单点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	使用道具和使用按钮
		*/
		void buyAndUse(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	点击是否再次显示弹窗
		*/
		void showPopup(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/*
		*	析构函数
		*/
		~ItemInfo();
		/**
		*	自定义监听
		*/
		cocos2d::EventListenerCustom* _goldlistener;
		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _goldPanel;
		/**
		*	左上金币显示窗口
		*/
		cocos2d::ui::Widget* _goldTip;
		/*
		*	道具窗口
		*/
		cocos2d::ui::Widget*_itemLayer;
		const std::string CLOSE = "close";
		/*
		*	道具金币数量的UI
		*/
		const std::string ITEMGOLDNUM = "goldnum";
		/*
		*	道具图标的UI
		*/
		const std::string ITEMPIC = "item";
		/*
		*	道具详细介绍的UI
		*/
		const std::string ITEMMOREINFO = "itemmoreinfo";
		/*
		*	道具的名称的UI
		*/
		const std::string ITEMNAME = "iteminfo";
		/*
		*	是否显示弹窗的按钮UI
		*/
		const std::string SHOW = "show";
		/*
		*	购买和使用的UI
		*/
		const std::string BUGANDUSE = "buganduse";
		/*
		*	如果是炸弹的话   购买和使用中间的文字应该是确定
		*/
		const std::string USE = "use";

		const std::string GOLDPANEL = "goldPanel";
		const std::string TIP = "tip";
		const std::string ITEMLAYER = "itemlayer";

		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/*
		*	道具的名字
		*/
		cocos2d::ui::Widget* _itemname;
		/**
		*	道具的图标
		*/
		cocos2d::ui::Widget* _itempic;
		/*
		*	道具的金币数量
		*/
		cocos2d::ui::Widget*_itemgoldnum;
		/*
		*	道具的具体简介
		*/
		cocos2d::ui::Widget*_itemmoreinfo;
		/*
		*	是否显示的按钮
		*/
		cocos2d::ui::Widget*_showmenu;
		/*
		*	是否显示按钮的对号
		*/
		cocos2d::ui::Widget*_showmenuon;
		/*
		*	购买并使用的按钮
		*/
		cocos2d::ui::Widget*_buyanduse;
		/*
		*	购买并使用的按钮的文字
		*/
		cocos2d::ui::Widget*_buganduseinfo;

		/**
		*	事件分发器
		*/
		cocos2d::EventDispatcher* _evt;

		
	};
}


#endif