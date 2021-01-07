/****************************************************************************
*	@       	       
*	@desc	主游戏场景
*	@date	2014-10-22
*	@author	120102
*	@       	       
*	@file	game/GameScene.cpp
*	@modify	null
******************************************************************************/
#include "game/Game.h"//  场景层
#include "popup/ItemShop.h"
#include "AppDelegate.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "AdsmogoBanner.h"
#include "AdsMogoInterstitial.h"
#endif
USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
const std::string Game::GAMEPAUSE = "gamepause";
static cocos2d::PhysicsWorld* _world = NULL;

bool Game::init()
{
	if (!Layer::init())
	{
		return false;
	}

    
	_isPauseState = false;

    _isHaveAD=false;

	_showGuideInfo = false;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winsize = Director::sharedDirector()->getVisibleSize();
	//弹窗层..
	PopUp* popUp = PopUp::create();
	addChild(popUp, 100, "popup");
	__flyLayer = Layer::create();
	addChild(__flyLayer, 99, "fly");
	UMGDBRow row = data::Game::getInstance()->getUserGame();
	_preScore = row["score"].asInt();

	_shockisCD = false;

	_runningTime = 0.0;

	//播放背景音乐..
	cache::Music::getInstance()->playBGM(cache::Music::BGMName::GAME);

	_surplusTime = 61;
	_endlesssocre = 0;
	_endless = false;
	_useMagic = true;
	_isBombFish = false;
	_isStringFish = false;
	_timeItem = false;
	_firstgame = true;
	_isFullUmgame = false;

	_backMenuEndGame = false;

	//添加得分的ui..
	__scoreUI = ScoreUI::create();
	this->addChild(__scoreUI, 20);
	//添加道具ui..
	__itemUI = ItemUI::create(ItemUI::Type::GAMEUI);
	this->addChild(__itemUI, 20, "itemUI");
	if (data::Game::getInstance()->isUseRage())
	{
		__itemUI->_ragegray->setVisible(true);
	}
	else 
	{
		__itemUI->_ragegray->setVisible(false);
	}
	


#ifdef CANDY
	_itemrageui = Sprite::create("pic/ui/magic.png");
	_itembombui = Sprite::create("pic/ui/bomb.png");
	_itemshockui = Sprite::create("pic/ui/lightning.png");
#endif
#ifdef LONGBAO
	_itemrageui = Sprite::create("pic/longbao/ui/kuaizi.png");
	_itembombui = Sprite::create("pic/longbao/ui/dasuan.png");
	_itemshockui = Sprite::create("pic/longbao/ui/cuping.png");
#endif
	_itemshockui->setPosition(__itemUI->getPos(ItemUI::Icon::shock));
	_itembombui->setPosition(__itemUI->getPos(ItemUI::Icon::bomb));
	_itemrageui->setPosition(__itemUI->getPos(ItemUI::Icon::magic));

	this->addChild(_itemrageui);
	this->addChild(_itemshockui);
	this->addChild(_itembombui);

	//添加时间UI..
	__timeUI = TimeUI::create();
	__timeUI->setEndless(false);
	this->addChild(__timeUI, 20);
	//添加金币 UI..
	__goldUI = GoldUI::create();
	this->addChild(__goldUI, 20, "goldUI");
	//添加umgame..
	__umgame = UmGameUI::create();
	this->addChild(__umgame, 20);
	//添加游戏最后倒计时的显示文字..
	_label = LabelTTF::create("11", "Arial", 400);
	_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_label, 1);
	_label->setVisible(false);

	this->initWithUIValue();

	//添加技能冷却的图片..
	_pray1 = Sprite::create("pic/public/lightning_lq_gray.png");
	_pray2 = Sprite::create("pic/public/lightning_lq_gray.png");
	_rageCDPanel = Sprite::create("pic/public/magic_lq.png");
	_shockCDPanel = Sprite::create("pic/public/lightning_lq.png");
	_rageCDPanel->setVisible(false);
	_shockCDPanel->setVisible(false);
	_pray1->setVisible(false);
	_pray2->setVisible(false);
	_rageCDPanel->setVisible(false);
	_shockCDPanel->setVisible(false);



	this->addChild(_pray1, 21);
	this->addChild(_pray2, 21);
	this->addChild(_rageCDPanel, 21);
	this->addChild(_shockCDPanel, 21);

	_rageProgress = ProgressTimer::create(_rageCDPanel);
	this->addChild(_rageProgress, 22);
	_shockProgress = ProgressTimer::create(_shockCDPanel);
	this->addChild(_shockProgress, 22);
	_rageProgress->setVisible(false);
	_shockProgress->setVisible(false);

	// 读取系统存档的时间..
	UMGDBRow rows = data::Game::getInstance()->getUserGame();
	_time = rows["time"].asInt();


	//添加背景..
	_bg = Background::create();
	_bg->changeBgState(Background::NORMAL);
	this->addChild(_bg);



	//监听道具的数量..
	__itemUI->addListener(ItemUI::ITEM_CLICK, CC_CALLBACK_1(Game::useItem, this));

	//成功界面下一关的点击..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Success::NEXTLEVEL, CC_CALLBACK_1(Game::resumeInit, this));
	//暂停界面的放弃游戏..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Pause::GIVEUP, CC_CALLBACK_1(Game::resumeInit, this));
	//失败界面的重玩本关..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Fail::RESUMEGAME, CC_CALLBACK_1(Game::resumeInit, this));
	//成功界面的重玩本关..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Replay::RESUMEGAME, CC_CALLBACK_1(Game::resumeInit, this));
	//无尽模式的重玩本关..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Pause::RESUMEENDLESS, CC_CALLBACK_1(Game::resumeInit, this));
	//成功界面的重玩本关..
	Director::getInstance()->getEventDispatcher()->addCustomEventListener(Success::RESUMEGAME, CC_CALLBACK_1(Game::resumeInit, this));
	//游戏失败弹出清算界面..
	_gamefailListener = EventListenerCustom::create(TimeItem::FAILGAME, CC_CALLBACK_1(Game::gameFail, this));
	_eventDispatcher->addEventListenerWithFixedPriority(_gamefailListener, 1);


	auto endtomainlistener = [=](EventCustom*e)
	{
		_backMenuEndGame = true;
	};
	_eventDispatcher->addCustomEventListener(popup::QuitGame::ENDGAMETOMAIN, endtomainlistener);
	_eventDispatcher->addCustomEventListener(popup::Fail::ENDGAMETOMAIN, endtomainlistener);

	//_eventDispatcher->addCustomEventListener(data::Item::ITEM_CHANGE, CC_CALLBACK_1(Game::itemNumFunction, this));

	auto scorelistener = [=](EventCustom* e){

		int score = *(int*)e->getUserData();
		Node* block = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->CUSCORE);
		String* ns = String::createWithFormat("%d", score);
		const char* s = ns->getCString();
		TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
		la->setString(s);
	};
	_eventDispatcher->addCustomEventListener(data::Game::SCORE_CHANGE, scorelistener);

	auto stagelistener = [=](EventCustom* e){
		//得分..
		int stage = *(int*)e->getUserData();
		Node* block = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->LEVEL)->getChildByName("levelnum");
		String* ns = String::createWithFormat("%d", stage);
		const char* s = ns->getCString();
		TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
		la->setString(s);

		int totle = data::Game::getInstance()->getTotleScore();
		Node* blocktotle = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->TOTLESCORE)->getChildByName("totlenum");
		String* nstotle = String::createWithFormat("%d", totle);
		const char* stotle = nstotle->getCString();
		TextAtlas  *latotle = dynamic_cast<TextAtlas*>(blocktotle);
		latotle->setString(stotle);
	};
	_eventDispatcher->addCustomEventListener(data::Game::STAGE_CHANGE, stagelistener);

	_timeListener = EventListenerCustom::create(data::Game::TIME_CHANGE, [=](EventCustom* e){
		int time = *(int*)e->getUserData();
		this->showTime(time);
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_timeListener, 1);

	_menuPause = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->PAUSES);
	_menuPause->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Game::pauseClick, this)));
	_adblockui = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->ADBLOCK);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)

	_adblockui->setVisible(false);

