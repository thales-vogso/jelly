/****************************************************************************
*	@       	       
*	@desc	分数ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/ScoreUI.h
*	@modify	null
******************************************************************************/
#ifndef __ScoreUI_H__
#define  __ScoreUI_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/Game.h"
#include "data/Item.h"

class ScoreUI :public cocos2d::Layer
{

public:
	~ScoreUI();
	/*
	*  初始化
	*/
	bool init();
	/*
	*  create  方法
	*/
	CREATE_FUNC(ScoreUI);
	/*
	*	改变得分
	*/
	void ScoreChange(cocos2d::EventCustom* e);
	/*
	*	改变关卡
	*/
	void stageChange(cocos2d::EventCustom*e);
	/*
	*	修正位置
	*/
	void fixPosition();
	/*
	*	根据关卡设置目标分数
	*/
	void setTotleScore(int stage);
	/**
	*	cocostuido创造的暂停界面ui的名字
	*/
	const std::string PANEL_NAME = "csb/game/score.csb";
	/*  当前的得分  */
	const std::string CUSCORE = "cuscore";
	/*  目标得分  */
	const std::string TOTLESCORE = "totlescore";
	/*  关卡  */
	const std::string LEVEL = "level";
	/*  获取的ui  */
	cocos2d::ui::Widget* _panel;
	/*  关卡  */
	cocos2d::ui::Widget*_stage;
	/*  目标得分  */
	cocos2d::ui::Widget*_target;
	/*  设置是否是无尽模式  默认不是  */
	void setEndLess(bool = false);
	/*
	*  改变分数板上的分数
	*/
	void changeScore(int score);
	/*
	*  改变分数板上的分数
	*/
	cocos2d::Vec2 getScorePosition();
	//发送给主场景的点击事件..
	static const std::string SCOREUISHOCK;
private:	
};
#endif