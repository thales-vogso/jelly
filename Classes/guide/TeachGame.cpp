/****************************************************************************
*	@       	       
*	@desc	新手教程的关卡部分场景
*	@date	2014-12-15
*	@author	jinzhen
*	@       	       
*	@file	guide/TeachGame.h
*	@modify	null
******************************************************************************/
#include "TeachGame.h"
USING_NS_CC;
using namespace  ui;
using namespace popup;
static cocos2d::PhysicsWorld *_world = NULL;
cocos2d::Scene* TeachGame::createScene(TeachEntity::Level level)
{
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    _world = scene->getPhysicsWorld();
	auto layer = TeachGame::create(level);
	scene->addChild(layer);
	return scene;
}
TeachGame* TeachGame::create(TeachEntity::Level level)
{
	auto pRet = new TeachGame();
	if (pRet&&pRet->init(level))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return nullptr;
	}
}
bool TeachGame::init(TeachEntity::Level level)
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	//弹窗层..
	PopUp* popUp = PopUp::create();
	addChild(popUp, 100, "popup");

	__flyLayer = Layer::create();
	addChild(__flyLayer, 99, "fly");

	_level = level;
	this->setDateNull();
	//添加背景..
	_bg = Background::create();
	_bg->changeBgState(Background::NORMAL);
	this->addChild(_bg);

	//添加得分的ui..
	__scoreUI = ScoreUI::create();
	this->addChild(__scoreUI, 20);
	__scoreUI->_stage->setVisible(false);
	__scoreUI->_target->setVisible(false);
	//添加时间UI..
	__timeUI = TimeUI::create();
	__timeUI->setEndless(false);
    __timeUI->_adblockui->setVisible(false);
	this->addChild(__timeUI, 20);

	//添加游戏最后倒计时的显示文字..
	_label = LabelTTF::create("11", "Arial", 400);
	_label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(_label, 1);
	_label->setVisible(false);

	switch (_level)
	{
	case TeachEntity::LEVEL1:
		break;
	case TeachEntity::LEVEL2:
		break;
	case TeachEntity::LEVEL3:
		//添加金币 UI..
		__goldUI = GoldUI::create();
		this->addChild(__goldUI, 20);
		__goldUI->_plus->setVisible(false);
		//添加umgame..
		__umgame = UmGameUI::create(true);
		this->addChild(__umgame, 3);

		break;
	default:
		break;
	}
	Widget*pausemenu = cocos2d::ui::Helper::seekWidgetByName(__timeUI->_panel, __timeUI->PAUSES);
	pausemenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TeachGame::pauseClick, this)));

	/*
	*	暂停界面三个按键的事件的监听  分别是重玩 ，继续游戏，跳过教程
	*/
	auto resumeLisenter = [=](EventCustom*e)
	{
		//重新初始化..
		reset();
	};
	_eventDispatcher->addCustomEventListener(TeachPause::RESUMETEACH, resumeLisenter);

	auto backgameLisenter = [=](EventCustom*e)
	{
		//继续游戏..
		gameResume();
	};
	_eventDispatcher->addCustomEventListener(TeachPause::BACKGAME, backgameLisenter);

	auto skipLisenter = [=](EventCustom*e)
	{
		//TODO 跳过教程..


	};
	_eventDispatcher->addCustomEventListener(TeachPause::SKIPTEACH, skipLisenter);

	outKeyInit();
	return true;
}