#endif
  
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)	
    //判断是否有广告
//    if(data::User::getInstance()->getAdblock())
//    {
//        //
//       
//        
//    }
//    else
//    {
    
        _adblockui->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Game::adBlock,this)));
   // }
#endif

	auto backgamelistener = [=](EventCustom* e){
		gameResume();
	};
	_eventDispatcher->addCustomEventListener(Pause::BACK_YOUXI, backgamelistener);
	auto _timeItemlistener = [=](EventCustom* e){
		//在飞行的时间道具到了以后再继续游戏.....

		//gameResume();
		//setItemEnable(true);
		bool isfirst = data::User::getInstance()->getFirstTimeItem();
		if (isfirst == false)
		{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			umeng::MobClickCpp::use("timeItem", 1, 5);
#endif
			data::User::getInstance()->goldPlus(-5);
			//_time += 20;
			TimeFly* tf = TimeFly::create(20);
			tf->retain();
			if (__flyLayer->getChildrenCount() == 0)
				__flyLayer->addChild(tf);
			else
			{
				auto done = CallFuncN::create([=](Ref* ref){
					__flyLayer->addChild(tf);
				});
				this->runAction(Sequence::create(DelayTime::create(1.5), done, NULL));
			}
		}
		else 
		{
			data::User::getInstance()->setFirstTimeItem(false);
			addGrayLayer(GUIDETEXT::TIMEITEM, nullptr);
		}
	};
	_eventDispatcher->addCustomEventListener(TimeItem::TIMEPLUS, _timeItemlistener);

	auto pauselistener = [=](EventCustom* e){
	};
	_eventDispatcher->addCustomEventListener(QuitGame::FUNCPAUSE, pauselistener);

	auto _gamepauselistener = [=](EventCustom*e)
	{
		this->gamePause();
	};
	_eventDispatcher->addCustomEventListener(Game::GAMEPAUSE, _gamepauselistener);

	auto _gameresumelistener = [=](EventCustom*e)
	{
		if (popUp->getChildrenCount() == 1)
		{
			gameResume();
			gamePause();
			gameResume();
		}
	};
	_eventDispatcher->addCustomEventListener(ItemShop::GAMERESUME, _gameresumelistener);
	_eventDispatcher->addCustomEventListener(GoldShop::GAMESUME, _gameresumelistener);

	//侦听umgame 收集全的情况。。

	auto _umgameFulllistener = [=](EventCustom*e)
	{
		if (data::User::getInstance()->getFirstFullLetter()&&_showGuideInfo==false)
		{
			//暂停。。
			_showGuideInfo = true;
			auto done = CallFuncN::create([=](Ref* ref){
				addGrayLayer(FULLLETTER, nullptr);
				data::User::getInstance()->setFirstFullLetter(false);
				
			});
			this->runAction(Sequence::create(DelayTime::create(0.3), done, NULL));
		}
	};

	_eventDispatcher->addCustomEventListener(data::UmGame::LETTER_DONE, _umgameFulllistener);



	//加时间的操作
	auto timeplus = [=](EventCustom*e)
	{
		
		int time =*(int*)e->getUserData();
		if (time==20)
		{
			gameResume();
			setItemEnable(true);
		}
		_time = _time + time;
	};

	_eventDispatcher->addCustomEventListener(TimeFly::TIMEPLUS, timeplus);

	outKeyInit();

	//弹出金币商城游戏暂停的监听..
	_goldUIListener = EventListenerCustom::create(GoldUI::GAMEGOLDUI, [=](EventCustom* e){
		this->gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		popup->addTopPop(GoldShop::create());
	});

	_eventDispatcher->addEventListenerWithFixedPriority(_goldUIListener, 1);
	//弹出道具商城游戏暂停的监听..
	_itemUIListener = EventListenerCustom::create(ItemUI::GAMEITEMUI, [=](EventCustom* e){
		this->gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		popup->addTopPop(ItemShop::create());
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_itemUIListener, 1);

	_moveInListener = EventListenerCustom::create(Quit::MOVEIN, [=](EventCustom* e){
		gamePause();
		openQuit = true;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveInListener, 1);

	NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(Game::endLess), Gateway::ENDLESSGAME, NULL);

	_moveOutListener = EventListenerCustom::create(Quit::MOVEOUT, [=](EventCustom* e){
		gameResume();
		openQuit = false;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveOutListener, 1);


	_appgamepause = EventListenerCustom::create(AppDelegate::GAMEPAUSE, [=](EventCustom* e){
		if (popUp->getChildrenCount() == 0)
		{
			gamePause();
			PopUp* popup = (PopUp*)getChildByName("popup");
			//添加暂停界面..
			popup->addTopPop(Pause::create(_endless));
		}
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_appgamepause, 1);

	_appgameresume = EventListenerCustom::create(AppDelegate::GAMERESUME, [=](EventCustom* e){
		//gameResume();
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_appgameresume, 1);


	return true;
}
void Game::setScoreNum(int num)
{
	Node* block = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->CUSCORE);
	String* ns = String::createWithFormat("%d", num);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);
}
void Game::endLess(Ref*ref)
{
	//播放背景音乐..
	cache::Music::getInstance()->playBGM(cache::Music::BGMName::GATEWAY);
	//添加鱼层..
	fishes = GameEntity::createWithPhysicsWorld(_world);
	this->addChild(fishes, 2);
	_endless = true;
	__umgame->setVisible(false);
	__scoreUI->setEndLess(true);
	__timeUI->setEndless(true);
	_eventDispatcher->removeCustomEventListeners(data::Game::TIME_CHANGE);
	fishes->removeListener(GameEntity::RUNNING);
	fishes->endless(true);
	this->setScoreNum(0);
}
void Game::useItem(EventCustom* e)
{
	std::string str = *(std::string*)e->getUserData();
	int num = data::User::getInstance()->getGold();

	if ((str == "bomb"&&num < 2) || (str == "shock"&&num < 6) || (str == "magic"&&num < 10))
	{
		this->gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		if (data::User::getInstance()->getLibao())
			popup->addTopPop(GoldShop::create(true));
		else
			popup->addTopPop(GoldShop::create(false));
		return;
	}
	else
	{
		if (str == "magic"&&!fishes->isShining() && !fishes->isShock())
		{
			if (_endless)
			{
				if (fishes->rageisCD())
				{
					fishes->useRage();
					
					__itemUI->_text4->setVisible(false);
					__itemUI->_text->setVisible(false);
				}
				else
				{
					//判断是否显示道具说明界面。。
					if (data::User::getInstance()->getShowRage())
					{
						gamePause();
						PopUp* popup = (PopUp*)getChildByName("popup");
						//添加暂停界面..
						popup->addTopPop(ItemInfo::create(ItemInfo::ItemType::RAGE));
					}
					else
					{

						fishes->useRage();
						data::Item::getInstance()->use(data::Item::ITEM_RAGE_ID);
					}
				}
			}
			else
			{
				if (_useMagic&&!data::Game::getInstance()->isUseRage())
				{
					if (data::User::getInstance()->getShowRage())
					{
						gamePause();
						PopUp* popup = (PopUp*)getChildByName("popup");
						//添加暂停界面..
						popup->addTopPop(ItemInfo::create(ItemInfo::ItemType::RAGE));
						//popup->addTopPop(AdBlock::create());
					}
					else
					{
						data::Item::getInstance()->use(data::Item::ITEM_RAGE_ID);
						fishes->useRage();
						__itemUI->_ragegray->setVisible(true);
						__itemUI->_magicui->setVisible(false);
						data::Game::getInstance()->setUseRage(true);
						_useMagic = false;
					}

				}
				else
				{
					Size visibleSize = Director::getInstance()->getVisibleSize();
					__itemUI->_text4->setVisible(true);
				
					__itemUI->_text->setVisible(false);
					__itemUI->_text4->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(3), FadeOut::create(0.5), NULL));
					__itemUI->_text4->setPosition(Vec2(__itemUI->_bg->getPositionX() + __itemUI->_bg->getContentSize().width / 2, __itemUI->_text->getPositionY()));
				}
			}
		}
		if (str == "shock"&&!fishes->isShine() && !fishes->isRage())
		{

			if (fishes->shockisCD())
			{
				fishes->useShock();
			
				__itemUI->_text4->setVisible(false);
				__itemUI->_text->setVisible(false);
			
			}
			else
			{
				if (data::User::getInstance()->getShowShock())
				{
					//TODO
					//TODO..
					gamePause();
					PopUp* popup = (PopUp*)getChildByName("popup");
					//添加暂停界面..
					popup->addTopPop(ItemInfo::create(ItemInfo::ItemType::SHOCK));
				}
				else
				{
					fishes->useShock();
					data::Item::getInstance()->use(data::Item::ITEM_SHOCK_ID);
				}
			}
		}
		if (str == "bomb"&&!fishes->isRage())
		{
			if (data::User::getInstance()->getShowBomb())
			{
				//TODO
				//TODO..
				gamePause();
				PopUp* popup = (PopUp*)getChildByName("popup");
				//添加暂停界面..
				popup->addTopPop(ItemInfo::create(ItemInfo::ItemType::BOMB));

			}
			else
			{
				Size visibleSize = Director::getInstance()->getVisibleSize();
				__itemUI->_text->setVisible(true);
				
				__itemUI->_text4->setVisible(false);
				
				__itemUI->_text->runAction(Sequence::create(FadeIn::create(0.5), DelayTime::create(3), FadeOut::create(0.5), NULL));
				__itemUI->_text->setPosition(Vec2(__itemUI->_bg->getPositionX() + __itemUI->_bg->getContentSize().width / 2, __itemUI->_text->getPositionY()));

			}
		}
	}
}
void Game::resumeInit(EventCustom* e)
{
	// 	UMGDBRow row = data::Game::getInstance()->getUserGame();
	// 	_preScore = row["score"].asInt();
	setItemEnable(true);
	_shockisCD = false;
	_label->setVisible(false);
	_menuPause->setEnabled(true);
	__itemUI->_ragegray->setVisible(false);
	__itemUI->_magicui->setVisible(true);
	std::string str = *(std::string*)e->getUserData();
	if (str == "giveup")
	{
		_showGuideInfo = false;
		_useMagic = true;
		_bg->randBg();
		data::Game::getInstance()->setUseRage(false);
		fishes->setGameFirst();

		_pray1->setVisible(false);
		_pray2->setVisible(false);
		_shockProgress->setVisible(false);
		__itemUI->_shockmenu->setVisible(true);
		_shockCDPanel->setVisible(false);
	}
	else if (str == "next")
	{
		data::Game::getInstance()->setUseRage(false);
		_showGuideInfo = false;
		_useMagic = true;
		_bg->randBg();
		fishes->setGameFirst();
		if (fishes)  fishes->reset();
		_time = 61;
		_pray1->setVisible(false);
		_pray2->setVisible(false);
		_shockProgress->setVisible(false);
		__itemUI->_shockmenu->setVisible(true);
		_shockCDPanel->setVisible(false);
		this->initWithUIValue();
		UMGDBRow row = data::Game::getInstance()->getUserGame();
		int stagenum = row["stage"].asInt();
		String*ns = String::createWithFormat("%d", stagenum);
		const char *level = ns->getCString();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		umeng::MobClickCpp::startLevel(level);
#endif
	}
	else if (str == "reback")
	{

//        CCLOG("_preScore = %d",_preScore);
        int totle = data::Game::getInstance()->getTotleScore();
//        CCLOG("totle = %d",totle);

		if (data::User::getInstance()->getFirstFail() && _preScore < totle)
		{
			auto dones = CallFuncN::create([=](Ref* ref){
				addGrayLayer(GUIDETEXT::FAIL, nullptr);
				data::User::getInstance()->setFirstFail(false);
			});
			this->runAction(Sequence::create(DelayTime::create(0.3), dones, NULL));
		}
		gameResume();
		// 得到上一关的数据  ..
		_useMagic = true;
		_timeItem = false;
		_firstgame = true;
		data::Game::getInstance()->setUseRage(false);
		_bg->randBg();
		fishes->setGameFirst();
		if (fishes)  fishes->reset();
		_time = 61;
		//为得分  关卡  目标分数  赋初值  时间..
		UMGDBRow row = data::Game::getInstance()->getUserGame();
		int stagenum = row["stage"].asInt();
		if (stagenum == 1)
		{
			data::Game::getInstance()->setScore(0);
			data::Game::getInstance()->setStage(1);
			data::Game::getInstance()->setTime(61);
			data::User::getInstance()->setFirstLevel(false);
			_preScore = 0;
		}
		else
		{
			UMGDBRow row = data::Game::getInstance()->getUserGame(-1);
		}
		_pray1->setVisible(false);
		_pray2->setVisible(false);
		_shockProgress->setVisible(false);
		__itemUI->_shockmenu->setVisible(true);
		_shockCDPanel->setVisible(false);
		data::Game::getInstance()->setTime(61);

		String*ns = String::createWithFormat("%d", stagenum);
		const char *level = ns->getCString();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		umeng::MobClickCpp::startLevel(level);
#endif
	}
	else if (str == "endlessresume")
	{
		_showGuideInfo = false;
		gameResume();
		_useMagic = true;
		_firstgame = true;
		fishes->setGameFirst();
		_bg->randBg();
		if (fishes) fishes->reset();
		_endlesssocre = 0;
		this->setScoreNum(0);
		_pray1->setVisible(false);
		_pray2->setVisible(false);
		_rageProgress->setVisible(false);
		__itemUI->_magicmenu->setVisible(true);
		_rageCDPanel->setVisible(false);
		////////////////////////////////////////
		_shockProgress->setVisible(false);
		__itemUI->_shockmenu->setVisible(true);
		_shockCDPanel->setVisible(false);
	}
}
void Game::setScore(EventCustom* e)
{
	std::vector<Fish*> vscore = *(std::vector<Fish*>*)e->getUserData();

	int nums = vscore.size();
	if (nums <= 0)
		return;
	int score = 0;
	int line = 0;
	int round = 0;
	int bomb = 0;
	int magic = 0;
	int capture = 0;

	for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
	{
		if ((*it)->_award == "")
		{
			_isStringFish = false;
		}
		else
		{
			_isStringFish = true;
			if ((*it)->_arrest != Fish::Arrest::RAGE)
			{
				std::string str = (*it)->_award;
				__umgame->getLetter(str);
			}
		}
		switch ((*it)->_arrest)
		{
		case Fish::Arrest::LINK:
			line++;
			break;
		case Fish::Arrest::ROUND:
			round++;
			break;
		case Fish::Arrest::BOMB:
			bomb++;
			break;
		case Fish::Arrest::RAGE:
			magic++;
		case Fish::Arrest::CAPTURE:
			if ((*it)->_type == cache::Fish::FishName::DISCO)
			{
				_isBombFish = true;
			}
			capture++;
			break;
		default:
			break;
		}

	}
	if (line != 0)
	{
		score = line * 2;
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 2;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::LINK)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}
	else if (bomb)
	{
		score = bomb * 3;
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 2;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::BOMB)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}
	else if (round&&_isBombFish)
	{
		score = 2 * (4 * round + (capture - 1)*(capture - 1)) + 50;
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = capture * 2;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::CAPTURE)
			{
				popFly(time, (*it)->getPosition());
			}
		}
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 8;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::ROUND)
			{
				popFly(time, (*it)->getPosition());
			}
		}
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 50;
			if ((*it)->_type == cache::Fish::FishName::DISCO)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}
	else if (round&&!_isBombFish)
	{
		score = 4 * round + capture*capture;
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 4;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::ROUND)
			{
				popFly(time, (*it)->getPosition());
			}
		}
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = capture;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::CAPTURE)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}
	else if (magic)
	{
		score = 2 * magic;
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 2;
			if (fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::RAGE)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}
	if (fishes->isShining())
	{
		score = score * 3;
	}
	_isBombFish = false;
	int num = _preScore / 100;

	int tenbit = _preScore - 100 * num;

	if (tenbit + score >= 100)
	{
		if (data::User::getInstance()->getFirstThress() && !_endless&&_showGuideInfo==false)
		{
			_showGuideInfo = true;
			CallFunc*func = CallFunc::create([=](){
				addGrayLayer(GUIDETEXT::THRESS, nullptr);
				data::User::getInstance()->setFirstThress(false);
			});
			this->runAction(Sequence::create(DelayTime::create(0.3), func, NULL));
		}
		else
		{
			Size size = Director::getInstance()->getVisibleSize();
			
			if (!_endless)
			{
				TimeFly* tf = TimeFly::create(3);
				tf->retain();
				if (__flyLayer->getChildrenCount() == 0)
					__flyLayer->addChild(tf);
				else
				{
					auto done = CallFuncN::create([=](Ref* ref){
						__flyLayer->addChild(tf);

					});
					this->runAction(Sequence::create(DelayTime::create(1.5), done, NULL));
				}
			}
		}
	}
	//气泡得分..
	_preScore += score;
	if (_endless)
	{
		_endlesssocre += score;
		__scoreUI->changeScore(_endlesssocre);
	}
	else
	{
		__scoreUI->changeScore(_preScore);
		//data::Game::getInstance()->scorePlus(score);
	}
}

