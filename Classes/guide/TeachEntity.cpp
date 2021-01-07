/****************************************************************************
*	@       	       
*	@desc	游戏物理引擎
*	@date	2014-11-2
*	@author	110101
*	@       	       
*	@file	game/TeachEntity.cpp
*	@modify	null
******************************************************************************/
#include "guide/TeachEntity.h"// 鱼的层
USING_NS_CC;
const std::string TeachEntity::FISH_CATCHED = "fishCatched";
const std::string TeachEntity::RUNNING = "gameRunning";
const std::string TeachEntity::SHINE_START = "gameShineStart";
const std::string TeachEntity::SHINE_FINISH = "gameShineFinish";
TeachEntity* TeachEntity::create(Level level,cocos2d::PhysicsWorld *world)
{
	auto pRet = new TeachEntity();
	if (pRet&&pRet->init(level,world))
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
bool TeachEntity::init(Level level,cocos2d::PhysicsWorld *world)
{
	if (!Layer::init())
	{
		return false;
	}
	_level = level;
	_beginShiningTime = 0.0;
	//随机种子..
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);
	_isHaveAward = false;

	_evt = new EventDispatcher();
	_evt->setEnabled(true);
	Size size = Director::getInstance()->getVisibleSize();
	/**  物理世界  */
//	auto scene = Scene::createWithPhysics();
//	scene->setPosition(0, 0);
//	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    _world = world;//scene->getPhysicsWorld();
	/**  创建边界  */
	_zone = Rect(LEFT_SPACE, TOP_SPACE, size.width - LEFT_SPACE - RIGHT_SAPCE, size.height - TOP_SPACE - BOTTOM_SAPCE);
	auto body = PhysicsBody::createEdgeBox(_zone.size, PhysicsMaterial(0, 0.5f, 0), 3);
	body->setMass(PHYSICS_INFINITY);
	body->setRotationEnable(false);
	auto edgeNode = Node::create();
	edgeNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	edgeNode->setPosition(Vec2(size.width * 0.5, size.height * 0.5));
	edgeNode->setPhysicsBody(body);
	this->addChild(edgeNode);
//	addChild(scene);
	/**  鱼和线添加  */
	__line = Line::create();
	this->addChild(__line);
	__fish = Layer::create();
	this->addChild(__fish);
	/**  点击侦听事件  */
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(false);
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
		//传递鱼的类型  ..
		__line->drawing(_linkPoint);

	};
	listener->onTouchEnded = [=](Touch* t, Event* e){
		_linkEnable = false;
		_linkPoint = t->getLocation();
		catchEnd(_linkPoint);

	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	/*  重置  */
	reset();
	return true;
}
void TeachEntity::moveChange(float dt)
{
	/*for (int i = 0;i<)*/
}
void TeachEntity::reset(){
	__fish->removeAllChildrenWithCleanup(true);
	__line->drawEnd();
	_fishPool.clear();
	_fishNet.clear();
	_isHaveAward = false;

	//类型..
#ifdef CANDY
	std::vector<int> types;
	int randNum = rand() % 4;
	switch (randNum)
	{
	case 0:
		types = { 0, 1, 2, 3, 5, 6 };
		break;
	case 1:
		types = { 0, 1, 2, 3, 6, 7 };
		break;
	case 2:
		types = { 0, 1, 3, 4, 6, 7 };
		break;
	case 3:
		types = { 0, 1, 3, 4, 5, 6 };
		break;
	default:
		break;
	}
	_types.clear();
	while (_types.size() < 4)
	{
		int index = rand() % types.size();
		_types.push_back(types.at(index));
		types.erase(types.begin() + index);
	}
#endif
#ifdef LONGBAO
	_types.clear();
	int index = 0;
	while (_types.size() < 4)
	{		
		_types.push_back(index);
		index++;
	}
#endif
	/**  恢复鱼  */
	recoveryFish();
	/*  定时执行事件  */
	_pauseTime = _startTime = time(NULL);
	_correctTime = _lastTime = 0;
	_bombFishExpire = SHINE_START_TIME;
	this->scheduleUpdate();
}
void TeachEntity::pause(){
	_pauseTime = time(NULL);

	//Vector<Node*> fishes = __fish->getChildren();
	for (Vector<Fish*>::iterator it = _fishPool.begin(); it != _fishPool.end(); it++){
		Fish* fish = (Fish*)*it;
		fish->pause();
	}
	catchEnd(_linkPoint);

	Layer::pause();
}
void TeachEntity::resume(){
	_correctTime += (time(NULL) - _pauseTime);
	Vector<Node*> fishes = __fish->getChildren();
	for (Vector<Node*>::iterator it = fishes.begin(); it != fishes.end(); it++){
		Fish* fish = (Fish*)*it;
		fish->resume();
	}
	Layer::resume();
}
void TeachEntity::addListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback){
	_evt->addCustomEventListener(eventName, callback);
}

