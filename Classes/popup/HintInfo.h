/****************************************************************************
*	@       	       
*	@desc
*	@date	2015-1-5
*	@author	120102
*	@       	       
*	@file	popup/HintInfo.h
*	@modify	null
******************************************************************************/
#include "cocos2d.h"
namespace popup{
	class HintInfo :public cocos2d::LayerColor
	{
	public:
		bool init();
		CREATE_FUNC(HintInfo);
	};
}