void Game::pauseClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		//添加暂停界面..
		popup->addTopPop(Pause::create(_endless));
	}
}
void Game::adBlock(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		//添加暂停界面..
		popup->addTopPop(AdBlock::create());
	}
}
void Game::gameFail(EventCustom*e)
{
	cache::Music::getInstance()->playEffect(cache::Music::EffectName::GAMEOVER);
	PopUp* popup = (PopUp*)getChildByName("popup");
	popup->addTopPop(Fail::create());
	fishes->gameOver();
}
Scene* Game::createScene()
{
	Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
//    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _world = scene->getPhysicsWorld();
	Layer* layer = Game::create();
	scene->addChild(layer);
//    CCLOG("创建物理世界");
	return scene;
}
void Game::outKeyInit(){

	auto listener = EventListenerKeyboard::create();

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
		if (keyCode == EventKeyboard::KeyCode::KEY_BACK){
			PopUp* popup = (PopUp*)getChildByName("popup");
			if (!popup->closeTopPop())
			{
				if (!openQuit)
				{
					addChild(Quit::create(), 1000, "quit");
				}
				else
				{

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
					umeng::MobClickCpp::end();
#endif			

					Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					exit(0);
#endif
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}
void Game::gamePause()
{
	cache::Music::getInstance()->pauseBGM();
	fishes->pause();
}
void Game::gameResume()
{
	cache::Music::getInstance()->resumeBGM();
	fishes->resume();
}
Game::~Game()
{
	_eventDispatcher->removeEventListener(_moveInListener);
	_eventDispatcher->removeEventListener(_moveOutListener);
	_eventDispatcher->removeEventListener(_goldUIListener);
	_eventDispatcher->removeEventListener(_itemUIListener);
	_eventDispatcher->removeEventListener(_gamefailListener);
	_eventDispatcher->removeEventListener(_timeListener);
	_eventDispatcher->removeCustomEventListeners(Game::GAMEPAUSE);
	_eventDispatcher->removeCustomEventListeners(ItemShop::GAMERESUME);
	_eventDispatcher->removeCustomEventListeners(GoldShop::GAMESUME);
	_eventDispatcher->removeCustomEventListeners(data::UmGame::LETTER_CHANGE);
	_eventDispatcher->removeCustomEventListeners(data::UmGame::LETTER_DONE);
	_eventDispatcher->removeCustomEventListeners(TimeItem::TIMEPLUS);
	_eventDispatcher->removeCustomEventListeners(Fail::RESUMEGAME);
	_eventDispatcher->removeCustomEventListeners(Success::NEXTLEVEL);
	_eventDispatcher->removeCustomEventListeners(Success::RESUMEGAME);
	_eventDispatcher->removeCustomEventListeners(QuitGame::FUNCPAUSE);
	_eventDispatcher->removeCustomEventListeners(Pause::GIVEUP);
	_eventDispatcher->removeCustomEventListeners(data::Game::SCORE_CHANGE);
	_eventDispatcher->removeCustomEventListeners(Replay::RESUMEGAME);
	_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
	_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
	_eventDispatcher->removeCustomEventListeners(popup::Pause::RESUMEENDLESS);
	_eventDispatcher->removeCustomEventListeners(popup::QuitGame::ENDGAMETOMAIN);
	_eventDispatcher->removeCustomEventListeners(popup::Pause::BACK_YOUXI);
	_eventDispatcher->removeCustomEventListeners(popup::Fail::ENDGAMETOMAIN);
	_eventDispatcher->removeCustomEventListeners(GameEntity::DOUBLE_CLICKED);
	NotificationCenter::getInstance()->removeObserver(this, Gateway::ENDLESSGAME);
	_eventDispatcher->removeCustomEventListeners(AppDelegate::GAMEPAUSE);
	_eventDispatcher->removeCustomEventListeners(AppDelegate::GAMERESUME);
	_eventDispatcher->removeCustomEventListeners(GameEntity::SHING_FISH);
	_eventDispatcher->removeCustomEventListeners(GameEntity::LETTER_FISH);
	_eventDispatcher->removeCustomEventListeners(GameEntity::RUNNINGGAME);
	_eventDispatcher->removeCustomEventListeners(ItemInfo::USEITEM_BACK_GAME);
	_eventDispatcher->removeCustomEventListeners(TimeFly::TIMEPLUS);
	_eventDispatcher->removeCustomEventListeners(ItemUI::ITEM_CLICK);
	//判断是返回主菜单的方式..

	if (_backMenuEndGame)
	{
		data::Game::getInstance()->setTime(61);
		data::Game::getInstance()->setScore(0);
	}
	else if (!_endless)
	{
		data::Game::getInstance()->setTime(_surplusTime);
		data::Game::getInstance()->setScore(_preScore);
	}
    if(_isHaveAD)
    {
        //this->hiddenBannerCallback();
        /**
         *  代码注释 安卓不需要 谢涛
         *
         *  @param CC_TARGET_PLATFORM!
         *
         *  @return
         */
//#if (CC_TARGET_PLATFORM!=CC_PLATFORM_IOS)
//
//         AdsmogoBanner::sharedBanner()->releaseBanner();
//
//#endif        
    }
        
}
void Game::initWithUIValue()
{
	//为金币赋初始值..
	std::string goldstr = Value(data::User::getInstance()->getGold()).asString();
	TextAtlas  *gold = dynamic_cast<TextAtlas*>(__goldUI->_num);
	gold->setString(goldstr);
	//为道具赋初始值..
	// 	int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	// 	int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	// 	int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
	// 	if (magicnum >= 999) magicnum = 999;
	// 	if (shocknum >= 999) shocknum = 999;
	// 	if (bombnum >= 999) bombnum = 999;
	// 	std::string magicstr = std::to_string(magicnum);
	// 	std::string shockstr = std::to_string(shocknum);
	// 	std::string bombstr = std::to_string(bombnum);
	// 	TextAtlas  *magic = dynamic_cast<TextAtlas*>(__itemUI->_magic);
	// 	TextAtlas  *bomb = dynamic_cast<TextAtlas*>(__itemUI->_bomb);
	// 	TextAtlas  *shock = dynamic_cast<TextAtlas*>(__itemUI->_shock);
	// 
	// 	magic->setString(magicstr);
	// 	bomb->setString(bombstr);
	// 	shock->setString(shockstr);

	//为得分  关卡  目标分数  赋初值  时间..
	UMGDBRow row = data::Game::getInstance()->getUserGame();
	int stagenum = row["stage"].asInt();
	int scorenum = row["score"].asInt();
	int timenum = row["time"].asInt();

	int targetnum = data::Game::getInstance()->getTotleScore();
	std::string stagestr = Value(stagenum).asString();
	std::string scorestr = Value(scorenum).asString();
	std::string timestr = Value(timenum).asString();
	std::string targetstr = Value(targetnum).asString();
	Node* scoreblock = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->CUSCORE);
	Node* targetScoreblock = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->TOTLESCORE)->getChildByName("totlenum");
	Node* levelblock = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->LEVEL)->getChildByName("levelnum");
	TextAtlas  *score = dynamic_cast<TextAtlas*>(scoreblock);
	TextAtlas  *targetScore = dynamic_cast<TextAtlas*>(targetScoreblock);
	TextAtlas  *level = dynamic_cast<TextAtlas*>(levelblock);
	score->setString(scorestr);
	targetScore->setString(targetstr);
	level->setString(stagestr);
	__scoreUI->fixPosition();
}
void Game::itemNumFunction(EventCustom*e)
{
	data::UserItemInfo userItem = *(data::UserItemInfo*)e->getUserData();
	std::stringstream str;
	str << userItem.num;
	Node* block;
	int num = atoi(str.str().c_str());
	int length = num / 10;

	int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);

	int magiclength = magicnum / 10;
	int shocklength = shocknum / 10;
	int bomblength = bombnum / 10;

	if (magicnum >= 999) magicnum = 999;
	if (shocknum >= 999) shocknum = 999;
	if (bombnum >= 999) bombnum = 999;
	__itemUI->setGray();
	__itemUI->setLength(shocklength, __itemUI->ITESHOCK);
	__itemUI->setLength(bomblength, __itemUI->ITEMBOMB);
	__itemUI->setLength(magiclength, __itemUI->ITEMMAGIC);
	__itemUI->setBgSize();

	switch (userItem.id)
	{
	case data::Item::ITEM_SHOCK_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITESHOCK)->getChildByName("shocknum");
		break;
	case data::Item::ITEM_BOMB_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMBOMB)->getChildByName("bombnum");
		break;
	case data::Item::ITEM_RAGE_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMMAGIC)->getChildByName("magicnum");
		break;
	default:
		break;
	}
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	int itemnum = atoi(str.str().c_str());
	if (itemnum >= 999)
	{
		itemnum = 999;
	}
	la->setString(Value(itemnum).asString());
	str.clear();
}

