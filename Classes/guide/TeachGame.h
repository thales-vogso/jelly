/****************************************************************************
*	@       	       
*	@desc	新手教程的关卡部分场景
*	@date	2014-12-15
*	@author	jinzhen
*	@       	       
*	@file	guide/TeachGame.h
*	@modify	null
******************************************************************************/
#ifndef _TEACHGAME_H__
#define  _TEACHGAME_H__
#include "cocos2d.h"
#include "game/Background.h"
#include "guide/Guide.h"
#include "game/TimeUI.h"
#include "game/ScoreUI.h"
#include "game/UmGameUI.h"
#include "game/GoldUI.h"
#include "guide/TeachEntity.h"
#include "ui/CocosGUI.h"
#include "guide/TeachEntity.h"
#include "popup/TeachPause.h"
class TeachGame : public cocos2d::Layer
{
public:

	/*
	*	创建场景
	*/
	static cocos2d::Scene*createScene(TeachEntity::Level);
	/*
	*	静态的create方法
	*/
	static TeachGame* create(TeachEntity::Level);
	/*
	*	初始化
	*/
	bool init(TeachEntity::Level);
 	/*
 	*	场景完全加载好后再开始倒计时
 	*/
 	void onEnterTransitionDidFinish();
	/*
	*	设置分数
	*/
	void setScore(cocos2d::EventCustom*e);
	/*
	*	显示时间 
	*/
	void showTime(double time);
	/*  是哪个关卡  */
	TeachEntity::Level _level;
	/*  显示时间的ui  */
	TimeUI* __timeUI;
	/*  显示金币的UI  */
	GoldUI* __goldUI;
	/*  显示UMGAME的ui  */
	UmGameUI* __umgame;
	/*  显示得分的UI  */
	ScoreUI* __scoreUI;
	/*  是否有炸弹鱼  */
	bool _isBombFish;
	/*  设置标志 是否有字母鱼  */
	bool _isStringFish;
	/*
	*	当前关卡结束后的操作
	*/
	void FinishLevel();
	/*
	*	新手教程游戏数据为0
	*/
	void setDateNull();
	/*
	*	暂停按钮
	*/
	void pauseClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*	暂停游戏
	*/
	void gamePause();
	/*
	*	继续游戏
	*/
	void gameResume();
	/*
	*	重置游戏
	*/
	void reset();
	/*
	*	析构函数  是否各种事件
	*/
	~TeachGame();

private:
	/**
	*	飞行奖励容器
	*/
	cocos2d::Layer* __flyLayer;
	/*
	*	糖果的物理层
	*/
	TeachEntity *_fishes;
	/*  游戏的剩余时间  */
	int _surplusTime;

	/*  游戏已经进行的时间  */
	double _runningTime;
	/*  教学关卡的游戏的时间  */
    double _time;
	/*
	*	游戏背景
	*/
	Background*_bg;
	/*
	*	新手教程的得分
	*/
	int  _score;
	/*
	*	新手教程的金币数
	*/
	int _goldNum;
	/**
	*	外部按键
	*/
	void outKeyInit();
	/*
	*	游戏倒计时
	*/
	void Countdown(int time);
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _moveInListener;
	cocos2d::EventListenerCustom* _moveOutListener;
	/**
	*	是否弹出退出界面
	*/
	bool openQuit = false;
	/*
	*	倒计时数字显示
	*/
	cocos2d::LabelTTF*_label;
	/**
	*	泡泡飞行
	*/
	void popFly(int score, cocos2d::Vec2 pos);
};
#endif // !_TEACHGAME_H__