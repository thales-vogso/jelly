/****************************************************************************
*	@       	       
*	@desc	弹窗层
*	@date	2014-11-11
*	@author	120101
*	@       	       
*	@file	popup/PopUp.h
*	@modify	null
******************************************************************************/
#include "popup/PopUp.h"

USING_NS_CC;

namespace popup{

	bool PopUp::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		return true;
	}

	bool PopUp::closeTopPop()
	{
		if (__PopBaseVector.size() > 0)
		{
			if (!__PopBaseVector.back()->moving)
			{
				PopBase* popBase = __PopBaseVector.back();
				popBase->closePop();				
			}
			return true;
		}
		return false;
	}

	void PopUp::addTopPop(PopBase* popBase)
	{
		if (__PopBaseVector.size() == 0||(__PopBaseVector.size() != 0 && !__PopBaseVector.back()->moving))
		{
			__PopBaseVector.push_back(popBase);
			this->addChild(popBase, __PopBaseVector.size());
		}
	}
	void PopUp::popBack()
	{
		__PopBaseVector.back()->removeFromParentAndCleanup(true);
		__PopBaseVector.pop_back();
	}

	int PopUp::popNum()
	{
		return __PopBaseVector.size();
	}

}