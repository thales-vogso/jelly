/****************************************************************************
*	@       	       
*	@desc	主游戏场景
*	@date	2014-10-22
*	@author	120102
*	@       	       
*	@file	game/GameScene.h
*	@modify	null
******************************************************************************/
#ifndef __GAME_SCENE_H__
#define  __GAME_SCENE_H__
#include "cocos2d.h"
#include "popup/Pause.h"
#include "ui/CocosGUI.h"
#include "ScoreUI.h"
#include "game/ItemUI.h"
#include "GoldUI.h"
#include "TimeUI.h"
#include "UmGameUI.h"
#include "cocostudio/CocoStudio.h"
#include "game/GameEntity.h"
#include "ui/UITextField.h"
#include "data/Item.h"
#include "popup/Success.h"
#include "popup/Fail.h"
#include "popup/TimeItem.h"
#include "popup/ItemShop.h"
#include "popup/GoldShop.h"
#include "popup/QuitGame.h"
#include "game/Background.h"
#include "game/PopFly.h"
#include "game/TimeFly.h"
#include "popup/ItemInfo.h"
#include "popup/AdBlock.h"
class Game : cocos2d::Layer
{
public: 


	/*
	*	游戏中的引导显示不同的文字
	*/
	enum GUIDETEXT
	{
		THRESS,
		SHING,
		LETTER,
		FULLLETTER,
		TIMEITEM,
		FAIL,
		GUIDESHOCK,
		GUIDEBOMB,
		GUIDERAGE
	};

	/*
	*	鱼的层
	*/
	GameEntity*fishes = nullptr;
	/*  初始化  */
	virtual bool init();
	/**
	*	创造场景
	*	@return	场景
	*/
	static cocos2d::Scene*createScene();

	/**
	*	暂停界面的点击
	*/
	void pauseClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);

	/*
	*  create 方法
    */
	CREATE_FUNC(Game);

	// 游戏背景..
	cocos2d::Sprite*bg;
	// 功能区的大小..
	cocos2d::Size funcSize;
	//更改分数..
	void setScore(cocos2d::EventCustom* e);

	/*
	*	设置关卡数
	*	@param str  需要设置的关卡数
	*/
	void setLevel(std::string str);


	/*  重新初始化  */
	void resumeInit(cocos2d::EventCustom* e);

	/*  使用道具  */
	void useItem(cocos2d::EventCustom* e);
	/*  外部按键  */
	void outKeyInit();
	
	/*  暂停游戏  包括鱼的游动和时间  */
	void gamePause();
	/*  继续游戏  */
	void gameResume();