void Game::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	UMGDBRow row = data::Game::getInstance()->getUserGame();
	int stagenum = row["stage"].asInt();
	String*ns = String::createWithFormat("%d", stagenum);
	const char *level = ns->getCString();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	umeng::MobClickCpp::startLevel(level);
#endif
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winsize = Director::sharedDirector()->getVisibleSize();
	if (!_endless)//添加鱼层..
	{
		//添加鱼层..
		fishes = GameEntity::createWithPhysicsWorld(_world);
		this->addChild(fishes, 2);
	}
	fishes->addListener(GameEntity::DOUBLE_CLICKED, [=](EventCustom* e){

		this->gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");

		if (data::User::getInstance()->getLibao())
			popup->addTopPop(GoldShop::create(true));
		else
			popup->addTopPop(GoldShop::create(false));

	});
	auto useitemlistener = [=](EventCustom* e){
		std::string str = *(std::string*)e->getUserData();
		if (str == "shock")
		{
			fishes->useShock();
			data::Item::getInstance()->use(data::Item::ITEM_SHOCK_ID);
		}
		else if (str == "magic")
		{
			fishes->useRage();
			data::Item::getInstance()->use(data::Item::ITEM_RAGE_ID);
			if (!_endless)
			{
				__itemUI->_ragegray->setVisible(true);
				__itemUI->_magicui->setVisible(false);
				data::Game::getInstance()->setUseRage(true);
				_useMagic = false;
			}
		}
	};
	_eventDispatcher->addCustomEventListener(ItemInfo::USEITEM_BACK_GAME, useitemlistener);
	//根据连接的鱼设置分数..
	fishes->addListener(GameEntity::FISH_CATCHED, CC_CALLBACK_1(Game::setScore, this));
	if (!_endless)
	{
		fishes->addListener(GameEntity::RUNNING, [=](EventCustom* e)
		{
            
            if (data::User::getInstance()->getAdblock()) {
                _adblockui->setVisible(false);
            }
			_runningTime = *(double*)e->getUserData();
			_surplusTime = _time - _runningTime;
			this->showTime(_surplusTime);
            /**
             *  注释 安卓不需要 谢涛注释
             */
//#if (CC_TARGET_PLATFORM!=CC_PLATFORM_IOS)
//            if (!data::User::getInstance()->getAdblock()) {
//                if (_runningTime>0&&(int)_runningTime%30==0) {
//                    if(_isHaveAD)
//                    {
//                        AdsmogoBanner::sharedBanner()->showBanner();
//                    }
//                    else
//                    {
//                        this->menuBannerCallback();
//                        _isHaveAD=true;
//                    }
//                }
//                if (_runningTime>0&&(int)_runningTime%40==0) {
//                    AdsmogoBanner::sharedBanner()->hidenBanner();
//                }  
//            }
//            else{
//                AdsmogoBanner::sharedBanner()->releaseBanner();
//            }
//#endif
			if (_surplusTime <= 0)
			{
				setItemEnable(false);
				_menuPause->setEnabled(false);
				_label->setVisible(false);
				int totle = data::Game::getInstance()->getTotleScore();
				//在游戏结束的时候（及时间为0的时候）道具是不可使用状态.......
				

				if (_preScore >= totle)
				{
					UMGDBRow row = data::Game::getInstance()->getUserGame();
					int stagenum = row["stage"].asInt();
					if (stagenum == 1)
					{
						data::User::getInstance()->setFirstLevel(false);
					}
					String*ns = String::createWithFormat("%d", stagenum);
					const char *level = ns->getCString();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
					umeng::MobClickCpp::finishLevel(level);
#endif
					fishes->gameOver();
					data::Game::getInstance()->setScore(_preScore);
					auto done = CallFuncN::create([=](Ref* ref)
					{
						data::Game::getInstance()->setUseTimeItem(false);
						data::Game::getInstance()->stageClear();
						_bg->changeBgState(Background::NORMAL);
						cache::Music::getInstance()->playEffect(cache::Music::EffectName::GAMEWIN);
						PopUp* popup = (PopUp*)getChildByName("popup");
						_label->setVisible(false);
						popup->addTopPop(Success::create());
						_menuPause->setEnabled(true);
						fishes->gameOver();
#ifdef GIFT_POPUE_VETSION
                        time_t now = time(0);
                        tm *timeData = localtime(&now);
                        
                        int weekType = timeData->tm_wday;
                        weekType = (((int)weekType)?weekType:7);
                        
                        int openWeek = UserDefault::getInstance()->getIntegerForKey("open_specialoffer");
                        if (openWeek != weekType)
                        {
                            //                        popup->addTopPop(SpecialOfferLayer::createWithType(SpecialOffersType));
                            SpecialOfferLayer *specLayer = SpecialOfferLayer::createWithType(SpecialOffersType);
                            specLayer->m_bNotPushToColse = true;
                            this->addChild(specLayer,100);
                        }
                        

#endif
                        
//

					});
					this->runAction(Sequence::create(DelayTime::create(1.2), done, NULL));
				}
				else
				{
					if (!_timeItem&&_firstgame&&!data::Game::getInstance()->isUseTimeItem())
					{
						gamePause();
						PopUp* popup = (PopUp*)getChildByName("popup");
						popup->addTopPop(TimeItem::create());
						_menuPause->setEnabled(true);
						_timeItem = true;
					}
					else
					{
						UMGDBRow row = data::Game::getInstance()->getUserGame();
						int stagenum = row["stage"].asInt();
						String*ns = String::createWithFormat("%d", stagenum);
						const char *level = ns->getCString();
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
						umeng::MobClickCpp::failLevel(level);
#endif
						fishes->gameOver();
						auto done = CallFuncN::create([=](Ref* ref){
							data::Game::getInstance()->setUseTimeItem(false);
							cache::Music::getInstance()->playEffect(cache::Music::EffectName::GAMEOVER);
							PopUp* popup = (PopUp*)getChildByName("popup");
							//
							_menuPause->setEnabled(true);
							popup->addTopPop(Fail::create());
							_label->setVisible(false);
							_bg->changeBgState(Background::NORMAL);
							fishes->gameOver();
						});
						this->runAction(Sequence::create(DelayTime::create(1.2), done, NULL));
					}
				}
			}
			else if (_surplusTime <= 10)
			{
				if (fishes->isRage() || fishes->isShine() || fishes->isShock())
					CCLOG("fsdf");
				else
					Countdown(_surplusTime);
			}
	});
}
	else
	{
        if (data::User::getInstance()->getAdblock()) {
            _adblockui->setVisible(false);
        }
		fishes->addListener(GameEntity::RUNNING, [=](EventCustom* e){
			_runningTime = *(double*)e->getUserData();
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
            if (!data::User::getInstance()->getAdblock()) {
                if (_runningTime>0&&(int)_runningTime%30==0) {
                    if(_isHaveAD)
                    {
                        AdsmogoBanner::sharedBanner()->showBanner();
                    }
                    else
                    {
                        this->menuBannerCallback();
                        _isHaveAD=true;
                    }
                }
                if (_runningTime>0&&(int)_runningTime%40==0) {
                    AdsmogoBanner::sharedBanner()->hidenBanner();
                }
                
            }
            else{
                AdsmogoBanner::sharedBanner()->releaseBanner();
            }
#endif
			if (fishes->isRage())
			{
				Countdown(fishes->rageCountTime());
				__itemUI->_magicmenu->setVisible(false);
				_pray1->setVisible(true);
				_pray1->setPosition(__itemUI->getPos(ItemUI::Icon::magic));
				_rageProgress->setVisible(true);
				_rageProgress->setPosition(_pray1->getPosition());
				_rageProgress->setType(ProgressTimer::Type::RADIAL);
			}
			_rageProgress->setPercentage(fishes->rageCDTime());
			if (fishes->rageCDTime() >= 100)
			{
				__itemUI->_magicmenu->setVisible(true);
				_pray1->setVisible(false);
				_rageProgress->setVisible(false);
				_rageCDPanel->setVisible(false);
				__itemUI->_magicui->setVisible(true);
				__itemUI->_ragegray->setVisible(false);

			}


	});
	}
	fishes->addListener(GameEntity::RUNNINGGAME, [=](EventCustom*e)
	{
		if (fishes->isShock())
		{
			Countdown(fishes->shockCountTime());
			__itemUI->_shockmenu->setVisible(false);
			_pray2->setVisible(true);
			_pray2->setPosition(__itemUI->getPos(ItemUI::Icon::shock));
			_shockProgress->setVisible(true);
			_shockProgress->setPosition(_pray2->getPosition());
			_shockProgress->setType(ProgressTimer::Type::RADIAL);
		}
		_shockProgress->setPercentage(fishes->shockCDTime());
		if (fishes->shockCDTime() >= 100)
		{
			__itemUI->_shockmenu->setVisible(true);
			_pray2->setVisible(false);
			_shockProgress->setVisible(false);
			_shockCDPanel->setVisible(false);
			_shockisCD = false;
			//__itemUI->_shockui->setPosition(_itemPoint);

		}
		else
		{
			_shockisCD = true;
		}
		if (fishes->isShine())
		{
			Countdown(fishes->shingCountTime());
		}
		if (fishes->isRage())
		{
			Countdown(fishes->rageCountTime());
		}
	});
	fishes->addListener(GameEntity::ITEM_START, [=](EventCustom* e){
		GameEntity::ItemType type = *(GameEntity::ItemType*)e->getUserData();
		if (type == GameEntity::ItemType::RAGE)
		{
			Sprite*sprite = Sprite::createWithTexture(_bg->_bg->getTexture());
			this->addChild(sprite);
			sprite->runAction(FadeOut::create(1));
			Size winsize = Director::sharedDirector()->getVisibleSize();
			sprite->setPosition(ccp(winsize.width / 2, winsize.height / 2));
			float scaleX = visibleSize.width / sprite->getContentSize().width;
			float scaleY = visibleSize.height / sprite->getContentSize().height;
			float scale = scaleX > scaleY ? scaleX : scaleY;
			sprite->setScale(scale);
			_bg->changeBgState(Background::RAGE);
		}
		else if (type == GameEntity::ItemType::SHOCK)
		{

			Sprite*sprite = Sprite::createWithTexture(_bg->_bg->getTexture());
			this->addChild(sprite);

			sprite->runAction(FadeOut::create(1));

			Size winsize = Director::sharedDirector()->getVisibleSize();
			sprite->setPosition(ccp(winsize.width / 2, winsize.height / 2));
			float scaleX = visibleSize.width / sprite->getContentSize().width;
			float scaleY = visibleSize.height / sprite->getContentSize().height;
			float scale = scaleX > scaleY ? scaleX : scaleY;
			sprite->setScale(scale);
			_bg->changeBgState(Background::SHOCK);
		}
	});
	fishes->addListener(GameEntity::ITEM_FINISH, [=](EventCustom* e){
		GameEntity::ItemType type = *(GameEntity::ItemType*)e->getUserData();
		_label->setVisible(false);
		//判断是否是闪光时间 。。。。
		if (fishes->getIsShing())
		{

		}
		else
		{
			_bg->changeBgState(Background::NORMAL);
		}
		
	});
	fishes->addListener(GameEntity::SHINE_START, [=](EventCustom* e){
		Sprite*sprite = Sprite::createWithTexture(_bg->_bg->getTexture());
		this->addChild(sprite);
		sprite->runAction(FadeOut::create(1));
		Size winsize = Director::sharedDirector()->getVisibleSize();
		sprite->setPosition(ccp(winsize.width / 2, winsize.height / 2));
		float scaleX = visibleSize.width / sprite->getContentSize().width;
		float scaleY = visibleSize.height / sprite->getContentSize().height;
		float scale = scaleX > scaleY ? scaleX : scaleY;
		sprite->setScale(scale);

		_bg->changeBgState(Background::SHING);
	});
	fishes->addListener(GameEntity::SHINE_FINISH, [=](EventCustom* e){
		_bg->changeBgState(Background::NORMAL);
		_label->setVisible(false);
	});
	fishes->addListener(GameEntity::SHING_FISH, [=](EventCustom*e){
		if (data::User::getInstance()->getFirstShing() && _shockisCD == false&&_showGuideInfo==false)
		{
			CallFunc*func = CallFunc::create([=](){
				addGrayLayer(GUIDETEXT::SHING, fishes->getShing());
				_showGuideInfo = true;
				data::User::getInstance()->setFirstShing(false);
			});
			this->runAction(Sequence::create(DelayTime::create(1), func, NULL));
		}

	});
	fishes->addListener(GameEntity::LETTER_FISH, [=](EventCustom*e){
		if (data::User::getInstance()->getFirstLetter()&&_showGuideInfo==false)
		{
			CallFunc*func = CallFunc::create([=](){
				addGrayLayer(GUIDETEXT::LETTER, fishes->getLetter());
				data::User::getInstance()->setFirstLetter(false);
			});
			this->runAction(Sequence::create(DelayTime::create(1), func, NULL));

		}
	});
	//TODO  侦听金币收集全的情况。。

