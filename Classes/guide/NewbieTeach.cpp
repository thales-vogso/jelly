/****************************************************************************
*	@       	       
*	@desc	新手引导的教学关卡的场景
*	@date	2014-12-10
*	@author	120102
*	@       	       
*	@file	main/NewbieTeach.cpp
*	@modify	null
******************************************************************************/
#include "guide/NewbieTeach.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
static PhysicsWorld *_world = NULL;
cocos2d::Scene* NewbieTeach::createScene(TeachLevel level)
{
    Scene* scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
    _world = scene->getPhysicsWorld();
	auto layer = NewbieTeach::create(level);
	scene->addChild(layer);
	return scene;
}
bool NewbieTeach::init(TeachLevel level)
{
	if (!Layer::init())
	{
		return false;
	}
	__flyLayer = Layer::create();
	addChild(__flyLayer, 99, "fly");
	//添加背景..
	_bg = Background::create();
	_bg->changeBgState(Background::NORMAL);
	this->addChild(_bg);

	_level = level;
	_isSuccess = false;
	/**  鱼和线添加  */
	__line = Line::create();
	addChild(__line);
	__fish = Layer::create();
	addChild(__fish);
	switch (_level)
	{
	case NewbieTeach::LINE:
		addLineFish();
		break;
	case NewbieTeach::ROUND:
		addClicleFish();
		break;
	case NewbieTeach::SHING:
		addShingFish();
		break;
	case NewbieTeach::LETTER:
		addLetterFish();
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


	_size = Director::getInstance()->getVisibleSize();
	/**   点击侦听事件  */
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* t, Event* e){
		if (_linkEnable)
		{
			return false;		
		}
		_linkEnable = true;
		_linkPoint = t->getLocation();
		return true;
	};
	listener->onTouchMoved = [=](Touch* t, Event* e){
		_linkEnable = true;
		_linkPoint = t->getLocation();
		__line->drawing(_linkPoint);
	};
	listener->onTouchEnded = [=](Touch* t, Event* e){
		_linkEnable = false;
		_linkPoint = t->getLocation();
		if (!_isSuccess)
		{
			catchEnd(_linkPoint);
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	this->scheduleUpdate();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	std::string str = "";
	switch (_level)
	{
#ifdef LONGBAO
	case NewbieTeach::LINE:
		str = "csb/longbao/guide/step2newbee.csb";
		break;
	case NewbieTeach::ROUND:
		str = "csb/longbao/guide/step4newbee.csb";
		break;
	case NewbieTeach::SHING:
		str = "csb/longbao/guide/step6newbee.csb";
		break;
	case NewbieTeach::LETTER:
		str = "csb/longbao/guide/step7newbee.csb";
		break;
#endif

#ifdef CANDY
	case NewbieTeach::LINE:
		str = "csb/guide/step2newbee.csb";
		break;
	case NewbieTeach::ROUND:
		str = "csb/guide/step4newbee.csb";
		break;
	case NewbieTeach::SHING:
		str = "csb/guide/step6newbee.csb";
		break;
	case NewbieTeach::LETTER:
		str = "csb/guide/step7newbee.csb";
		break;
#endif
	}	
	//加载动画节点..
	__rootNode = CSLoader::createNode(str);
	__rootNode->setPosition(midPoint);
	addChild(__rootNode, 1);
	//加载动画： ..
	__action = CSLoader::createTimeline(str);
	__rootNode->runAction(__action);
	__action->setTimeSpeed(0.8);
	__action->gotoFrameAndPlay(0, 30, false);

	Widget* skip = (Widget*)Main::seekNodeByName(__rootNode, "skip");
	skip->setPosition(Vec2(visibleSize.width * 0.5 - 26 - 45, visibleSize.height * 0.5 - 26 - 45));
	skip->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(NewbieTeach::skip, this)));
	return true;
}

