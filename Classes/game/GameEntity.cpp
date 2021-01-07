/****************************************************************************
*	@       	       
*	@desc	游戏物理引擎
*	@date	2014-11-2
*	@author	110101
*	@       	       
*	@file	game/GameEntity.cpp
*	@modify	null
******************************************************************************/
#include "GameEntity.h"// 鱼的层..
USING_NS_CC;
const std::string GameEntity::FISH_CATCHED = "fishCatched";
const std::string GameEntity::RUNNING = "gameRunning";
const std::string GameEntity::SHINE_START = "gameShineStart";
const std::string GameEntity::SHINE_FINISH = "gameShineFinish";
const std::string GameEntity::ITEM_START = "gameItemStart";
const std::string GameEntity::ITEM_FINISH = "gameItemFinish";
const std::string GameEntity::DOUBLE_CLICKED = "doubleclicked";
const std::string GameEntity::RUNNINGGAME = "runninggame";
const std::string GameEntity::SHING_FISH = "haveshingfish";
const std::string GameEntity::LETTER_FISH = "letter_fish";

GameEntity* GameEntity::createWithPhysicsWorld(cocos2d::PhysicsWorld *world)
{
    GameEntity *entuty = new GameEntity();
    if (entuty && entuty->init(world)) {
        entuty->autorelease();
        return entuty;
    }
    else
    {
        delete entuty;
        entuty = NULL;
        return NULL;
    }
}

bool GameEntity::init(cocos2d::PhysicsWorld *world)
{
	if (!Layer::init())
	{
		return false;
	}
	_runGameTimes = 0.0;
	_beginShiningTime = 0.0;
	_streak = MotionStreak::create(0.2, 10, 20, ccc3(255, 255, 255), "pic/public/write.png");
	addChild(_streak, 20);
	//随机种子..
	struct timeval now;
	gettimeofday(&now, NULL);
	unsigned rand_seed = (unsigned)(now.tv_sec * 1000 + now.tv_usec / 1000);
	srand(rand_seed);

	_rageisCD = false;
	_shockisCD = false;
	_isendless = false;
	_isHaveAward = false;
	_isFirstUseShock = true;
	_isFirstUseRage = true;
	_evt = new EventDispatcher();
	_evt->setEnabled(true);
	Size size = Director::getInstance()->getVisibleSize();
	/**  物理世界  */
//	auto scene = Scene::createWithPhysics();
//	scene->setPosition(0, 0);
//	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	//scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	_world = world;
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

		struct timeb tb;
		ftime(&tb);
		double timestamp = tb.time + (double)tb.millitm / 1000.0f;
		if (timestamp - _lastClick < 0.25f)
		{
			//双击操作  发送使用炸弹的事件..
			if (data::User::getInstance()->getGold() > 1)
			{
				if (!isRage())
				{
					if (useBomb(_linkPoint))
					{
						if ((!data::User::getInstance()->getFirstFail())&&data::User::getInstance()->getFirstBomb())
						{
							data::User::getInstance()->setFirstBomb(false);
						}
						else 
						{
							data::Item::getInstance()->use(data::Item::ITEM_BOMB_ID);
						}
					}
				}
			}
			if (data::User::getInstance()->getGold() <=1)
			{
				if (!isRage())
				{
					if (useBomb(_linkPoint))
					{
						_evt->dispatchCustomEvent(GameEntity::DOUBLE_CLICKED, nullptr);
					}
				}
			}
		}
		if (_linkEnable)
		{
			return false;
		}

		_lastClick = timestamp;
		_linkEnable = true;
		_linkPoint = t->getLocation();
		catchBegin(_linkPoint);
		return true;
	};
	listener->onTouchMoved = [=](Touch* t, Event* e){
		_linkEnable = true;
		_linkPoint = t->getLocation();
		//传递鱼的类型..
		__line->drawing(_linkPoint);
		if (isRage())
		{
			_streak->setPosition(_linkPoint);
		}
		catching(_linkPoint);
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
void GameEntity::moveChange(float dt)
{
	/*for (int i = 0;i<)*/
}
void GameEntity::reset(){
	__fish->removeAllChildrenWithCleanup(true);
	__line->drawEnd();
	_fishPool.clear();
	_fishNet.clear();
	shockUseUp();
	rageUseUp();
	shineUp();
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
	/*  定时执行事件   */
	_pauseTime = _startTime = time(NULL);
	_correctTime = _lastTime = 0;
	_bombFishExpire = SHINE_START_TIME;
	this->scheduleUpdate();
}
void GameEntity::pause(){
	_pauseTime = time(NULL);

	//Vector<Node*> fishes = __fish->getChildren();
	for (Vector<Fish*>::iterator it = _fishPool.begin(); it != _fishPool.end(); it++){
		Fish* fish = (Fish*)*it;
		fish->pause();
	}
	catchEnd(_linkPoint);

	Layer::pause();
}
void GameEntity::resume(){
	_correctTime += (time(NULL) - _pauseTime);
	Vector<Node*> fishes = __fish->getChildren();
	for (Vector<Node*>::iterator it = fishes.begin(); it != fishes.end(); it++){
		Fish* fish = (Fish*)*it;
		fish->resume();
	}
	Layer::resume();
}
void GameEntity::addListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback){
	_evt->addCustomEventListener(eventName, callback);
}

