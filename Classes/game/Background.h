/****************************************************************************
*	@       	       
*	@desc	背景类
*	@date	2014-11-17
*	@author	120102
*	@       	       
*	@file	game/Background.h
*	@modify	null
******************************************************************************/
#ifndef __BACKGROUND_H__
#define  __BACKGROUND_H__

#include "cocos2d.h"
#include "plat.h"
class Background :public cocos2d::Layer
{
public:
	/*
	*	初始化
	*/
	bool init();
	//创造背景类的对象..
	CREATE_FUNC(Background);
	/*
	*	背景的状态，正常，炸弹，雷电，闪光 ,狂暴,主界面 ,新手引导
	*/
	enum State
	{
		NORMAL = 0,
		BOMB,
		SHOCK,
		SHING,
		RAGE, 
		MAIN,
		LOADING,
		BLACK,
		NEWBIE
	};
	void changeBgState(State=Background::NORMAL);
	cocos2d::Sprite* _bg;
	/*
	*	重新随机新的背景
	*/
	void randBg();

private:
	
	char _pis[20];



};
#endif
