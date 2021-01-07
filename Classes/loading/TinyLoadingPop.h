/****************************************************************************
*	@       	       
*	@desc	小型载入弹窗
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	loading/TinyLoadingPop.h
*	@modify	null
******************************************************************************/
#ifndef __TINYLOADING_POP_H__
#define __TINYLOADING_POP_H__

#include "cocos2d.h"
#include "loading/Loader.h"
#include "game/Game.h"

class TinyLoadingPop : public cocos2d::Layer{
public:
	/**
	 *	构造函数
	 */
	TinyLoadingPop();
	/**
	 *	析构函数
	 */
	virtual ~TinyLoadingPop();
	/**
	 *	初始化
	 *	@return	布尔值
	 */
	virtual bool init();
	/**
	 *	创造场景
	 *	@return	场景
	 */
	static TinyLoadingPop* create();
	/**
	 *	关闭
	 */
	void close();
private:

};

#endif // __TINYLOADING_POP_H__