void GameEntity::removeListener(const std::string &eventName)
{
	_evt->removeCustomEventListeners(eventName);
}
void GameEntity::gameOver(){

	//使用狂暴道具和雷電道具效果消失....

	unscheduleUpdate();
	//TODO
	stopActionByTag(ACTION_ITEM_RAGE);
	stopActionByTag(ACTION_ITEM_SHOCK);
	//Layer::setTouchEnabled(false);
	catchEnd(_linkPoint);
	auto done = CallFuncN::create([=](Ref* ref){
		/*	catchEnd(Vec2::ZERO);*/
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
void GameEntity::update(float dt)
{
	if (_isFirstUseRage)
	{
		_rageisCD = false;
	}
	else
	{
		if (_useRageTime + _rageCD <= _runTime)
		{
			_rageisCD = false;
		}
		else
		{
			_rageisCD = true;
		}
	}
	if (_isFirstUseShock)
	{
		_shockisCD = false;
	}
	else
	{
		if (_useShockTime + _shockCD - SHOCK_TIME <= _runTime)
		{
			_shockisCD = false;
		}
		else
		{
			_shockisCD = true;
		}
	}

	struct timeb tb;
	ftime(&tb);
	_timestamp = tb.time + (double)tb.millitm / 1000.0f;
	_runGameTimes = _timestamp - _startTime - _correctTime;

	if (!_isUseShock && abs(_runGameTimes - _runTime) > 0.1){
		_runTime = _runGameTimes;
		_evt->dispatchCustomEvent(GameEntity::RUNNING, &_runTime);
	}

	_evt->dispatchCustomEvent(GameEntity::RUNNINGGAME, nullptr);

	int num = __fish->getChildrenCount();
	Size size = Director::getInstance()->getVisibleSize();
	Rect rec = Rect(0, 0, size.width, size.height);
	int fishnum = 0;

	if (num < FISH_MAX)
	{
		if (!_isUseShock && _runGameTimes - _lastTime >= FISH_FREQUENCY){
			_lastTime = _runGameTimes;
			if (_runTime >= _bombFishExpire){
				_bombFishExpire = _runTime + 1000;
				this->addFish(-1);
				_evt->dispatchCustomEvent(GameEntity::SHING_FISH, nullptr);
			}
			else{
				this->addFish();
			}
		}
	}
	// 	if (_linkEnable){
	// 		catching(_linkPoint);
	// 	}
}
void GameEntity::addFish()
{
	int type;
	UMGDBRow row = data::Game::getInstance()->getUserGame();
	int stagenum = row["stage"].asInt();
    if(_isendless)
    {
        type = rand()%4;
    }
    else
    {
        if (stagenum==1)
        {
            type = rand() % 2;
        }
        else if(stagenum==2)
        {
            type = rand() % 3;
        }
        else 
        {
            type = rand() % 4;
        }
    }
	addFish(_types[type]);
}
void GameEntity::addFish(int type)
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

		//出现字母鱼的事件。。
		_evt->dispatchCustomEvent(GameEntity::LETTER_FISH,nullptr);
#ifdef LONGBAO
		award = reward.at(rand() % 6);
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

	if (_isendless)
	{
		addFish(1, type, x, y, "");
	}
	else
	{
		addFish(1, type, x, y, award);
	}
}
void GameEntity::endless(bool isendless)
{
	_isendless = isendless;
}
void GameEntity::addFish(int id, int type, int x, int y, std::string award, bool suddenly)
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
	if (_isUseRage)
	{
		fish->rage();
	}
	if (_isShine)
	{
		fish->shining();
	}
	__fish->addChild(fish);
	_fishPool.pushBack(fish);
}
void GameEntity::recoveryFish(){

	Size size = Director::getInstance()->getVisibleSize();
	int widthlength = size.width / 6;
	int heightlength = size.height / 5;
	int type;
	UMGDBRow row = data::Game::getInstance()->getUserGame();
	int stagenum = row["stage"].asInt();
	for (int i = 0; i < FISH_MAX; i++){
		int randX = i % 5 * widthlength + widthlength;
		int randY = i / 5 * heightlength + heightlength;
		if (stagenum == 1)
		{
			type = rand() % 2;
		}
		else if (stagenum == 2)
		{
			type = rand() % 3;
		}
		else
		{
			type = rand() % 4;
		}
		addFish(i, _types[type], randX, randY, "", true);
	}
}
Fish* GameEntity::getFishByPoint(Vec2 point){
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch() && fish->getCollision().containsPoint(point)){
			return fish;
		}
	}
	return nullptr;
}
Fish*GameEntity::getRageFishByPoint(Vec2 point)
{
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch() && fish->getCollision().intersectsRect(Rect(point.x - 40, point.y - 40, 80, 80))){
			return fish;
		}
	}
	return nullptr;
}
Fish* GameEntity::getFishByPoint(Vec2 point, Fish* referFish){

	Vector<Fish*> vec;
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch()){
			if (__line->isWebify(fish->getPosition())){
				vec.pushBack(fish);
			}
		}
	}
	if (_fishNet.size()>2)
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