#ifdef LONGBAO
	//开始游戏的背景的缓慢出现..
	Sprite*bg = Sprite::create("map/map8.png");
	bg->setPosition(ccp(winsize.width / 2, winsize.height / 2));
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setScale(scale);
	this->addChild(bg);
	bg->setOpacity(0);
	bg->runAction(FadeIn::create(1));
#endif
}
void Game::showTime(double time)
{
	int minute = time / 60;
	int second = time - minute * 60;

	Node*minutezero = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->MINUTEZERO);
	Node*secondzero = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->SECONDZERO);

	if (minute / 10 == 0)
	{
		minutezero->setVisible(true);
	}
	else
	{
		minutezero->setVisible(false);
	}
	if (second / 10 == 0)
	{
		secondzero->setVisible(true);
	}
	else
	{
		secondzero->setVisible(false);
	}
	Node* blockMIN = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->MINUTE);
	String* nsMIN = String::createWithFormat("%d", minute);
	const char* smin = nsMIN->getCString();
	TextAtlas  *lamin = dynamic_cast<TextAtlas*>(blockMIN);
	lamin->setString(smin);
	Node* block = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->SECOND);
	String* ns = String::createWithFormat("%d", second);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);
}
void Game::Countdown(int time)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	String* ns = String::createWithFormat("%d", time);
	_label->setVisible(true);
