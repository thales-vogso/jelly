/****************************************************************************
*	@       	       
*	@desc	飞行泡泡
*	@date	2014-12-28
*	@author	120101
*	@       	       
*	@file	game/popFly.app
*	@modify	null
******************************************************************************/
#include "game/PopFly.h"
#include "game/ScoreUI.h"

USING_NS_CC;

PopFly* PopFly::create(cocos2d::Vec2 from, cocos2d::Vec2 to, bool large)
{ 
	PopFly*  pRet = new PopFly();
	if (pRet && pRet->init(from,to,large))
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL; 
	} 
}

bool PopFly::init(cocos2d::Vec2 from, cocos2d::Vec2 to, bool large)
{
	if (!Layer::init())
	{
		return false;
	}
#ifdef CANDY
	//气泡..
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("pic/candy/candy_tm.png");
	sprite->setPosition(from);
	if(large)
		sprite->setScale(1);
	else
		sprite->setScale(0.7);
	addChild(sprite);
	MoveTo* moveto = MoveTo::create(1, to);
	ScaleTo* scaleto = ScaleTo::create(1, 0.5);
	auto done = CallFuncN::create([=](Ref* ref){
		sprite->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ScoreUI::SCOREUISHOCK, this);
	});
	sprite->runAction(Sequence::create(Spawn::create(moveto, scaleto, NULL), done, NULL));

#endif
#ifdef LONGBAO
	//气泡..
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto sprite = Sprite::create("pic/longbao/bao.png");
	sprite->setPosition(from);
	if(large)
		sprite->setScale(2);
	else
		sprite->setScale(1);
	addChild(sprite);
	MoveTo* moveto = MoveTo::create(1, to);
	ScaleTo* scaleto = ScaleTo::create(1, 0.5);
	auto done = CallFuncN::create([=](Ref* ref){
		sprite->removeFromParentAndCleanup(true);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ScoreUI::SCOREUISHOCK, this);
	});
	sprite->runAction(Sequence::create(Spawn::create(moveto, scaleto, NULL), done, NULL));
#endif

	return true;
}