private:
	/**
	*	飞行奖励容器
	*/
	cocos2d::Layer* __flyLayer;
	/**
	*	是否弹出了退出界面
	*/
	bool openQuit = false;
	/*
	*	读取存档时间
	*/
	double _time;
	/*  开始的得分和关卡  */
	int _score;
	int _stage;
	/*  显示时间的ui  */
	TimeUI* __timeUI;
	/*  显示金币的UI  */
	GoldUI* __goldUI;
	/*  显示道具的ui  */
	ItemUI* __itemUI;
	/*  显示UMGAME的ui  */
	UmGameUI* __umgame;
	/*显示得分的UI*/
	ScoreUI* __scoreUI;
	/*  狂暴只能使用一次 设置一个标志  */
	bool _useMagic;
	/*  是否有炸弹鱼  */
	bool _isBombFish;
	/*  设置标志 是否有字母鱼  */
	bool _isStringFish;
	/*  狂暴的背景  */
	cocos2d::Sprite*_magicbg;
	/*  雷电的背景  */
	cocos2d::Sprite*_shockbg;
	/*  闪光时间的背景  */
	cocos2d::Sprite*_shareingbg;
	/*  是否使用了时间道具  */
	bool _timeItem;
	/*  是否是第一次游戏  */
	bool _firstgame;

	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _goldUIListener;
	cocos2d::EventListenerCustom* _itemUIListener;
	cocos2d::EventListenerCustom*_gamefailListener;
	cocos2d::EventListenerCustom*_timeListener;
	cocos2d::EventListenerCustom*_appgamepause;
	cocos2d::EventListenerCustom*_appgameresume;
	/*  弹出商城游戏暂停的界面  */
	static const std::string GAMEPAUSE;

	/*  析构函数  */
	~Game();
	/*  为游戏中各个的ui 赋值  */
	void initWithUIValue();
	/*  游戏失败  弹出失败的清算界面  鱼清空  用户数据清空  */
	void gameFail(cocos2d::EventCustom*e);
	/*  监听道具数量的改变  */
	void itemNumFunction(cocos2d::EventCustom*e);
	/*  无尽模式  */
	void endLess(cocos2d::Ref*ref);
	/*
	*	设置得分的显示
	*	@param num 需要改变的数字
	*/
	void setScoreNum(int num);
	/*  游戏完全加载好后再开始倒计时  */
	void onEnterTransitionDidFinish();
	/*  设置游戏的时间  */
	void showTime(double time);
	/**
	*	倒计时的显示
	*/
	void Countdown(int time);
	/**
	*	泡泡飞行
	*/
	void popFly(int score,cocos2d::Vec2 pos);
	/*
	*	添加灰色蒙版   
	*	@param guide 根据的不同来添加不同的文字   rect 是要裁剪的区域  
	*/
	void addGrayLayer(GUIDETEXT guide ,cocos2d::Node *node);
	/*
	*	去掉灰色蒙版
	*/
	void dropGrayLayer(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e, GUIDETEXT guide);
	/*
	*	点击引导后的动作
	*/
	void clickGuide(GUIDETEXT guide);
	void adBlock(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	//
	double _lastClick = 0.0f;
	//设置标志  umgame字母是否集齐..
	bool _isFullUmgame;
	//背景类的对象..
	Background*_bg;
	//是否是无尽模式..
	bool _endless;
	/**
	*	自定义监听
	*/
	cocos2d::EventListenerCustom* _moveInListener;
	cocos2d::EventListenerCustom* _moveOutListener;
	//无尽模式的得分..
	int _endlesssocre;
	/*  游戏的剩余时间  */
	int _surplusTime;
	/*  返回主菜单的方式  */
	bool _backMenuEndGame;
	/*  游戏已经进行的时间  */
	double _runningTime;
	
	/*  技能冷却的灰色图片1  */
	cocos2d::Sprite*_pray1;
	/*  技能冷却的灰色图片2  */
	cocos2d::Sprite*_pray2;
	/*  魔药道具的冷却图片  */
	cocos2d::Sprite*_rageCDPanel;
	/*  雷电道具的冷却图片  */
	cocos2d::Sprite*_shockCDPanel;
	/*  魔药的冷却条  */
	cocos2d::ProgressTimer * _rageProgress;
	/*  雷电的冷却条  */
	cocos2d::ProgressTimer*_shockProgress;
	/*
	*	 当局游戏的总得分
	*/
	int  _preScore;
	/*
	*	倒计时数字显示
	*/
	cocos2d::LabelTTF*_label;
	/*
	*	暂停按钮
	*/
	cocos2d::ui::Widget* _menuPause;
	/*
	*	奖励的csb
	*/
	const std::string PRICE_NAME = "csb/game/jiangli.csb";
	/*
	*	奖励的金币数字
	*/
	const std::string PRICENUM = "num";
	/*
	*	奖励的UI
	*/
	cocos2d::ui::Widget* _price;
	/*
	*	道具的位置
	*/
	cocos2d::Vec2 _itemPoint;
	/*
	*	雷电道具是否正在冷却中
	*/
	bool _shockisCD;
	/*
	*	显示三个道具的UI
	*/
	cocos2d::Sprite*_itemshockui;
	cocos2d::Sprite*_itemrageui;
	cocos2d::Sprite*_itembombui;
	/*
	*	提示信息每一关只出现一次
	*/
	bool _showGuideInfo;

	/*
	*	判断是否是暂停状态
	*/
	bool _isPauseState;
	/*
	*	去除广告的UI
	*/
	cocos2d::ui::Widget*_adblockui;


#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
    /*
     *   获取和显示广告
     */
    void menuBannerCallback();
    /*
     *   隐藏广告
     */
    void hiddenBannerCallback();

	
#endif
    /*
     *  是否创建了广告
     */
    bool _isHaveAD;
	/*
	*	设置三个道具是否是可以点击的...
	*/
	void setItemEnable(bool b);

};

#endif