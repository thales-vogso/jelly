/****************************************************************************
*	@       	       
*	@desc	跳过界面
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	popup/Skip.h
*	@modify	by jinzhen 2014-12-16
******************************************************************************/
#ifndef __SKIP_H__
#define  __SKIP_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "popup/PopBase.h"
#include "plat.h"
namespace popup
{
	class Skip :public  PopBase
	{
	public:

		/*
		*  初始化
		*/
		bool init(bool);
		/*
		*  create  方法  默认是false  是不是教学关卡里面
		*/
		static Skip*create(bool=false);
		/*
		* 关闭
		*/
		void closePop() override;
		/*
		*	是否是从教学关卡中暂停
		*/
		bool _isTeachLevel;
        //设置监听
        cocos2d::EventListenerCustom *_listener;
        ~Skip();
        bool m_bNotPushToColse;

	private:
		/**
		*	确认点击
		*/
		void yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
		/**
		*	取消点击
		*/
		void noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
#ifdef LONGBAO
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/guide/skip.csb";
#endif
#ifdef CANDY
		/**
		*	cocostuido创造的暂停界面ui的名字
		*/
		const std::string PANEL_NAME = "csb/guide/skip.csb";
#endif
		/**
		*	金币窗口
		*/
		cocos2d::ui::Widget* _savePanel;

		const std::string SAVEPANEL = "replay";
		const std::string YES = "yes";
		const std::string NO = "no";
		/**
		*	进出时间
		*/
		const float DELTATIME = 0.5f;
		/**
		*	存档花费
		*/
		const int SAVECOST = 5;
	};
}
#endif