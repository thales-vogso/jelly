/****************************************************************************
*	@       	       
*	@desc	新手引导的教学关卡场景
*	@date	2014-12-10
*	@author	120102
*	@       	       
*	@file	main/NewbieTeach.h
*	@modify	null
******************************************************************************/
#ifndef _NEWBIETEACH_H__
#define  _NEWBIETEACH_H__
#include "cocos2d.h"
#include "game/Fish.h"
#include "game/Line.h"
#include "game/Background.h"
#include "guide/Guide.h"
#include "game/UmGameUI.h"
#include "game/GoldUI.h"
#include "popup/Skip.h"

class NewbieTeach : public cocos2d::Layer
{
public:
	/*
	*	演示关卡的4个部分   
	*/
	enum TeachLevel
	{
		LINE,
		ROUND,
		SHING,
		LETTER
	};
	static cocos2d::Scene*createScene(TeachLevel);
	/*
	*	静态的create方法
	*/
	static NewbieTeach* create(TeachLevel);
	/*
	*	初始化函数
	*/
	bool init(TeachLevel);
	/*
	*	连的操作添加糖果
	*/
	void addLineFish();
	/*
	*	圈的操作添加糖果
	*/
	void addClicleFish();
	/*
		添加糖果
	*/
	void addFish(int id, int type, int x, int y, std::string award, bool suddenly = false);
	/*
	*	抓鱼中
	*/
	void catching(cocos2d::Vec2 v);
	/**
	*	圈抓取
	*/
	void catchRound();
	/*
	*	抓鱼结束
	*/
	void catchEnd(cocos2d::Vec2 v);
	/*
	*	根据点的位置获取是否有鱼存在
	*/
	Fish* getFishByPoint(cocos2d::Vec2 point);
	Fish* getFishByPoint(cocos2d::Vec2 point, Fish* referFish);
	/*
	*	判断抓鱼进行时是否碰到鱼
	*/
	void update(float dt);
	/**
	*	可连接
	*/
	bool _linkEnable = false;
	/*  背景  */
	Background*_bg;
	/*
	*	返回玩家是否操作成功
	*/
	bool isSuccess();
	/*
	*	玩家操作后的动作
	*/
	void FinishTeach();
	/*  析构函数  */
	~NewbieTeach();

	/*
	*	演示关卡的第几关
	*/
	TeachLevel _level;
	/*  显示金币的UI  */
	GoldUI* __goldUI;
	/*  显示UMGAME的ui  */
	UmGameUI* __umgame;
    /**
     *	物理速度-普通
     */
    const int SPEED_NORMAL = 1;
    /**
     *	物理速度-静止
     */
    const int SPEED_STATIC = 0;
    /**
     *	物理速度-闪光
     */
    const int SPEED_SHINE = 4;
private:
	/**
	*	飞行奖励容器
	*/
	cocos2d::Layer* __flyLayer;
	cocos2d::Size _size;
	/*  鱼层  */
	cocos2d::Layer*__fish;
	Line* __line;
	/**
	*	鱼池
	*/
	cocos2d::Vector<Fish*> _fishPool;
	/**
	*	连到的鱼
	*/
	cocos2d::Vector<Fish*> _fishNet;
	/**
	*	连接点
	*/
	cocos2d::Vec2 _linkPoint;

	/*
	*	玩家是否操作成功
	*/
	bool _isSuccess;
	/**
	*	动画节点
	*/
	Node* __rootNode = NULL;
	/**
	*	动画
	*/
	cocostudio::timeline::ActionTimeline* __action;
	/**
	*	跳过
	*/
	void skip(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/*
	*	添加闪光演示动画的糖果
	*/
	void addShingFish();
	/*
	*	添加字母糖果的演示糖果
	*/
	void addLetterFish();
	/*
	*	开始闪光效果
	*/
	void shining();
	/*
	*	闪光效果结束
	*/
	void shineUp();

};
#endif