void GameEntity::catchBegin(Vec2 v){
	if (_isUseBomb) useBomb(v);
}
void GameEntity::catching(Vec2 v){
	if (_fishNet.size() > 2){
		if (_fishNet.at(0)->getCollision().containsPoint(v)&&getFishByPoint(v,_fishNet.at(0))){
			__line->drawNode(_fishNet.at(0)->getPosition(), _fishNet.at(0)->getType());
			catchRound();
			catchEnd(v);
			return;
		}
	}
	Fish* fish = nullptr;
	//TODO
	if (_isUseRage){
		fish = getRageFishByPoint(v);
		if (fish){
			if (fish->isCanCatch()){
				fish->beRage();
				_fishNet.pushBack(fish);
				catchEnd(v);
				_fishPool.eraseObject(fish);
			}
			fish->dead();
		}
		return;
	}

	if (useBombValid()) return;

	if (_fishNet.size() == 0){
		fish = getFishByPoint(v);
	}
	else{
		fish = getFishByPoint(v, _fishNet.at(0));
		if (_fishNet.at(0)==fish)
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
void GameEntity::catchRound(){
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
void GameEntity::catchEnd(Vec2 v){

	if (_fishNet.size() == 1 && !_isUseRage && !_isUseBomb) {
		_fishNet.at(0)->pull(v);
		_fishPool.pushBack(_fishNet.at(0));
		_fishNet.erase(_fishNet.begin());
	}
	else{
		if (_fishNet.size()>=1)
		{
			_evt->dispatchCustomEvent(GameEntity::FISH_CATCHED, &_fishNet);
		}
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
	}
	_fishNet.clear();
	__line->drawEnd();
	_linkEnable = false;
}
double GameEntity::getRunTime(){
	return _runTime;
}
void GameEntity::shining(){

	_isShine = true;
	_beginShiningTime = _runGameTimes;
	_nowSpeed = _world->getSpeed();
	_world->setSpeed(SPEED_SHINE);
	for (Fish* fish : _fishPool){
		fish->shining();
	}
	auto done = CallFunc::create(CC_CALLBACK_0(GameEntity::shineUp, this));
	Sequence*seq = Sequence::create(DelayTime::create(SHINE_TIME), done, NULL);
	this->runAction(seq);

	_evt->dispatchCustomEvent(GameEntity::SHINE_START, nullptr);
}
void GameEntity::shineUp(){
	_world->setSpeed(SPEED_NORMAL);
	_isShine = false;
	for (Fish*fish : _fishPool)
	{
		fish->normal();
	}
	_bombFishExpire = _runTime + SHINE_START_TIME_INTERVAL;
	_evt->dispatchCustomEvent(GameEntity::SHINE_FINISH, nullptr);
}
bool GameEntity::isShining(){
	return _isShine;
}
bool GameEntity::isItemInUsing(){
	if (_isShine) return true;
	if (_isUseBomb) return true;
	if (_isUseShock) return true;
	if (_isUseRage) return true;
	return false;
}
bool GameEntity::isShock()
{
	return _isUseShock;
}
bool GameEntity::isRage()
{
	return _isUseRage;
}
bool GameEntity::isShine()
{
	return _isShine;
}
void GameEntity::useBomb(){
	_isUseBomb = true;
}
bool GameEntity::useBomb(Vec2 v){
	Fish* fish = this->getFishByPoint(v);
	if (!fish) return false;
	if (fish->isBomb()) return false;

	if (fish){
		if (data::User::getInstance()->getGold()<= 1)
		{
			return true;
		}
		else
		{
			_isUseBomb = true;
			_useBombTime = _timestamp;
			_linkPoint = fish->getPosition();
			fish->dead();
			fish->beBomb();
			_fishNet.pushBack(fish);
			this->useBombValid();
			useBombUp();
			int item = GameEntity::ItemType::BOMB;
			_evt->dispatchCustomEvent(GameEntity::ITEM_START, &item);
			return true;
		}
	}
	return false;
}
void GameEntity::useBombUp()
{
	catchEnd(Vec2::ZERO);
	_isUseBomb = false;
	int item = GameEntity::ItemType::BOMB;
	_evt->dispatchCustomEvent(GameEntity::ITEM_FINISH, &item);
}
bool GameEntity::useBombValid(){
	if (!_isUseBomb) return false;
	double radius = (_timestamp - _useBombTime) * BOMB_RADIUS;
	radius = BOMB_RADIUS;
	//CCLOG("radius %f - %f - %f", radius, _timestamp, _useBombTime);
	Vec2 centre = _linkPoint;
	for (Fish* fish : _fishPool){
		if (fish->isCanCatch() && !fish->isBomb() && centre.distance(fish->getPosition()) < radius){
			fish->beBomb();
			fish->dead();
			_fishNet.pushBack(fish);
		}
	}
	return true;
}
void GameEntity::useShock(){
	if (_isFirstUseShock)
	{
		_isFirstUseShock = false;
		_useShockTime = _runTime;
		_isUseShock = true;
		_nowSpeed = _world->getSpeed();
		_world->setSpeed(SPEED_STATIC);
		for (Fish* fish : _fishPool){
			fish->shock();
		}
		auto done = CallFunc::create(CC_CALLBACK_0(GameEntity::shockUseUp, this));
		Sequence*seq = Sequence::create(DelayTime::create(SHOCK_TIME), done, NULL);
		seq->setTag(ACTION_ITEM_SHOCK);
		_correctTime += SHOCK_TIME;
		this->runAction(seq);
		int item = GameEntity::ItemType::SHOCK;

		_evt->dispatchCustomEvent(GameEntity::ITEM_START, &item);
	}
	else
	{
		if (_useShockTime + _shockCD - SHOCK_TIME <= _runTime)
		{

			_isFirstUseShock = false;
			_useShockTime = _runTime;
			_isUseShock = true;
			_nowSpeed = _world->getSpeed();
			_world->setSpeed(SPEED_STATIC);
			for (Fish* fish : _fishPool){
				fish->shock();
			}
			auto done = CallFunc::create(CC_CALLBACK_0(GameEntity::shockUseUp, this));
			Sequence*seq = Sequence::create(DelayTime::create(SHOCK_TIME), done, NULL);
			_correctTime += SHOCK_TIME;
			this->runAction(seq);
			int item = GameEntity::ItemType::SHOCK;
			_evt->dispatchCustomEvent(GameEntity::ITEM_START, &item);
		}
		else
		{

		}
	}

}
void GameEntity::shockUseUp(){
	_world->setSpeed(SPEED_NORMAL);
	_isUseShock = false;
	for (Fish* fish : _fishPool){
		fish->normal();
	}
	int item = GameEntity::ItemType::SHOCK;
	_evt->dispatchCustomEvent(GameEntity::ITEM_FINISH, &item);
}
void GameEntity::useRage(){
	if (_isFirstUseRage)
	{
		_isUseRage = true;
		_isFirstUseRage = false;
		_useRageTime = _runTime;
		_nowSpeed = _world->getSpeed();
		_world->setSpeed(SPEED_RAGE);
		for (Fish* fish : _fishPool){
			fish->rage();
		}
		


		auto done = CallFunc::create(CC_CALLBACK_0(GameEntity::rageUseUp, this));
		Sequence*seq = Sequence::create(DelayTime::create(RAGE_TIME), done, NULL);
		seq->setTag(ACTION_ITEM_RAGE);
		this->runAction(seq);
		int item = GameEntity::ItemType::RAGE;
		_evt->dispatchCustomEvent(GameEntity::ITEM_START, &item);
	}
	else
	{
		if (_useRageTime + _rageCD <= _runTime)
		{
			_isUseRage = true;
			_isFirstUseRage = false;
			_useRageTime = _runTime;
			_nowSpeed = _world->getSpeed();
			_world->setSpeed(SPEED_RAGE);
			for (Fish* fish : _fishPool){
				fish->rage();
			}
			auto done = CallFunc::create(CC_CALLBACK_0(GameEntity::rageUseUp, this));
			Sequence*seq = Sequence::create(DelayTime::create(RAGE_TIME), done, NULL);
			this->runAction(seq);
			int item = GameEntity::ItemType::RAGE;
			_evt->dispatchCustomEvent(GameEntity::ITEM_START, &item);
		}
		else
		{

		}
	}

}
void GameEntity::rageUseUp()
{
	_world->setSpeed(SPEED_NORMAL);
	_isUseRage = false;
	for (Fish* fish : _fishPool){
		fish->normal();
	}
	//todo
	//_fishNet.clear();
	int item = GameEntity::ItemType::RAGE;
	_evt->dispatchCustomEvent(GameEntity::ITEM_FINISH, &item);
}
bool GameEntity::shockisCD()
{
	return _shockisCD;
}
bool GameEntity::rageisCD()
{
	return _rageisCD;
}
void GameEntity::setGameFirst()
{
	_isFirstUseRage = true;
	_isFirstUseShock = true;
	_rageisCD = false;
	_shockisCD = false;
}

double GameEntity::shockCDTime()
{

	return (_runGameTimes + 5 - _useShockTime) / _shockCD * 100;

}
double GameEntity::rageCDTime()
{
	return (_runTime - _useRageTime) / _rageCD * 100;
}
double GameEntity::rageCountTime()
{
	double times = _runGameTimes - _useRageTime - 1;
	return RAGE_TIME - times;
}
double GameEntity::shockCountTime()
{
	double times = _runGameTimes - _useShockTime + SHOCK_TIME - 1;
	return SHOCK_TIME - times;
}
double GameEntity::shingCountTime()
{
	double times = _runGameTimes - _beginShiningTime - 1;
	return SHINE_TIME - times;
}

Node* GameEntity::getShing()
{
	for (Fish*fish:_fishPool)
	{
		if (fish->getType() == cache::Fish::FishName::DISCO)
		{
			return fish;
		}
	}
}
Node*GameEntity::getLetter()
{
	for (Fish*fish:_fishPool)
	{
		if (fish->getAward()!="")
		{
			return fish;
		}
	}
}

bool GameEntity::getIsShing()
{
	return _isShine;
}