void NewbieTeach::skip(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);	
		
        cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
        popup::Skip *skip = popup::Skip::create();
        skip->m_bNotPushToColse = true;
        addChild(skip,100);
	}
}
void NewbieTeach::addFish(int id, int type, int x, int y, std::string award, bool suddenly)
{
	Fish*fish = new Fish(id, type, x, y, award);
	if (suddenly)
		fish->into(true);

	
	__fish->addChild(fish);
	_fishPool.pushBack(fish);
}
void NewbieTeach::addLineFish(){
    _world->setSpeed(SPEED_STATIC);

	Size size = Director::getInstance()->getVisibleSize();
	addFish(0, cache::Fish::FishName::RED, size.width / 2, size.height / 2-90, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 - 440, size.height / 2+249, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 + 440, size.height / 2+249, "", true);
	addFish(0, cache::Fish::FishName::EYE, size.width / 2, size.height / 2+257, "", true);
}
void NewbieTeach::addClicleFish()
{
    _world->setSpeed(SPEED_STATIC);

	Size size = Director::getInstance()->getVisibleSize();
	addFish(0, cache::Fish::FishName::RED, size.width/2-486,size.height/2+350, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width/2-289,size.height / 2-139, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width/2+511,size.height / 2+376, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width/2+242,size.height / 2-131, "", true);
	addFish(0, cache::Fish::FishName::EYE, size.width / 2 - 163, size.height / 2 + 144, "", true);
	addFish(0, cache::Fish::FishName::BLUE, size.width / 2 + 145, size.height / 2 + 162, "", true);
}
void NewbieTeach::addShingFish()
{
    _world->setSpeed(SPEED_STATIC);

	Size size = Director::getInstance()->getVisibleSize();
	addFish(0, cache::Fish::FishName::RED, size.width / 2 - 486, size.height / 2 + 350, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 - 289, size.height / 2 - 139, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 + 511, size.height / 2 + 376, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 + 242, size.height / 2 - 131, "", true);

	addFish(0, cache::Fish::FishName::BLUE, size.width / 2 - 600, size.height / 2, "", true);
#ifdef CANDY
	addFish(0, cache::Fish::FishName::PINK, size.width / 2 + 700, size.height / 2 + 100, "", true);
#endif
#ifdef LONGBAO
	addFish(0, cache::Fish::FishName::GREEN, size.width / 2 + 700, size.height / 2 + 100, "", true);
#endif
	addFish(2, cache::Fish::FishName::DISCO, size.width / 2 + 145, size.height / 2 + 162, "", true);
}
void NewbieTeach::addLetterFish()
{
    _world->setSpeed(SPEED_STATIC);

	Size size = Director::getInstance()->getVisibleSize();
	addFish(0, cache::Fish::FishName::RED, size.width / 2 - 486, size.height / 2 + 350, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 - 289, size.height / 2 - 139, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 + 511, size.height / 2 + 376, "", true);
	addFish(0, cache::Fish::FishName::RED, size.width / 2 + 242, size.height / 2 - 131, "", true);
	addFish(1, cache::Fish::FishName::RED, size.width / 2 + 145, size.height / 2 + 162, "M", true);
}
void NewbieTeach::catching(Vec2 v){
	if (_fishNet.size() > 2){
		if (_fishNet.at(0)->getCollision().containsPoint(v)&&getFishByPoint(v,_fishNet.at(0))){
			if (_fishNet.size()==4||(_level==SHING)||_level==LETTER)
			{
				__line->drawNode(_fishNet.at(0)->getPosition(), _fishNet.at(0)->getType());
				catchRound();
				catchEnd(v);
				return;
			}
		}
	}
	Fish* fish = nullptr;
	if (_fishNet.size() == 0){
		fish = getFishByPoint(v);
	}
	else{
		fish = getFishByPoint(v, _fishNet.at(0));
		if (fish==_fishNet.at(0))
		{
			return;
		}
		__line->drawing(_linkPoint);
	}

	if (fish){
		fish->stop();
		_fishNet.pushBack(fish);
		__line->drawNode(fish->getPosition(), _fishNet.at(0)->getType());
		_fishPool.eraseObject(fish);
	}
}
void NewbieTeach::catchRound(){
	for (Fish* fish : _fishNet){
		fish->beRound();
	}
	int num = 0;
	int n = 0;
	while (n < _fishPool.size()){
		Fish* fish = _fishPool.at(n);
		if (fish->isCanRound()){
			if (__line->isRounded(fish->getPosition())){
				fish->beCapture();
				fish->dead();
				if (fish->isBomb()){
					//shining();
				}
			
				_fishNet.pushBack(fish);
				_fishPool.eraseObject(fish);
				num++;
				continue;
			}
		}
		n++;
	}	
}