#ifdef LONGBAO
	_label->setColor(ccc3(0, 0, 0));
#endif
#ifdef CANDY
	_label->setColor(ccc3(255, 255, 255));
#endif
	_label->setOpacity(80);
	if (time == 10 || (fishes->isShock() && time == 5))
	{
		if (ns->getCString() != _label->getString())
		{
			_label->setScale(1);
			_label->setString(ns->getCString());
			_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height + 300));
			_label->setVisible(true);
			_label->runAction(EaseElasticOut::create(MoveTo::create(0.3, Vec2(visibleSize.width / 2, visibleSize.height / 2))));
		}
	}
	if (ns->getCString() != _label->getString())
	{
		_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
		_label->setString(ns->getCString());
		Sequence*seq = Sequence::create(EaseElasticOut::create(ScaleTo::create(0.6, 1.2, 1.2)), ScaleBy::create(0.4, 0.6, 0.6), EaseElasticOut::create(ScaleTo::create(0.2, 0.6, 0.6)), NULL);
		_label->runAction(seq);
	}
}
void Game::popFly(int score, cocos2d::Vec2 pos)
{
	int largenum = score / 10;
	int smallnum = score % 10;
	if (smallnum != 0)
	{
		auto done = CallFuncN::create([=](Ref* ref){
			PopFly* fly = PopFly::create(pos, __scoreUI->getScorePosition());
			addChild(fly, 98);
		});
		this->runAction(Repeat::create(Sequence::create(done, DelayTime::create(0.1f), NULL), smallnum));
	}
	if (largenum != 0)
	{
		auto done = CallFuncN::create([=](Ref* ref){
			PopFly* fly = PopFly::create(pos, __scoreUI->getScorePosition(), true);
			addChild(fly, 98);
		});
		this->runAction(Repeat::create(Sequence::create(done, DelayTime::create(0.1f), NULL), largenum));
	}
}
void Game::addGrayLayer(GUIDETEXT guide, Node *node)
{
	Sprite* sprite = NULL;
	Size visibleSize = Director::getInstance()->getVisibleSize();
#ifdef LONGBAO
	std::string str = "csb/guide/guideingame.csb";
#endif
#ifdef CANDY
	std::string str = "csb/guide/guideingameca.csb";
#endif
	Node*rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
	cocostudio::timeline::ActionTimeline* action = CSLoader::createTimeline(str);
	rootNode->runAction(action);
	this->addChild(rootNode, 30, 20);
	rootNode->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	__umgame = UmGameUI::create();
	this->addChild(__umgame, 20);
	Widget*umgame = __umgame->_umgame->clone();

	switch (guide)
	{
	case Game::THRESS:
		action->gotoFrameAndPlay(0, 0, true);
		sprite = Sprite::create("pic/ui/3s.png");
		this->addChild(sprite, 22, 21);
		sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 220));
		break;
	case Game::SHING:
		action->gotoFrameAndPlay(5, 5, true);
		break;
	case Game::LETTER:
		action->gotoFrameAndPlay(15, 15, true);
		break;
	case Game::FULLLETTER:
		action->gotoFrameAndPlay(20, 20, true);
		break;
	case Game::TIMEITEM:
		action->gotoFrameAndPlay(0, 0, true);
		sprite = Sprite::create("pic/ui/20ss.png");
		this->addChild(sprite, 22, 22);
		sprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 320));
		action->gotoFrameAndPlay(25, 25, true);
		break;
	case Game::FAIL:
		action->gotoFrameAndPlay(35, 35, true);
		break;
	case Game::GUIDESHOCK:
		action->gotoFrameAndPlay(10, 10, true);
		break;
	case Game::GUIDEBOMB:
		action->gotoFrameAndPlay(40, 40, true);
		break;
	case Game::GUIDERAGE:
		action->gotoFrameAndPlay(30, 30, true);
		break;
	default:
		break;
	}

	Vec2 midPoint = Vec2(visibleSize.width / 2, visibleSize.height / 2);
	gamePause();
	/**  场景背景图片  */

	ImageView* bg = ImageView::create("map/mask2048.png");
	bg->setOpacity(0);
	FadeTo* fade = FadeTo::create(0.5f, 255 * 0);
	bg->runAction(fade);
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setPosition(midPoint);
	bg->setScale(scale);
	bg->setTouchEnabled(true);
	bg->setSwallowTouches(true);
	addChild(bg, 210);
