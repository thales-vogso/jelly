/****************************************************************************
*	@       	       
*	@desc	爱游戏的关于界面
*	@date	2015-03-30
*	@author	120102
*	@       	       
*	@file	popup/Info.h
*	@modify	null
******************************************************************************/
#ifndef _INFO_LAYER_H_
#define _INFO_LAYER_H_
#include "cocos2d.h"
#include "data/User.h"
#include "popup/PopUp.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "main/Main.h"
namespace  popup
{
	class Info :public PopBase
	{
	public:
		/*
		*	静态的create方法
		*/
		CREATE_FUNC(Info);
		/*
		* 初始化
		*/
		bool init();
		/*
		*	关闭
		*/
		void closePop() override;
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/popup/info.csb";
		/*
		*	去广告界面ui
		*/
		cocos2d::Node*_panel;
		/*
		*	关闭ui
		*/
		cocos2d::ui::Widget*_closeBtn;
		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
	private:
		/**
		*	关闭按钮的点击
		*/
		void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	};
}
#endif