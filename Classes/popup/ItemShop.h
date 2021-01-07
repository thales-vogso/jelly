/****************************************************************************
*	@       	       
*	@desc	道具商店
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	shop/ItemShop.h
*	@modify	null
******************************************************************************/
#ifndef __ITEMSHOP_H__
#define  __ITEMSHOP_H__

#include "cocos2d.h"
#include "main/Main.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "data/Shop.h"
#include "data/Item.h"
#include "data/User.h"
#include "popup/PopBase.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
namespace popup
{
	class ItemShop :public PopBase
	{

	public:
		/*
		*  初始化
		*/
		bool init();
		/*
		*  create  方法
		*/
		CREATE_FUNC(ItemShop);
		/*  继续游戏的事件  */
		static const std::string GAMERESUME;
		/*  析构函数  */
		~ItemShop();
		/*
		*  关闭
		*/
		void closePop() override;
	private:
		/**
		*	切换到金币商店
		*/
		void changeGoldShop(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	回到主菜单点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	加号点击
		*/
		void addClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	减号点击
		*/
		void minClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	商品点击
		*/
		void goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
#ifdef CANDY
		const std::string PANEL_NAME = "csb/popup/itemshop.csb";
#endif
#ifdef LONGBAO
		const std::string PANEL_NAME = "csb/longbao/ui/itemshop.csb";
#endif
		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _itemPanel;
		/**
		*	左上金币显示窗口
		*/
		cocos2d::ui::Widget* _itemTip;

		const std::string CLOSE = "close";
		const std::string BAR = "bar";
		const std::string ITEMPANEL = "itemPanel";
		const std::string TIP = "tip";
		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/*
		*	更新用户金币数
		*/
		void goldChange(cocos2d::EventCustom* e);
		/*
		*	更新物品底图
		*/
		void refreshItemBar();
		/**
		*	自定义监听
		*/
		cocos2d::EventListenerCustom* _goldlistener;
	};
}
#endif