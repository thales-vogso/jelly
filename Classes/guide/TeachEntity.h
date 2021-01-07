/****************************************************************************
*	@       	       
*	@desc	游戏物理引擎
*	@date	2014-12-15
*	@author	120102
*	@       	       
*	@file	guide/TeachEntity.h
*	@modify	null
******************************************************************************/
#ifndef  __TEACH_ENTITY_H__
#define  __TEACH_ENTITY_H__

#include "cocos2d.h"
#include "game/Fish.h"
#include "game/Line.h"
#include "data/Game.h"
#include <sys/timeb.h>
#include "data/Item.h"

class TeachEntity : public cocos2d::Layer
{
public:
	enum Level
	{
		LEVEL1,
		LEVEL2,
		LEVEL3
	};
	/*
	*   静态的create方法
	*/
	static TeachEntity* create(Level,cocos2d::PhysicsWorld *world);
	/*
	*   初始化
	*/
	bool init(Level,cocos2d::PhysicsWorld *world);
	/**
	*	重置
	*/
	void reset();
	/*
	*	更新函数  在这里面处理  连线以及 鱼的消除  还有 触摸的处理
	*/
	void update(float dt);
	/**
	*	游戏结束，停止任何操作
	*/
	void gameOver();
	/**
	*	暂停
	*/
	void pause();
	/**
	*	恢复
	*/
	void resume();
	/**
	*	现在物理引擎的速度
	*/
	int _physicsSpeed;

	/**
	*	抓鱼进行
	*/
	void catching(cocos2d::Vec2 v);
	/**
	*	圈抓取
	*/
	void catchRound();
	/**
	*	抓鱼结束
	*/
	void catchEnd(cocos2d::Vec2 v);
	/**
	*	事件，鱼捕获
	*/
	static const std::string FISH_CATCHED;
	/**
	*	获取游戏执行时间
	*/
	double getRunTime();
	/**
	*	闪光
	*/
	void shining();
	/**
	*	闪光结束
	*/
	void shineUp();
	/**
	*	是否正在闪光时间
	*/
	bool isShining();


	/**
	*	添加事件
	*/
	void addListener(const std::string &eventName, const std::function<void(cocos2d::EventCustom*)>& callback);
	/**
	*	游戏进行中
	*/
	static const std::string RUNNING;
	
	/**
	*	事件-闪光时间
	*/
	static const std::string SHINE_START;
	/**
	*	事件-闪光时间结束
	*/
	static const std::string SHINE_FINISH;


	/*  移除监听  */
	void removeListener(const std::string &eventName);
	
	/**
	*	可连接
	*/
	bool _linkEnable = false;

	/*
	*	关卡数
	*/
	Level _level;
	/*
	*	闪光时间的倒计时
	*/
	double shingCountTime();
	/*
	*	第一次的闪光时间
	*/
	double _beginShiningTime;

protected:
	Line* __line;
	cocos2d::Layer* __fish;

private:
	/**
	*	移动改变
	*/
	void moveChange(float dt);
	/*
	*   往层里面添加鱼
	*   @param    dt 每隔dt 秒添加一条鱼  在这里设置鱼的种类
	*/
	void addFish(int id, int type, int x, int y, std::string award, bool suddenly = false);
	void addFish(int type);
	void addFish();
	/**
	*	恢复鱼
	*/
	void recoveryFish();
	/**
	*	通过点获取鱼，referFish为参考鱼
	*	@param	point	点
	*/
	Fish* getFishByPoint(cocos2d::Vec2 point);
	Fish* getFishByPoint(cocos2d::Vec2 point, Fish* referFish);
	


	/**
	*	物理世界
	*/
	cocos2d::PhysicsWorld* _world;
	/**
	*	边界
	*/
	cocos2d::Rect _zone;
	/**
	*	事件分发器
	*/
	cocos2d::EventDispatcher* _evt;
	/**
	*	现在的物理速度，用于改变时候恢复速度
	*/
	int _nowSpeed;
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

	/**
	*	时间戳
	*/
	double _timestamp = 0.0f;
	/**
	*	运行时间
	*/
	double _runTime = 0.0f;
	/**
	*	游戏开始时间
	*/
	double _startTime = 0.0f;
	/**
	*	游戏修正时间
	*/
	double _correctTime = 0.0f;
	/**
	*	暂停时间
	*/
	double _pauseTime = 0.0f;
	/**
	*	上次执行时间
	*/
	double _lastTime = 0.0f;
	/**
	*	每种鱼最少出现条数
	*/
	const int FISH_TYPE_MIN = 2;
	/**
	*	鱼的最大数目
	*/
	const int FISH_MAX = 20;
	/**
	*	出鱼频率，秒
	*/
	const double FISH_FREQUENCY = 0;
	/**
	*	炸弹鱼出现期限
	*/
	double _bombFishExpire = 0;
	/**
	*	闪光效果
	*/
	bool _isShine = false;
	/**
	*	闪光时间，单位秒
	*/
	const int SHINE_TIME = 10;
	/**
	*	第一次闪光鱼出现时间，单位秒
	*/
	const double SHINE_START_TIME = 30.0f;
	/**
	*	闪光鱼出现间隔，单位秒
	*/
	const double SHINE_START_TIME_INTERVAL = 10.0f;
	/**
	*	字母鱼
	*/
	bool _isAward = false;
	/**
	*	连操作出现奖励数量
	*/
	const int AWARD_LINK_NUM = 10;
	/**
	*	圈操作出现奖励数量
	*/
	const int AWARD_ROUND_NUM = 7;
	
	
	/**
	*	上下边界
	*/
	const int TOP_SPACE = -100;
	const int BOTTOM_SAPCE = -100;
	const int LEFT_SPACE = -100;
	const int RIGHT_SAPCE = -100;
	//
	double _lastClick = 0.0f;
	/**
	*	当前类型
	*/
	std::vector<int> _types;
	/*
	*	屏幕中是否有字母鱼
	*/
	bool _isHaveAward;
};
#endif // __GAME_ENTITY_H__