void NewbieTeach::shining(){
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	auto done = CallFunc::create(CC_CALLBACK_0(NewbieTeach::shineUp, this));
	Sequence*seq = Sequence::create(DelayTime::create(10), done, NULL);
	this->runAction(seq);

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
}
void NewbieTeach::shineUp(){
	_bg->changeBgState(Background::NORMAL);
}
void NewbieTeach::catchEnd(Vec2 v){
	if (_fishNet.size()==0)
	{
		return;
	}
	if (_fishNet.size() == 1) {
		_fishNet.at(0)->pull(v);
		_fishPool.pushBack(_fishNet.at(0));
		_fishNet.erase(_fishNet.begin());
		
	}
	else
	{
		switch (_level)
		{
		case NewbieTeach::LINE:
			if (_fishNet.size() == 3)
				_isSuccess = true;
			else
				_isSuccess = false;
			break;
		case NewbieTeach::ROUND:
			if (_fishNet.size() == 6)
				_isSuccess = true;			
			else		
				_isSuccess = false;		
			break;
		case NewbieTeach::SHING:
			break;
		case NewbieTeach::LETTER:
			break;
		default:
			break;
		}
	
		
		std::vector<FishData> fishLinked;	
		float delay = 0;
		for (Fish* fish : _fishNet)
		{
			if (fish->getID() == 1 && _level == LETTER)
			{
				_isSuccess = true;
				__umgame->getLetter("M");				
			}
			if (fish->getID()==2&&_level==SHING)
			{
				_isSuccess = true;
			}
			fishLinked.push_back(fish->getFishData());
			delay += 0.1;
			if (fish->getState() != Fish::DEAD)fish->dead(delay);
		}
		this->FinishTeach();
	}
	_fishNet.clear();
	__line->drawEnd();
	
	_linkEnable = false;
}
Fish* NewbieTeach::getFishByPoint(Vec2 point){
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch() && fish->getCollision().containsPoint(point)){
			return fish;
		}
	}
	return nullptr;
}
Fish* NewbieTeach::getFishByPoint(Vec2 point, Fish* referFish){
	Vector<Fish*> vec;
	for (Fish* fish : _fishPool){

		if (fish->isCanCatch()){
			if (__line->isWebify(fish->getPosition())){
				vec.pushBack(fish);
			}
		}
	}
	if (_fishNet.size() > 2)
	{
		if (__line->isWebify(_fishNet.at(0)->getPosition()))
		{
			vec.pushBack(_fishNet.at(0));
		}
	}
	if (vec.size() == 1)
	{
		if (vec.at(0)->getType() == referFish->getType())
		{
			return vec.at(0);
		}
	}
	return nullptr;
}
void NewbieTeach::update(float dt)
{
	if (_linkEnable){
		catching(_linkPoint);
	}
}
bool NewbieTeach::isSuccess()
{
	return _isSuccess;
}
void NewbieTeach::FinishTeach()
{
	Scene*scene;
	if (_isSuccess)
	{
		switch (_level)
		{
		case NewbieTeach::LINE:
			scene = Guide::createScene(3);
			break;
		case NewbieTeach::ROUND:
			scene = TeachGame::createScene(TeachEntity::LEVEL2);
			break;
		case NewbieTeach::SHING:
			scene = Guide::createScene(9);
			break;
		case NewbieTeach::LETTER:
			scene = Guide::createScene(0);
			break;
		}
	}
	else if (!_isSuccess)
	{
		switch (_level)
		{
		case NewbieTeach::LINE:
			scene = Guide::createScene(2);
			break;
		case NewbieTeach::ROUND:
			scene = Guide::createScene(4);
			break;
		case NewbieTeach::SHING:
			scene = Guide::createScene(8);
			break;
		case NewbieTeach::LETTER:
			scene = Guide::createScene(10);
			break;
		default:
			break;
		}
	}
	scene->retain();
	auto done = CallFuncN::create([=](Ref* ref){
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	});
	this->runAction(Sequence::create(DelayTime::create(1), done, NULL));
	
}
NewbieTeach::~NewbieTeach()
{
	
}

NewbieTeach* NewbieTeach::create(TeachLevel level)
{
	auto pRet = new NewbieTeach();
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