/*	ClippingNode *clip = ClippingNode::create();*/

	if (guide == THRESS || guide == TIMEITEM || guide == GUIDETEXT::FAIL||guide==FULLLETTER)
	{
		Node* next = Main::seekNodeByName(rootNode, "next");
		float flash = 0.5f;
		Sequence* seq = Sequence::create(FadeOut::create(flash), FadeIn::create(flash), NULL);
		next->runAction(RepeatForever::create(seq));
		bg->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Game::dropGrayLayer, this, (GUIDETEXT)guide)));
        if (guide == TIMEITEM) {
            this->gamePause();
        }
	}
	else if (guide == SHING || guide == LETTER)
	{
		Node* next = Main::seekNodeByName(rootNode, "next");
		float flash = 0.5f;
		Sequence* seq = Sequence::create(FadeOut::create(flash), FadeIn::create(flash), NULL);
		next->runAction(RepeatForever::create(seq));
		Sprite*hand = Sprite::create("pic/ui/finger1.png");
		ScaleTo * scale1 = CCScaleTo::create(0.6f, 2.2f);
		ScaleTo * scale2 = CCScaleTo::create(0.6f, 2.0f);
		Sequence * sequence = CCSequence::create(scale1, scale2, NULL);
		RepeatForever * repeat = CCRepeatForever::create(sequence);
		hand->runAction(repeat);
		hand->setAnchorPoint(Vec2(0,0));
		hand->setPosition(node->getPosition()+Vec2(30,30));
		this->addChild(hand,23,23);
		bg->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Game::dropGrayLayer, this, (GUIDETEXT)guide)));
		//clip->setInverted(true);
		//clip->setAlphaThreshold(0.0f);
		//this->addChild(clip, 22);
		//clip->addChild(bg);
		//clip->setStencil(node);
