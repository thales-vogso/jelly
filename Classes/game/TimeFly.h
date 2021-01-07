/****************************************************************************
*	@       	       
*	@desc	加时间道具
*	@date	2014-12-29
*	@author	120101
*	@       	       
*	@file	game/timeFly.h
*	@modify	null
******************************************************************************/
#ifndef __TIMEFLY_H__
#define  __TIMEFLY_H__

#include "cocos2d.h"
#include "plat.h"

class TimeFly :public cocos2d::Layer
{

public:
	/*
	*  初始化
	*/

	bool init(int time);
	/*
	*  create  方法
	*/
	static TimeFly* create(int time);
	//加时间的事件。。。
	static const std::string TIMEPLUS;
private:


};
#endif