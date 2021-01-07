/****************************************************************************
*	@       	       
*	@desc	游戏开始的Logo
*	@date	2015-03-23
*	@author	120102
*	@       	       
*	@file	loading/Logo.h
*	@modify	null
******************************************************************************/
#include "cocos2d.h"
#ifndef _LOGO_H__
#define _LOGO_H__
#include "loading/Loading.h"
class Logo : public cocos2d::LayerColor
{

public: 
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Logo);

private:

};
#endif