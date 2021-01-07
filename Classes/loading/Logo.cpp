/****************************************************************************
*	@       	2014,闈掑矝UMGame
*	@desc	娓告垙寮�濮婰OGO
*	@date	2015-03-23
*	@author	120102
*	@       	       
*	@file	loading/Logo.cpp
*	@modify	null
******************************************************************************/
#include "loading/Logo.h"
USING_NS_CC;

cocos2d::Scene* Logo::createScene()
{
	Scene*scene = Scene::create();
	Layer*layer = Logo::create();
	scene->addChild(layer);
	return scene;
}
bool Logo::init()
{
	if (!LayerColor::initWithColor(ccc4(0,0,0,0)))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

//#if TARGET_CHANNEL == TARGET_CHANNE_EGAME
//    // 	/* 鐖辨父鎴廘OGO  */
//    Sprite* logo1 = Sprite::create("egame_logo.png");
//    float scaleX1 = visibleSize.width / logo1->getContentSize().width;
//    float scaleY1 = visibleSize.height / logo1->getContentSize().height;
//    float scale1 = scaleX1 < scaleY1 ? scaleX1 : scaleY1;
//    logo1->setPosition(midPoint);
//    logo1->setScale(scale1*0.6);
//    logo1->setOpacity(0);
//    addChild(logo1, 1);
//#endif

	/*  鍏徃 LOGO */

	Sprite* logo2 = Sprite::create("UMGame_logo.png");
	float scaleX = visibleSize.width / logo2->getContentSize().width;
	float scaleY = visibleSize.height / logo2->getContentSize().height;
	float scale = scaleX < scaleY ? scaleX : scaleY;
	logo2->setPosition(midPoint);
	logo2->setScale(scale*0.6);
	logo2->setOpacity(0);
	addChild(logo2, 1);
	auto splashLogo1 = CallFuncN::create([=](Ref* ref){
//#if TARGET_CHANNEL == TARGET_CHANNE_EGAME
//        logo1->runAction(Sequence::create(FadeOut::create(0.3),FadeIn::create(0.7), FadeOut::create(0.7), NULL));
//#endif
	});
	auto splashLogo2 = CallFuncN::create([=](Ref* ref){
		//LayerColor::initWithColor(ccc4(0, 0, 0, 0));
		LayerColor::runAction(FadeOut::create(0.3));
		logo2->runAction(Sequence::create(FadeOut::create(0.3),FadeIn::create(0.7), FadeOut::create(0.7), NULL));
	});
	auto replacescene = CallFuncN::create([=](Ref* ref){
		Scene* scene = Loading::createScene();
		Director::getInstance()->replaceScene(scene);	
	});
	this->runAction(Sequence::create(splashLogo1, DelayTime::create(1.7), splashLogo2, DelayTime::create(1.7), replacescene, NULL));
	return true;
}
