/****************************************************************************
*	@       	       
*	@desc	帮助
*	@date	2014-12-9
*	@author	120101
*	@       	       
*	@file	main/Guide.h
*	@modify	null
******************************************************************************/
#ifndef __GUIDE_H__
#define __GUIDE_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "main/Main.h"
#include "popup/Skip.h"
#include "guide/NewbieTeach.h"
#include "guide/TeachEntity.h"
#include "plat.h"
class Guide : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene(int step);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Guide);

	void onEnterTransitionDidFinish();

	enum Step
	{
		STEP1 = 1,
		STEP2,
		STEP3,
		STEP4,
		FINISH
	};
	enum CSBStep
	{
		CSBSTEP1 = 1,
		CSBSTEP2 = 4,
		CSBSTEP3 = 5,
		CSBSTEP4 = 11,
	};
private:
	/**
	*	目录名前缀
	*/
	std::string _preStr = "";
	/**
	*	跳过
	*/
	cocos2d::ui::Widget* _skip;
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _moveInListener;
	cocos2d::EventListenerCustom* _moveOutListener;
    
    //设置监听
    cocos2d::EventListenerCustom *_listener;
    
    /**
	*	是否弹出退出界面
	*/
	bool openQuit = false;
	/**
	*	第几幕
	*/
	int _frame = 1;
	/**
	*	第几步
	*/
	int _step = 1;
	/**
	*	背景节点
	*/
	Node* __bgNode = NULL;
	/**
	*	动画节点
	*/
	Node* __rootNode = NULL;
	/**
	*	标签节点
	*/
	Node* __labelNode = NULL;
	/**
	*	节点动画
	*/
	cocostudio::timeline::ActionTimeline* __action;
	/**
	*	标签动画
	*/
	cocostudio::timeline::ActionTimeline* __labelAction;
	/**
	*	跳过
	*/
	void skip(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	*	下一步
	*/
	void next(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	 *	外部按键
	 */
	void outKeyInit();
	/**
	*	切换步骤
	*/
	void switchStep(int step);
	/**
	*	加载标签节点
	*/
	void loadLabelNode(int step);
	/**
	*	切换到下一步
	*/
	void nextStep();
	/**
	*	播放第一帧
	*/
	void playFirstFrame();
};

#endif // #define __MAIN_SCENE_H__

