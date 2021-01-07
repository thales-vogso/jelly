/****************************************************************************
*	@       	       
*	@desc	弹窗基类
*	@date	2014-11-11
*	@author	120101
*	@       	       
*	@file	shop/PopBase.h
*	@modify	null
******************************************************************************/
#ifndef __POPBASE_H__
#define  __POPBASE_H__

#include "cocos2d.h"

namespace popup{
	class PopBase :public cocos2d::Layer
	{

	public:
		bool moving = true;
		/*
		* 关闭
		*/
		virtual void closePop() = 0;
	};
}
#endif