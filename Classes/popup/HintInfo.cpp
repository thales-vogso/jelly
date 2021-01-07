/****************************************************************************
*	@       	       
*	@desc
*	@date	2015-1-5
*	@author	120102
*	@       	       
*	@file	popup/HintInfo.cpp
*	@modify	null
******************************************************************************/
#include "popup/HintInfo.h"
using namespace cocos2d;
namespace popup{
	bool HintInfo::init()
	{
		if (!LayerColor::initWithColor(Color4B(100, 100, 100, 100)))
		{
			return false;
		}
		auto callback = [](Touch *, Event *)
		{

			return true;

		};

		auto listener = EventListenerTouchOneByOne::create();

		listener->onTouchBegan = callback;

		listener->setSwallowTouches(true);

		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		return true;
	}
}