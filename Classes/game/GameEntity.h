/****************************************************************************
*	@       	       
*	@desc	游戏物理引擎
*	@date	2014-11-2
*	@author	110101
*	@       	       
*	@file	game/GameEntity.h
*	@modify	null
******************************************************************************/
#ifndef  __GAME_ENTITY_H__
#define  __GAME_ENTITY_H__

#include "cocos2d.h"
#include "Fish.h"
#include "Line.h"
#include "data/Game.h"
#include <sys/timeb.h>
#include "data/Item.h"

class GameEntity : public cocos2d::Layer
{
public:
	/*
	* 静态的create方法
	*/
//	CREATE_FUNC(GameEntity);
    static GameEntity* createWithPhysicsWorld(cocos2d::PhysicsWorld *world);

	/*
	* 初始化
	*/
	bool init(cocos2d::PhysicsWorld *world);
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
	 *	抓鱼开始
	 */
	void catchBegin(cocos2d::Vec2 v);
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
	 *	道具使用中
	 */
	bool isItemInUsing();
	/**
	 * 使用炸弹道具  就是一定范围的鱼全部消除  有粒子效果   点击的次数有限制
	 */
	bool useBomb(cocos2d::Vec2 v);
	void useBomb();
	/**
	 *	炸弹使用完毕
	 */
	void useBombUp();
	/**
	 *	使用雷电道具  鱼全部静止不动  时间是三秒
	 */
	void useShock();
	/**
	 *	雷电使用完毕
	 */
	void shockUseUp();
	/*
	 *   使用魔瓶道具（切水果）  时间是三秒
	 */
	void useRage();
	/**
	 *	结束魔瓶道具
	 */
	void rageUseUp();
	enum ItemType
	{
		SHOCK,
		BOMB,
		RAGE
	};
	/**
	 *	添加事件
	 */
	void addListener(const std::string &eventName, const std::function<void(cocos2d::EventCustom*)>& callback);
	/*
	*	游戏进行中（不去除雷电的静止时间）
	*/
	static const std::string RUNNINGGAME;
	/**
	*	游戏进行中
	*/
	static const std::string RUNNING;
	/**
	 *	事件-道具效果开始
	 */
	static const std::string ITEM_START;
	/**
	 *	事件-道具效果完毕
	 */
	static const std::string ITEM_FINISH;
	/**
	 *	事件-闪光时间
	 */
	static const std::string SHINE_START;
	/**
	*	事件-闪光时间结束
	*/
	static const std::string SHINE_FINISH;
	/**
	*	事件-双击事件
	*/
	static const std::string DOUBLE_CLICKED;
	/*
	*	事件-出现暗黑小笼女事件
	*/
	static const std::string SHING_FISH;
	/*
	*	事件-出现字母鱼事件
	*/
	static const std::string LETTER_FISH;	
	/*  处理单击事件  */
	void singleClick(float dt);
	/*
	*	是否是雷电时间
	*/
	bool isShock();
	/*
	*	是否是狂暴时间
	*/
	bool isRage();
	/*
	*	是否是闪光时间
	*/
	bool isShine();
	/*  移除监听  */
	void removeListener(const std::string &eventName);
	/*  是否是无尽模式  */
	void endless(bool isendless);
	/*  电击道具是否是冷却中  */
	bool shockisCD();
	/*  无尽模式的魔药道具是否是冷却时间  */
	bool rageisCD();
	/*  设置是第一次游戏  */
	void setGameFirst();
	/**
	*	可连接
	*/
	bool _linkEnable = false;

	cocos2d::MotionStreak* _streak;
	/*
	*	返回雷电道具从使用后到现在的冷却百分比
	*/
	double shockCDTime();
	/*
		返回无尽模式下的魔药从使用后到现在的冷却百分比
		*/
	double rageCDTime();
	/*
	*	魔药使用倒计时
	*/
	double rageCountTime();
	/*
	*	雷电使用的倒计时
	*/
	double shockCountTime();
	/*
	*	闪光时间的倒计时
	*/
	double shingCountTime();
	/*
	*	获取闪光鱼
	*/
	cocos2d::Node* getShing();
	/*
	*	获取字母鱼
	*/
	Node*getLetter();
	/*
	*	获取是否是闪光效果
	*/
	bool getIsShing();
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
	Fish* getRageFishByPoint(cocos2d::Vec2 point);
	/**
	 * 使用炸弹效果
	 */
	bool useBombValid();
	
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
	const int SPEED_SHINE = 2;
	/**
	*	物理速度-狂暴
	*/
	const int SPEED_RAGE = 4;
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
	 *	是否使用炸弹
	 */
	bool _isUseBomb = false;
	/**
	 *	炸弹使用时间
	 */
	double _useBombTime = 0;
	/**
	 *	爆炸半径
	 */
	const int BOMB_RADIUS = 300;
	/**
	 *	是否使用雷电
	 */
	bool _isUseShock = false;
	/**
	 *	电击道具持续时间
	 */
	const int SHOCK_TIME = 5;
	/**
	 *	是否使用狂暴魔药
	 */
	bool _isUseRage = false;
	/**
	 *	狂暴魔药持续时间
	 */
	const int RAGE_TIME = 10;
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
	/*
	*	设置是否是无尽模式
	*/
	bool _isendless;
	/*  电击道具的冷却时间  */
	const double _shockCD = 30;
	/*  无尽模式的魔药道具冷却时间  */
	const double _rageCD = 60;
	/*  魔药道具是否是冷却中  */
	bool _rageisCD;
	/*  雷电道具是否是冷却中  */
	bool _shockisCD;
	/*  记录使用雷电道具的时候游戏进行的时间  */
	double _useShockTime;
	/*  记录使用魔药道具的时候游戏进行的时间  */
	double _useRageTime;
	/*
	*	记录闪光开始的时间
	*/
	double _beginShiningTime;
	/*  是否是第一次使用雷电道具  */
	bool _isFirstUseShock;
	/*  是否是第一次使用魔药道具  */
	bool _isFirstUseRage;
	/*
	*	游戏进行的时间  不去除雷电时间
	*/
	double _runGameTimes;
	/*
	*	动作的标志
	*/
	enum ACTION_ITEM
	{
		ACTION_ITEM_RAGE=20,
		ACTION_ITEM_SHOCK
	};

};
#endif // __GAME_ENTITY_H__