void TeachGame::outKeyInit(){
	_moveInListener = EventListenerCustom::create(Quit::MOVEIN, [=](EventCustom* e){
		gamePause();
		openQuit = true;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveInListener, 1);

	_moveOutListener = EventListenerCustom::create(Quit::MOVEOUT, [=](EventCustom* e){
		gameResume();
		openQuit = false;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveOutListener, 1);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){

		if (keyCode == EventKeyboard::KeyCode::KEY_BACK){
			PopUp* popup = (PopUp*)getChildByName("popup");
			if (!popup->closeTopPop())
			{
				if (!openQuit)
				{
					addChild(Quit::create(), 10, "quit");
				}
				else
				{
					//退出游戏..
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

void TeachGame::setScore(EventCustom*e)
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
			if (_fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::LINK)
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
			if (_fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::CAPTURE)
			{
				popFly(time, (*it)->getPosition());
			}
		}
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = 8;
			if (_fishes->isShining())
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
			if (_fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::ROUND)
			{
				popFly(time, (*it)->getPosition());
			}
		}
		for (std::vector<Fish*>::iterator it = vscore.begin(); it != vscore.end(); ++it)
		{
			int time = capture;
			if (_fishes->isShining())
				time = time * 3;
			if ((*it)->_arrest == Fish::Arrest::CAPTURE)
			{
				popFly(time, (*it)->getPosition());
			}
		}
	}

	if (_fishes->isShining())
	{
		score = score * 3;
	}

	int scores = _score;

	int num = scores / 100;

	int tenbit = scores - 100 * num;

	if (tenbit + score >= 100 && _level != TeachEntity::LEVEL1)
	{
		Size size = Director::getInstance()->getVisibleSize();
		_time += 3;
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
	_isBombFish = false;
	_score += score;
	Node* block = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->CUSCORE);
	String* ns = String::createWithFormat("%d", _score);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);

}
void TeachGame::showTime(double time)
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

void TeachGame::onEnterTransitionDidFinish()
{
	cache::Music::getInstance()->playBGM(cache::Music::BGMName::GAME);

	Layer::onEnterTransitionDidFinish();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Size winsize = Director::sharedDirector()->getVisibleSize();

	//添加糖果层..
	_fishes = TeachEntity::create(_level,_world);
	this->addChild(_fishes, 2);

	//根据连接的鱼设置分数..
	_fishes->addListener(TeachEntity::FISH_CATCHED, CC_CALLBACK_1(TeachGame::setScore, this));


	_fishes->addListener(TeachEntity::RUNNING, [=](EventCustom* e){
		_runningTime = *(double*)e->getUserData();
		_surplusTime = _time - _runningTime;
		this->showTime(_surplusTime);

		if (_surplusTime <= 0)
		{
			_label->setVisible(false);
			_fishes->gameOver();
			auto done = CallFuncN::create([=](Ref* ref)
			{
				_bg->changeBgState(Background::NORMAL);
				cache::Music::getInstance()->playEffect(cache::Music::EffectName::GAMEWIN);
				this->FinishLevel();
			});
			this->runAction(Sequence::create(DelayTime::create(1.2), done, NULL));
		}
		else if (_surplusTime <= 10)
		{
			if (_fishes->isShining())
				CCLOG("fsdf");
			else
				Countdown(_surplusTime);
		}
		if (_fishes->isShining())
		{
			Countdown(_fishes->shingCountTime());
		}
	});
	_fishes->addListener(GameEntity::SHINE_START, [=](EventCustom* e){
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
	_fishes->addListener(GameEntity::SHINE_FINISH, [=](EventCustom* e){
		_bg->changeBgState(Background::NORMAL);
		_label->setVisible(false);
	});
}
void TeachGame::FinishLevel()
{
	//TODO 玩家结束后跳转场景..
	switch (_level)
	{
	case TeachEntity::LEVEL1:
	{
		Scene* scene = Guide::createScene(Guide::CSBSTEP2);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
		break;
	}
	case TeachEntity::LEVEL2:
	{
		Scene* scene = Guide::createScene(Guide::CSBSTEP3);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
		break;
	}
	case TeachEntity::LEVEL3:
	{
		Scene* scene = Guide::createScene(Guide::CSBSTEP4);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
		break;
	}
	}
}
void TeachGame::setDateNull()
{
	_score = 0;
	_goldNum = 0;
	_time = 61;
	//TODO umgame 
}
void TeachGame::pauseClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){

		gamePause();
		PopUp* popup = (PopUp*)getChildByName("popup");
		//添加暂停界面..
		popup->addTopPop(TeachPause::create());
	}
}
void TeachGame::gamePause()
{
	cache::Music::getInstance()->pauseBGM();
	_fishes->pause();
}
void TeachGame::gameResume()
{
	cache::Music::getInstance()->resumeBGM();
	_fishes->resume();
}
void TeachGame::reset()
{
	_label->setVisible(false);
	//TODO 重置..
	gameResume();
	_bg->randBg();
	if (_fishes)  _fishes->reset();
	this->setDateNull();
	Node* block = cocos2d::ui::Helper::seekWidgetByName(__scoreUI->_panel, __scoreUI->CUSCORE);
	String* ns = String::createWithFormat("%d", 0);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);
	if (_level == TeachEntity::LEVEL3)
	{
		__goldUI->changeGold(0);
		__umgame->setUmgameNull();
	}
}
TeachGame::~TeachGame()
{
	_eventDispatcher->removeEventListener(_moveInListener);
	_eventDispatcher->removeCustomEventListeners(TeachPause::RESUMETEACH);
	_eventDispatcher->removeCustomEventListeners(TeachPause::SKIPTEACH);
	_eventDispatcher->removeCustomEventListeners(TeachPause::BACKGAME);
}
void TeachGame::Countdown(int time)
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
	if (time == 10)
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

void TeachGame::popFly(int score, cocos2d::Vec2 pos)
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