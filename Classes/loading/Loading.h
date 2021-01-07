/****************************************************************************
*	@       	       
*	@desc	读取界面
*	@date	2014-11-17
*	@author	120101
*	@       	       
*	@file	loading/Loading.h
*	@modify	null
******************************************************************************/
#ifndef __LOADING_H__
#define __LOADING_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

#include "Loader.h"
#include "main/Main.h"
#include "plat.h"

class Loading : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Loading);
private:
	/*
	*  Panel名称
	*/
	const std::string PANEL = "loading";
	/**
	*	cocostuido创造的ui
	*/
	cocos2d::ui::Widget* _panel;
	/**
	*	进出时间
	*/
	const float DELAYTIME = 0.2f;
};

#endif // #define __GATEWAY_H__

