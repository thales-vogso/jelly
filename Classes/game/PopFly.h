/****************************************************************************
*	@       	       
*	@desc	飞行泡泡
*	@date	2014-12-28
*	@author	120101
*	@       	       
*	@file	game/popFly.h
*	@modify	null
******************************************************************************/
#ifndef __POPFLY_H__
#define  __POPFLY_H__

#include "cocos2d.h"
#include "plat.h"

class PopFly :public cocos2d::Layer
{

public:
	/*
	*  初始化
	*/

	bool init(cocos2d::Vec2 from, cocos2d::Vec2 to, bool large = false);
	/*
	*  create  方法
	*/
	static PopFly* create(cocos2d::Vec2 from, cocos2d::Vec2 to,bool large = false);

private:


};
#endif