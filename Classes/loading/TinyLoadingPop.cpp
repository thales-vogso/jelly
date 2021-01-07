/****************************************************************************
*	@       	       
*	@desc	小型载入弹窗
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	loading/TinyLoadingPop.app
*	@modify	null
******************************************************************************/

#include "TinyLoadingPop.h"

USING_NS_CC;

TinyLoadingPop::TinyLoadingPop(){
	this->init();
}
TinyLoadingPop::~TinyLoadingPop(){
}
TinyLoadingPop* TinyLoadingPop::create(){
	TinyLoadingPop* pop = new TinyLoadingPop();
	return pop;
}
void TinyLoadingPop::close(){
	removeFromParentAndCleanup(true);
}
bool TinyLoadingPop::init(){
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Sprite* loading = Sprite::create("loading/tiny_loading.png");
	loading->setPosition(size.width*0.5,size.height*0.5);
	loading->runAction(RepeatForever::create(RotateBy::create(1, 360)));
	addChild(loading);
	return true;
}