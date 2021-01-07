/****************************************************************************
*	@       	       
*	@desc	主场景
*	@date	2014-12-12
*	@author	120101
*	@       	       
*	@file	main/Main.h
*	@modify	null
******************************************************************************/
#ifndef __MAIN_SCENE_H__
#define __MAIN_SCENE_H__

#include "cocos2d.h"
#include "main/Setting.h"
#include "main/Gateway.h"
#include "popup/Quit.h"
#include "game/Background.h"
#include "data/User.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
 //void shareCallback(int platform, int stCode, std::string& errorMsg);
class Main : public cocos2d::Layer
{
public:
	static Node* seekNodeByName(Node* root, const std::string& name);
	~Main();
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(Main);
	/*
	*  点击设置界面之后的响应
	*/
	void clickSetting();
	/*
	*  点击主界面之后的响应
	*/
	void clickMain();
	/*
	*  已经切换到主界面
	*/
	void switchToMain();
	/*
	*  已经切换到设置界面
	*/
	void switchToSetting();
	/*
	*  去除遮罩
	*/
	void removeMask();
    void showEndlessLayer();
private:
	/**
	*	是否弹出了退出界面
	*/
	bool openQuit = false;
	/**
	*	是否切换了界面
	*/
	bool switchScene = false;
	/**
	*	是否正在切换界面
	*/
	bool switchingScene = false;
	/**
	 *	外部按键错误
	 */
	void outKeyInit();

	/*
	*  遮罩层
	*/
	cocos2d::ui::Widget* _touchLayer;
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _moveInListener;
	cocos2d::EventListenerCustom* _moveOutListener;
	/*  背景  */
	Background*_bg;
};

#endif // #define __MAIN_SCENE_H__

