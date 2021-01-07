/****************************************************************************
*	@       	       
*	@desc	umgame系统
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/UmGame.h
*	@modify	null
******************************************************************************/
#ifndef __UMGAMEUI_H__
#define  __UMGAMEUI_H__
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "data/UmGame.h"
#include "plat.h"
class UmGameUI :public cocos2d::Layer
{

public:
	static UmGameUI* create(bool guide = false);
	/*
	*  初始化
	*/
	bool init();
	/**
	*	获得字母
	*/
	void getLetter(std::string str);
	/*
	*  新手教程下把所有的字母变暗
	*/
	void setUmgameNull();
	cocos2d::ui::Widget* _price;
	/**
	*	面板
	*/
	cocos2d::ui::Widget* _umgame;
	/*
	*	umgame UI hehe
	*/
	cocos2d::Node*_umgameUI;
	/*
	*	获取UMGAMEUI 
	*/
	Node* getUmgameUI();
private:
	/**
	*	是否新手教程模式
	*/
	bool _guide = false;
	/**
	*	cocostuido创造的暂停界面ui的名字
	*/
#ifdef LONGBAO
	const std::string PANEL_NAME = "csb/longbao/ui/umgame.csb";
#endif
#ifdef CANDY
	const std::string PANEL_NAME = "csb/game/umgame.csb";
#endif	
	const std::string PRICE_NAME = "csb/game/jiangli.csb";

	const std::string UMGAME = "umgame";
	const std::string PRICENUM = "num";
	
	cocos2d::ui::Text* _num;
	cocos2d::Sprite* _letter;
	cocos2d::ui::Widget* _coin;
	/**
	*	初始化UMGAME
	*/
	void changeUmGame();
	/**
	*	增加UMGAME
	*/
	void addUmGame(std::string str, cocos2d::Vec2 pos);

	

	/**
	*	没有获得的字母透明度
	*/
	const float NOGET = 64;
	/**
	*	获得的字母透明度
	*/
	const float GET = 255;
	/**
	*	移动时间
	*/
	const float MOVEDELTATIME = 1;
	/**
	*  闪动时间
	*/
	const float FLASHDELTATIME = 0.3f;
	/**
	*  金币移动
	*/
	void moveCoin(float dt);
	
};
#endif