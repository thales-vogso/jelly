/****************************************************************************
*	@       	       
*	@desc	鱼的类
*	@date	2014-10-20
*	@author	120102
*	@       	       
*	@file	game/Fish.h
*	@modify	null
******************************************************************************/
#ifndef __GAME_FISH_H__
#define __GAME_FISH_H__
#include "cocos2d.h"
#include "cache/Fish.h"
#include "data/User.h"
#include "cache/Music.h"
#include "game/ScoreUI.h"
#include "cocostudio/CocoStudio.h"
#include "plat.h"
typedef struct FishDataTag{
	int id;
	int type;
	int arrest;
	std::string umgame;
}FishData;
class Fish: public cocos2d::Node
{
public:
	/*
	*	鱼的状态 分别是游动状态  被捕获的状态  和  死亡的状态
	*/
    enum State
	{
		MOVE=0,
		CATCHED,
		SHOCK,
		RAGED,
		DEAD
	};
	enum Arrest
	{
		NONE,//空..
		LINK,//连..
		ROUND,//圈..
		CAPTURE,//捕获..
		BOMB,//炸弹..
		RAGE//狂暴..
	};
	/**
	 *	构造函数
	 */
	Fish(int id, int type, int x, int y, std::string award = "");
	/**
	 *	析构函数
	 */
	~Fish();
	/**
	 *	鱼的游进
	 */
	void into(cocos2d::Rect rect);
	void into(bool suddenly);
	/**
	 *	更新
	 */
	void update(float dt);
	/**
	 *	暂停
	 */
	void pause();
	/**
	 *	恢复
	 */
	void resume();
	/*
	 *  鱼停止游动
	 */
	void stop();
	/*
	 *  鱼的自由游动
	 */
	void move();
	/*
	*	鱼的死亡
	*/
	void dead();
	void dead(float delay);
	//状态..
	/**
	 *	普通
	 */
	void normal();
	/**
	*	电击
	*/
	void shock();
	/**
	 *	狂暴
	 */
	void rage();
	/**
	*	闪光
	*/
	void shining();
	/**
	 *	鱼连成圈
	 */
	void beRound();
	/**
	 *	鱼被圈捕捉
	 */
	void beCapture();
	/**
	 *	鱼被炸
	 */
	void beBomb();
	/**
	 *	鱼被狂暴消除
	 */
	void beRage();
	/**
	 *	拉鱼
	 */
	void pull(cocos2d::Vec2 v);
	/**
	 *	获取鱼id
	 */
	int getID();
	/*
	*  获取鱼的类型
	*/
	int getType();
	/*
	*	获取鱼的状态
	*	@param 鱼的状态
	*/
	int getState();
	/**
	 *	是炸弹鱼
	 */
	bool isBomb();
	/**
	 *	可以被捕获
	 */
	bool isCanCatch();
	/**
	 *	可以被圈
	 */
	bool isCanRound();
	/**
	 *	获取鱼数据
	 */
	FishData getFishData();
	/**
	 *	获取碰撞区域
	 */
	cocos2d::Rect getCollision();
	/**
	*	移动改变
	*/
	void moveChange(float dt);
	/**
	*	改变身体
	*/
	void changeBody(float dt);
	/**
	*	恢复身体
	*/
	void changeNormal(float dt);
	/*
	*	返回是否有奖励。。
	*/
	std::string getAward();

	/**
	*	奖励
	*/
	std::string _award = "";
	/**
	*	捕获类型
	*/
	int _arrest = NULL;
	/*
	*	鱼的类型
	*/
	int _type;
private:
	/**
	*	进场变化
	*/
	bool _change = false;
	/**
	*	进场变化
	*/
	bool _rage = false;
	/*
	*	糖果的进场变化
	*/
	bool _shing=false;
	/**
	 *	鱼的唯一id
	 */
	int _id;
	/*
	*	初始化的鱼都是正常的游动状态
	*/
	int _state;
	/**
	*	umgame图片
	*/
	cocos2d::Sprite* __umgame = NULL;

	/**
	 *	加速度
	 */
	const float VELOCITY = 1800.0f;
	/**
	 *	运动延迟
	 */
	float _motionExpire = 0;
	/**
	 *	正常状态的运动间隔
	 */
	const float MOTION_DURATION_NORMAL = 2.0f;
	/**
	*	狂暴状态的运动间隔
	*/
	const float MOTION_DURATION_RAGE = 0.5f;
	/*
	*	闪光状态的运动间隔
	*/
	const float MOTION_DURATION_SHING = 1.0f;
	/**
	 *	物理参数-质量
	 */
	float MESS = 1.0f;
	/**
	 *	物理参数-力臂
	 */
	float MOMENT = 200;
	/* 
	 *	显示的鱼
	 */
	cocos2d::Node* __fishSprite;
	/**
	 *	状态-一般
	 */
	const std::string STATE_NORMAL = "move";
	/**
	 *	状态-暴怒
	 */
	const std::string STATE_RAGE = "rage";
	/**
	 *	状态-炸弹
	 */
	const std::string STATE_BOMB = "bomb";

};
#endif // __GAME_FISH_H__
