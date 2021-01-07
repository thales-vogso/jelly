/****************************************************************************
*	@       	       
*	@desc	加时间道具
*	@date	2014-12-29
*	@author	120101
*	@       	       
*	@file	game/
.app
*	@modify	null
******************************************************************************/
#include "game/TimeFly.h"
#include "game/TimeUI.h"

USING_NS_CC;
const std::string  TimeFly::TIMEPLUS = "timeplus";
TimeFly* TimeFly::create(int time)
{ 
	TimeFly*  pRet = new TimeFly();
	if (pRet && pRet->init(time))
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

bool TimeFly::init(int time)
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Sprite* sprite = NULL;
	if (time == 3)
		sprite = Sprite::create("pic/ui/3s.png");
	else if (time == 20)
		sprite = Sprite::create("pic/ui/20ss.png"); 
	sprite->setOpacity(0);
	this->addChild(sprite);
	sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 150));
	MoveTo* moveto = MoveTo::create(1, Vec2(300, visibleSize.height - 100));
	ScaleTo* scaleto = ScaleTo::create(1, 0.3);
	auto done = CallFuncN::create([=](Ref* ref){
		this->removeFromParentAndCleanup(true);


		int times = time;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeUI::TIMEUISHOCK, this);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeFly::TIMEPLUS, &times);

	
	});
	sprite->runAction(Sequence::create(Spawn::create(MoveBy::create(0.5,Vec2(0,300)), FadeIn::create(0.5), NULL), DelayTime::create(0.5), Spawn::create(moveto, scaleto, NULL), done, NULL));

	return true;
}