// 		if (guide == FULLLETTER)
// 		{
// 			clip->setStencil(__goldUI->_panel);
// 		}
	}
	else if (guide == GUIDESHOCK || guide == GUIDERAGE || guide == GUIDETEXT::GUIDEBOMB)
	{
        bg->setTouchEnabled(false);

		Sprite*hand = Sprite::create("pic/ui/finger1.png");
		ScaleTo * scale1 = CCScaleTo::create(0.6f, 2.2f);
		ScaleTo * scale2 = CCScaleTo::create(0.6f, 2.0f);
		Sequence * sequence = CCSequence::create(scale1, scale2, NULL);
		RepeatForever * repeat = CCRepeatForever::create(sequence);
		hand->runAction(repeat);
		hand->setAnchorPoint(Vec2(0, 0));

// 		Vec2 nodePoint;
// 		if (guide==GUIDESHOCK)
// 		{
// 			nodePoint = __itemUI->getPos(ItemUI::Icon::shock);
// 		}
// 		else if (guide==GUIDERAGE)
// 		{
// 			nodePoint = __itemUI->getPos(ItemUI::Icon::magic);
// 		}
// 		else if (guide==GUIDEBOMB)
// 		{
// 			nodePoint = __itemUI->getPos(ItemUI::Icon::bomb);
// 		}
		hand->setPosition(node->getPosition()+ Vec2(30, 30));
		this->addChild(hand, 23, 23);

// 		clip->setInverted(true);
// 		clip->setAlphaThreshold(0.0f);
// 		clip->addChild(bg);
// 		this->addChild(clip, 22);
// 		if (guide == GUIDEBOMB)
// 		{
// 
// 		}
// 		else if (guide == GUIDERAGE)
// 		{
// 
// 		}
// 		else if (guide == GUIDESHOCK)
// 		{
// 
// 		}
// 		clip->setStencil(node);
		auto callback = [=](Touch *t, Event *e)
		{
			if (node->getBoundingBox().containsPoint(t->getLocation()))
			{
				getChildByTag(23)->removeFromParentAndCleanup(true);
				__itemUI->_bombmenu->setEnabled(false);
				__itemUI->_shockmenu->setEnabled(false);
				__itemUI->_magicmenu->setEnabled(false);
				__itemUI->_ragegray->setEnabled(false);
				gameResume();
				bg->removeFromParentAndCleanup(true);
				if (guide == GUIDERAGE)
				{
					fishes->useRage();
					__itemUI->_ragegray->setVisible(true);
					__itemUI->_magicui->setVisible(false);
				}
				else if (guide == GUIDESHOCK)
				{
					fishes->useShock();
				}
				rootNode->removeFromParentAndCleanup(true);
				auto done = CallFuncN::create([=](Ref* ref){
					__itemUI->_bombmenu->setEnabled(true);
					__itemUI->_shockmenu->setEnabled(true);
					__itemUI->_magicmenu->setEnabled(true);
					__itemUI->_ragegray->setEnabled(true);
				});
				this->runAction(Sequence::create(DelayTime::create(0.5), done, NULL));
			}
			return true;
		};
		auto listener = EventListenerTouchOneByOne::create();
		listener->onTouchBegan = callback;
		listener->setSwallowTouches(true);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, bg);
	}
}
void Game::dropGrayLayer(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e, GUIDETEXT guide)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		getChildByTag(20)->removeFromParentAndCleanup(true);
		gameResume();
		ImageView*bg = (ImageView*)ref;
		bg->removeFromParentAndCleanup(true);

		if (guide == GUIDETEXT::THRESS)
		{
			_time += 3;
			MoveTo* moveto = MoveTo::create(1, Vec2(300, visibleSize.height - 100));
			ScaleTo* scaleto = ScaleTo::create(1, 0.3);
			auto done = CallFuncN::create([=](Ref* ref){
				getChildByTag(21)->removeFromParentAndCleanup(true);
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeUI::TIMEUISHOCK, this);
			});
			getChildByTag(21)->runAction(Sequence::create(Spawn::create(FadeIn::create(0.5), NULL), DelayTime::create(0.5), Spawn::create(moveto, scaleto, NULL), done, NULL));

		}
//        if (guide == GUIDETEXT::TIMEITEM)
//        {
//            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeItem::TIMEPLUS, nullptr);
//
//        }
		else if (guide == GUIDETEXT::FAIL)
		{
			auto done = CallFuncN::create([=](Ref* ref){
				/*__itemUI->_bombmenu->setEnabled(false);*/
				addGrayLayer(GUIDEBOMB, _itembombui);
			});
			this->runAction(Sequence::create(DelayTime::create(0.5), done, NULL));
		}
		else if (guide == GUIDETEXT::FULLLETTER)
		{

		}
		else if (guide == GUIDETEXT::LETTER){
			getChildByTag(23)->removeFromParentAndCleanup(true);
		}
		else if (guide == GUIDETEXT::SHING)
		{
			getChildByTag(23)->removeFromParentAndCleanup(true);
			auto done = CallFuncN::create([=](Ref* ref){
				addGrayLayer(GUIDESHOCK, _itemshockui);
			});
			this->runAction(Sequence::create(DelayTime::create(3), done, NULL));
		}
		else if (guide == GUIDETEXT::TIMEITEM)
		{
			_time += 20;
            this->gameResume();
			MoveTo* moveto = MoveTo::create(1, Vec2(300, visibleSize.height - 100));
			ScaleTo* scaleto = ScaleTo::create(1, 0.3);
			auto done = CallFuncN::create([=](Ref* ref){
				getChildByTag(22)->removeFromParentAndCleanup(true);
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeUI::TIMEUISHOCK, this);

				auto dones = CallFuncN::create([=](Ref* ref){

					addGrayLayer(GUIDERAGE, _itemrageui);
				});
				this->runAction(Sequence::create(DelayTime::create(0.5), dones, NULL));

			});
			getChildByTag(22)->runAction(Sequence::create(Spawn::create(FadeIn::create(0.5), NULL), DelayTime::create(0.5), Spawn::create(moveto, scaleto, NULL), done, NULL));

		}
	}
}

#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
void Game::menuBannerCallback(){
    char mogoid []="61884ac510f4454fadd245f11a8ff025";
    //  使用芒果广告位置
    //  可以通过修改AdMoGoPointTypeDown_middle 变化 位置
    AdsmogoBanner::sharedBanner()->createBanner(mogoid, AdsmogoBannerTypeNormalBanner, AdMoGoPointTypeTop_middle,false);
}

void Game::hiddenBannerCallback(){
    
    AdsmogoBanner::sharedBanner()->hidenBanner();
}
#endif
void Game::setItemEnable(bool b)
{
	__itemUI->_shockmenu->setEnabled(b);
	__itemUI->_bombmenu->setEnabled(b);
	__itemUI->_ragegray->setEnabled(b);
	__itemUI->_magicmenu->setEnabled(b);
}