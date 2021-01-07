/****************************************************************************
*	@       	       
*	@desc	弹窗层
*	@date	2014-11-11
*	@author	120101
*	@       	       
*	@file	popup/PopUp.h
*	@modify	null
******************************************************************************/
#ifndef __POPUP_POPUP_H__
#define  __POPUP_POPUP_H__

#include "cocos2d.h"

#include "popup/PopBase.h"

namespace popup{
	class PopUp :public cocos2d::Layer
	{

	public:
		/*
		*  create  方法
		*/
		CREATE_FUNC(PopUp);
		/*
		* 初始化
		*/
		bool init();
		/*
		* 关闭最上层弹窗
		*/
		bool closeTopPop();
		/*
		* 加入最上层弹窗
		*/
		void addTopPop(PopBase* popBase);
		/*
		* 弹出最外层
		*/
		void popBack();
		/*
		*	判断最上层的的数量
		*/
		int popNum();
	private:
		/*
		* 存储容器
		*/
		std::vector<PopBase*> __PopBaseVector;
		/**
		*	自身
		*/
		static PopUp* _instance;
		/*
		* 回调
		*/
		void callBack(float dt);
	};
}
#endif