void TeachEntity::removeListener(const std::string &eventName)
{
	_evt->removeCustomEventListeners(eventName);
}
void TeachEntity::gameOver(){
	unscheduleUpdate();
	auto done = CallFuncN::create([=](Ref* ref){
		catchEnd(Vec2::ZERO);
		_types.clear();
		Vector<Node*> fishes = __fish->getChildren();
		for (Vector<Node*>::iterator it = fishes.begin(); it != fishes.end(); it++){
			Fish* fish = (Fish*)*it;
			fish->dead();
		}
	});
	this->runAction(Sequence::create(DelayTime::create(0.2f), done, NULL));
	//data::Game::getInstance()->clearFish();
}
void TeachEntity::update(float dt)
{
	struct timeb tb;
	ftime(&tb);
	_timestamp = tb.time + (double)tb.millitm / 1000.0f;
	double runTime = _timestamp - _startTime - _correctTime;
	if (abs(runTime - _runTime) > 0.1){
		_runTime = runTime;
		_evt->dispatchCustomEvent(TeachEntity::RUNNING, &_runTime);
	}
	int num = __fish->getChildrenCount();
	Size size = Director::getInstance()->getVisibleSize();
	Rect rec = Rect(0, 0, size.width, size.height);
	int fishnum = 0;

	if (num < FISH_MAX)
	{
		if (runTime - _lastTime >= FISH_FREQUENCY){
			_lastTime = runTime;
			if (_runTime >= _bombFishExpire&&_level == LEVEL3){
				_bombFishExpire = _runTime + 1000;
				this->addFish(-1);
			}
			else{
				this->addFish();
			}
		}
	}
	if (_linkEnable){
		catching(_linkPoint);
	}
}
void TeachEntity::addFish()
{
	int type = rand() % 4;
	addFish(_types[type]);
}
void TeachEntity::addFish(int type)
{
	int randnum = 0;
	Size size = Director::getInstance()->getVisibleSize();
	int x;
	int y;
	int randNum = rand() % 4;//分别是四条边   下  上  左  右 ..
	switch (randNum)
	{
	case 0:
		x = rand() % (int)(size.width - 400) + 200;
		y = rand() % (int)(size.height / 5) + 150;
		break;
	case 1:
		x = rand() % (int)(size.width - 400) + 200;
		y = size.height - (rand() % (int)size.height / 5 + 150);
		break;
	case 2:
		x = rand() % (int)size.width / 5 + 250;
		y = rand() % (int)(size.height - 400) + 200;
		break;
	case 3:
		x = size.width - (rand() % (int)size.width / 5 + 250);
		y = rand() % (int)(size.height - 400) + 200;
		break;
	default:
		break;
	}

	std::string award = "";
	if (type != cache::Fish::FishName::DISCO && _isAward&&!_isHaveAward) {
		std::string reward = "UMGAME";
		_isHaveAward = true;
		_isAward = false;
#ifdef LONGBAO
		award = reward.at(rand()%6);
#endif
#ifdef CANDY
		//糖果的配色..
		switch (type)
		{
		case 0:
			award = reward.at(0);
			break;
		case 1:
			randnum = rand() % 2;
			if (randnum == 0)
				award = reward.at(0);
			else
				award = reward.at(1);
			break;
		case 2:
			randnum = rand() % 4;
			switch (randnum)
			{
			case 0:
				award = reward.at(1);
				break;
			case 1:
				award = reward.at(2);
				break;
			case 2:
				award = reward.at(3);
				break;
			case 3:
				award = reward.at(5);
				break;
			default:
				break;
			}
			break;
		case 3:
			randnum = rand() % 3;
			switch (randnum)
			{
			case 0:
				award = reward.at(1);
				break;
			case 1:
				award = reward.at(3);
				break;
			case 2:
				award = reward.at(5);
				break;
			default:
				break;
			}
			break;
		case 4:
			randnum = rand() % 4;
			switch (randnum)
			{
			case 0:
				award = reward.at(1);
				break;
			case 1:
				award = reward.at(2);
				break;
			case 2:
				award = reward.at(3);
				break;
			case 3:
				award = reward.at(5);
				break;
			default:
				break;
			}
			break;
		case 5:
			randnum = rand() % 3;
			switch (randnum)
			{
			case 0:
				award = reward.at(0);
				break;
			case 1:
				award = reward.at(1);
				break;
			case 2:
				award = reward.at(3);
				break;
			default:
				break;
			}
			break;
		case 6:
			randnum = rand() % 2;
			switch (randnum)
			{
			case 0:
				award = reward.at(2);
				break;
			case 1:
				award = reward.at(5);
				break;
			default:
				break;
			}
			break;
		case 7:
			randnum = rand() % 3;
			switch (randnum)
			{
			case 0:
				award = reward.at(1);
				break;
			case 1:
				award = reward.at(3);
				break;
			case 2:
				award = reward.at(5);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
#endif
	}

	if (_level == LEVEL3)
	{
		addFish(1, type, x, y, award);
	}
	else
	{
		addFish(1, type, x, y, "");
	}
}

void TeachEntity::addFish(int id, int type, int x, int y, std::string award, bool suddenly)
{
	Fish*fish = new Fish(id, type, x, y, award);
	if (suddenly)
	{
		float rota = rand() % 180 - 90;
		fish->setRotation(rota);
		fish->into(true);
	}
	else
		fish->into(_zone);
	if (_isShine) fish->shining();
	__fish->addChild(fish);
	_fishPool.pushBack(fish);
}
void TeachEntity::recoveryFish(){

	Size size = Director::getInstance()->getVisibleSize();
	int widthlength = size.width / 6;
	int heightlength = size.height / 5;
	for (int i = 0; i < FISH_MAX; i++){
		int randX = i % 5 * widthlength + widthlength;
		int randY = i / 5 * heightlength + heightlength;
		int type = rand() % 4;
		addFish(i, _types[type], randX, randY, "", true);
	}
}
Fish* TeachEntity::getFishByPoint(Vec2 point){
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch() && fish->getCollision().containsPoint(point)){
			return fish;
		}
	}
	return nullptr;
}
Fish* TeachEntity::getFishByPoint(Vec2 point, Fish* referFish){

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

void TeachEntity::catching(Vec2 v){
	if (_fishNet.size() > 2){
		if (_fishNet.at(0)->getCollision().containsPoint(v)&&getFishByPoint(v,_fishNet.at(0))){

			__line->drawNode(_fishNet.at(0)->getPosition(), _fishNet.at(0)->getType());
			catchRound();
			catchEnd(v);
			return;

		}
	}
	Fish* fish = nullptr;


	if (_fishNet.size() == 0){
		fish = getFishByPoint(v);
	}
	else{
		fish = getFishByPoint(v, _fishNet.at(0));
		if (_fishNet.at(0) == fish)
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
void TeachEntity::catchRound(){
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
					shining();
				}
				_fishNet.pushBack(fish);
				_fishPool.eraseObject(fish);
				num++;
				continue;
			}
		}
		n++;
	}
	if (num >= AWARD_ROUND_NUM)
		_isAward = true;
}
void TeachEntity::catchEnd(Vec2 v){
	if (_fishNet.size() == 1) {
		_fishNet.at(0)->pull(v);
		_fishPool.pushBack(_fishNet.at(0));
		_fishNet.erase(_fishNet.begin());
	}
	else{
		std::vector<FishData> fishLinked;
		if (!_isAward && _fishNet.size() >= AWARD_LINK_NUM) _isAward = true;
		bool award = false;
		float delay = 0;
		for (Fish* fish : _fishNet)
		{
			if (!(fish->getFishData().umgame == ""))
			{
				award = true;
			}
			fishLinked.push_back(fish->getFishData());
			data::Game::getInstance()->delFish(fish->getID());
			delay += 0.1;
			if (fish->getState() != Fish::DEAD)fish->dead(delay);
		}
		if (!_isHaveAward || award)
		{
			_isHaveAward = false;
		}
		else if (_isHaveAward&&!award)
		{
			_isHaveAward = true;
		}
		_evt->dispatchCustomEvent(TeachEntity::FISH_CATCHED, &_fishNet);
	}
	_fishNet.clear();
	__line->drawEnd();
	_linkEnable = false;
}
double TeachEntity::getRunTime(){
	return _runTime;
}
void TeachEntity::shining(){
	_isShine = true;
	_nowSpeed = _world->getSpeed();
	_world->setSpeed(SPEED_SHINE);
	_beginShiningTime = _runTime;
	for (Fish*fish : _fishPool)
	{
		fish->shining();
	}
	auto done = CallFunc::create(CC_CALLBACK_0(TeachEntity::shineUp, this));
	Sequence*seq = Sequence::create(DelayTime::create(SHINE_TIME), done, NULL);
	this->runAction(seq);
	_evt->dispatchCustomEvent(TeachEntity::SHINE_START, nullptr);
}
void TeachEntity::shineUp(){
	_world->setSpeed(SPEED_NORMAL);
	_isShine = false;
	for (Fish*fish : _fishPool)
	{
		fish->normal();
	}
	_bombFishExpire = _runTime + SHINE_START_TIME_INTERVAL;
	_evt->dispatchCustomEvent(TeachEntity::SHINE_FINISH, nullptr);
}
bool TeachEntity::isShining(){
	return _isShine;
}
double TeachEntity::shingCountTime()
{
	double times = _runTime - _beginShiningTime - 1;
	return SHINE_TIME - times;
}
