/****************************************************************************
*	@       	       
*	@desc	鱼的类
*	@date	2014-10-20
*	@author	120102
*	@       	       
*	@file	game/Fish.cpp
*	@modify	null
******************************************************************************/
#include "Fish.h"// 鱼类的头文件..
#include <cmath>
USING_NS_CC;
using namespace cocostudio::timeline;
Fish::Fish(int id, int type, int x, int y, std::string award)
{
	_id = id;

	this->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_type = type;
	_award = award;
	_shing = false;
	// 初始化鱼的状态..
	_state = Fish::State::MOVE;
	_arrest = Fish::Arrest::NONE;
	if (_type == cache::Fish::FishName::DISCO)
		__fishSprite = cache::Fish::getInstance()->getDiscoNormalFish();
	else
		__fishSprite = cache::Fish::getInstance()->getNormalFish(_type);
	addChild(__fishSprite, 0);
	if (_award != ""){
		std::stringstream sql;
		sql << "pic/public/UM_" << _award << ".png";
		__umgame = Sprite::create(sql.str());
		addChild(__umgame, 1);
	}
	/**  物理引擎  */
	PhysicsBody* body = PhysicsBody::createCircle(75, PhysicsMaterial(0.5f, 0.5f, 0.5f));
	body->setMass(MESS);
	body->setRotationEnable(true);
	setPhysicsBody(body);
	setPosition(Vec2(x, y));
	autorelease();
	scheduleUpdate();
	int randnum = rand() % 4 + 3;
#ifdef CANDY
	scheduleOnce(schedule_selector(Fish::changeBody), randnum);
#endif
}
void Fish::changeBody(float dt){
	if (_type == cache::Fish::FishName::DISCO)
		return;
	_change = true;
	if (_state == Fish::State::MOVE && _rage == false)
	{
		__fishSprite->removeFromParentAndCleanup(true);
#ifdef CANDY
		__fishSprite = cache::Fish::getInstance()->getChangeFish(_type);
#endif
#ifdef LONGBAO
		__fishSprite = cache::Fish::getInstance()->getNormalFish(_type);
#endif
		addChild(__fishSprite);
		int randnum = rand() % 13 + 8;
		scheduleOnce(schedule_selector(Fish::changeNormal), randnum);
	}
}
void Fish::changeNormal(float dt){
	if (_type == cache::Fish::FishName::DISCO)
		return;
	_change = false;
	if (_state == Fish::State::MOVE && _rage == false)
	{
		__fishSprite->removeFromParentAndCleanup(true);
		__fishSprite = cache::Fish::getInstance()->getNormalFish(_type);
		addChild(__fishSprite);
		int randnum = rand() % 4 + 3;
		scheduleOnce(schedule_selector(Fish::changeBody), randnum);
	}
}
Fish::~Fish(){
}
void Fish::into(Rect rect){
	getPhysicsBody()->setEnable(false);
	//现在的位置..
	Vec2 pos = getPosition();
	Vec2 offset = Vec2::ZERO;
	float posX = pos.x;
	float posY = pos.y;
	// 	if (pos.x < rect.getMidX()){
	// 		offset.x = rect.getMinX();
	// 	}else{
	// 		offset.x = rect.getMaxX();
	// 	}
	// 
	// 	offset.y = rect.getMinY() + rand() % (int)rect.size.height;

	if (pos.x < rect.getMidX())
	{
		if (pos.y < rect.getMidY())
		{
			if (abs(ccpDistance(pos, Vec2(rect.getMinX(), posY))) > abs(ccpDistance(pos, Vec2(posX, rect.getMinY()))))
			{
				offset.x = posX;
				offset.y = rect.getMinY() + 50;
			}
			else
			{
				offset.x = rect.getMinX() + 50;
				offset.y = posY;
			}
		}
		else
		{
			if (abs(ccpDistance(pos, Vec2(rect.getMinX(), posY))) > abs(ccpDistance(pos, Vec2(posX, rect.getMaxY()))))
			{
				offset.x = posX;
				offset.y = rect.getMaxY() - 50;
			}
			else
			{
				offset.x = rect.getMinX() - 50;
				offset.y = posY;
			}
		}
	}
	else
	{
		if (pos.y < rect.getMidY())
		{
			if (abs(ccpDistance(pos, Vec2(rect.getMaxX(), posY))) > abs(ccpDistance(pos, Vec2(posX, rect.getMinY()))))
			{
				offset.x = posX;
				offset.y = rect.getMinY() + 50;
			}
			else
			{
				offset.x = rect.getMaxX() - 50;
				offset.y = posY;
			}
		}
		else
		{
			if (abs(ccpDistance(pos, Vec2(rect.getMaxX(), posY))) > abs(ccpDistance(pos, Vec2(posX, rect.getMaxY()))))
			{
				offset.x = posX;
				offset.y = rect.getMaxY() - 50;
			}
			else
			{
				offset.x = rect.getMaxX() - 50;
				offset.y = posY;
			}
		}
	}

	setPosition(Vec2(offset.x, offset.y));

	CallFunc* done = CallFunc::create([&](){
		move();
	});
	Sequence* seq = Sequence::create(EaseSineOut::create(MoveTo::create(1.f, Vec2(pos.x, pos.y))), done, NULL, NULL);
	runAction(seq);
}
void Fish::into(bool suddenly){
	getPhysicsBody()->setEnable(false);
	__fishSprite->setScaleX(0.1f);
	__fishSprite->setScaleY(0.1f);
	CallFunc* done = CallFunc::create([&](){
		move();
	});
	Sequence* seq = Sequence::create(EaseSineIn::create(ScaleTo::create(1.0f, 1.0f)), done, NULL, NULL);
	__fishSprite->runAction(seq);
}
void Fish::update(float dt)
{
	float b = CC_RADIANS_TO_DEGREES(getPhysicsBody()->getRotation());
	__fishSprite->setRotation(-b);
	if (__umgame)
		__umgame->setRotation(-b);

	Vec2 velocity = getPhysicsBody()->getVelocity();
	float distance = velocity.getDistance(Vec2::ZERO);
	getPhysicsBody()->resetForces();
	if (distance < 1.0f){
		getPhysicsBody()->setVelocity(Vec2::ZERO);
	}
	else{
		Vec2 force = Vec2::ZERO - velocity;
		force *= 2.5;
		getPhysicsBody()->applyForce(force);
	}
}
void Fish::pause(){
	Node::pause();
	getPhysicsBody()->setEnable(false);
	__fishSprite->pause();
}
void Fish::resume(){
	Node::resume();
	getPhysicsBody()->setEnable(true);
	__fishSprite->resume();
}
void Fish::stop()
{
	__fishSprite->removeFromParentAndCleanup(true);

	if (_type == cache::Fish::FishName::DISCO)
		__fishSprite = cache::Fish::getInstance()->getDiscoPressFish();
	else
		__fishSprite = cache::Fish::getInstance()->getPressFish(_type);

	addChild(__fishSprite);

	_state = Fish::State::CATCHED;
	_arrest = Fish::Arrest::LINK;
	stopAllActions();
	getPhysicsBody()->setEnable(false);
	unschedule(schedule_selector(Fish::moveChange));
	cache::Music::getInstance()->playEffect(cache::Music::EffectName::PRESSFISH);
}
void Fish::move()
{
	_state = Fish::State::MOVE;
	_arrest = Fish::Arrest::NONE;
	getPhysicsBody()->setEnable(true);
	float motion = 0;
	if (_rage)
	{
		motion = MOTION_DURATION_RAGE;
	}
	else if (_shing)
	{
		motion = MOTION_DURATION_SHING;
	}
	else
	{
		motion = MOTION_DURATION_NORMAL;
	}

	if (isBomb()){
		motion /= 2;
	}
	schedule(schedule_selector(Fish::moveChange), motion);
	moveChange(0);
}
void Fish::moveChange(float dt){
	float motion = 0;
	if (!_rage&&!_shing)
	{
		motion = MOTION_DURATION_NORMAL;
	}
	else if (_rage)
	{ 
		motion = MOTION_DURATION_RAGE;
	}
	else if (_shing)
	{
		motion = MOTION_DURATION_SHING;
	}
	float compressX = 1.1;
	float compressY = 0.9;
	float stretchX = 1;
	float stretchY = 1.2;
	float compressTime = motion*0.25;
	float stretchTime = motion*0.125;
	float recoverTime = motion*0.25;
	float angle = 0.0;
	//四个方向..
	int num = rand() % 4;

	//出界往回方向判断..
	Vec2 pos = getPosition();
	Size size = Director::getInstance()->getVisibleSize();
	Vec2 mid = Vec2(size.width*0.5, size.height*0.5);
	PhysicsBody* a = getPhysicsBody();
	if (a == nullptr)
	{
		return;
	}
	float bodyRoatio = CC_DEGREES_TO_RADIANS((int)CC_RADIANS_TO_DEGREES(getPhysicsBody()->getRotation()) % 360);
	if (bodyRoatio < 0)
		bodyRoatio += 2 * M_PI;

	Rect winRect = Rect(size.width/6, size.height/6, size.width/6*4, size.height/6*4);
	Vec2 dir = mid - pos;

	if (!winRect.containsPoint(pos))
	{
		float angel0 = CC_DEGREES_TO_RADIANS(0) + bodyRoatio;
		float angel90 = CC_DEGREES_TO_RADIANS(90) + bodyRoatio;
		float angel180 = CC_DEGREES_TO_RADIANS(180) + bodyRoatio;
		float angel270 = CC_DEGREES_TO_RADIANS(270) + bodyRoatio;
		float angelMid = Vec2(1, 0).getAngle(dir);
		if (angel90 >= 2 * M_PI)
			angel90 -= 2 * M_PI;
		if (angel180 >= 2 * M_PI)
			angel180 -= 2 * M_PI;
		if (angel270 >= 2 * M_PI)
			angel270 -= 2 * M_PI;
		if (angelMid < 0)
			angelMid += 2 * M_PI;

		float cha0 = abs(angelMid - angel0);
		float cha90 = abs(angelMid - angel90);
		float cha180 = abs(angelMid - angel180);
		float cha270 = abs(angelMid - angel270);

		float a[4];
		a[0] = cha0; a[1] = cha90; a[3] = cha180; a[2] = cha270;
		float smalls = cha0;
		for (int i = 0; i < 4; i++)
		{
			if (a[i] < smalls)
				smalls = a[i];
		}
		if (smalls == cha0)
			num = 0;
		else if (smalls == cha90)
			num = 1;
		else if (smalls == cha180)
			num = 2;
		else if (smalls == cha270)
			num = 3;
	}
	num = num % 4;
	//赋值..
	switch (num)
	{
	case 0:
		angle = 0;
		break;
	case 1:
		angle = 90;
		break;
	case 2:
		angle = 180;
		break;
	case 3:
		angle = 270;
		break;
	}

	float radian = CC_DEGREES_TO_RADIANS(angle) + getPhysicsBody()->getRotation();
	auto done = CallFuncN::create([=](Ref* ref){

		float velocity = VELOCITY;
		velocity *= (float)(rand() % 5 + 5) / 10;
		Vec2 origin = Vec2(velocity, 0);
		Vec2 offset = origin.rotateByAngle(Vec2::ZERO, radian);
		getPhysicsBody()->resetForces();
		getPhysicsBody()->setVelocity(offset);
	});
	Sequence* seq;
	switch (num)
	{
	case 0:
		seq = Sequence::create(ScaleTo::create(compressTime, compressY, compressX), done, ScaleTo::create(stretchTime, stretchY, stretchX), ScaleTo::create(recoverTime, 1, 1), NULL, NULL);
		break;
	case 1:
		seq = Sequence::create(ScaleTo::create(compressTime, compressX, compressY), done, ScaleTo::create(stretchTime, stretchX, stretchY), ScaleTo::create(recoverTime, 1, 1), NULL, NULL);
		break;
	case 2:
		seq = Sequence::create(ScaleTo::create(compressTime, compressY, compressX), done, ScaleTo::create(stretchTime, stretchY, stretchX), ScaleTo::create(recoverTime, 1, 1), NULL, NULL);
		break;
	case 3:
		seq = Sequence::create(ScaleTo::create(compressTime, compressX, compressY), done, ScaleTo::create(stretchTime, stretchX, stretchY), ScaleTo::create(recoverTime, 1, 1), NULL, NULL);
		break;
	}
	__fishSprite->runAction(seq);
}
void Fish::dead(float delay)
{
	if (_state == Fish::DEAD) return;
	_state = Fish::State::DEAD;
	CallFunc* done = CallFunc::create([&](){
#ifdef LONGBAO
		std::string str;
		Node* rootNode;
		ActionTimeline* action;

		switch (_type)
		{
		case cache::Fish::FishName::BLUE:
			str = "csb/longbao/baozha/lan.csb";	
			break;
		case cache::Fish::FishName::GREEN:
			str = "csb/longbao/baozha/lv.csb";
			break;
		case cache::Fish::FishName::RED:
			str = "csb/longbao/baozha/fen.csb";
			break;
		case cache::Fish::FishName::EYE:
			str = "csb/longbao/baozha/cheng.csb";
			break;
		case  cache::Fish::FishName::DISCO:
			str = "csb/longbao/baozha/lv.csb";
			break;
		default:
			break;
		}

		rootNode = CSLoader::createNode(str);
		action = CSLoader::createTimeline(str);
		rootNode->runAction(action);
		action->gotoFrameAndPlay(0, false);
		rootNode->setPosition(this->getPosition() - Vec2(232, 178));
		//rootNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		getParent()->getParent()->addChild(rootNode);
		rootNode->runAction(Sequence::create(DelayTime::create(0.4), RemoveSelf::create(), NULL));
#endif
#ifdef CANDY
		//粒子效果..
		ParticleSystemQuad * particleSystem = ParticleSystemQuad::create("particle/dead.plist");
		particleSystem->setScale(2.0f);
		particleSystem->setPosition(this->getPosition());
		particleSystem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		getParent()->getParent()->addChild(particleSystem);
#endif
		//播放声音..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::PRESSFISH);
	});
	Sequence*seq = Sequence::create(DelayTime::create(delay), done, DelayTime::create(0.3), RemoveSelf::create(), NULL);
	this->runAction(seq);
}
void Fish::dead(){
	dead(0);
}
void Fish::normal(){
	if (__umgame)
		__umgame->setVisible(true);
	_rage = false;
	_shing = false;
	__fishSprite->removeFromParentAndCleanup(true);
	if (_type == cache::Fish::FishName::DISCO)
		__fishSprite = cache::Fish::getInstance()->getDiscoNormalFish();
	else
	{
		if (_change)
			__fishSprite = cache::Fish::getInstance()->getSmileFish(_type);
		else
			__fishSprite = cache::Fish::getInstance()->getNormalFish(_type);
	}
	unschedule(schedule_selector(Fish::moveChange));
	schedule(schedule_selector(Fish::moveChange), MOTION_DURATION_NORMAL);
	moveChange(0);
	addChild(__fishSprite);
}
void Fish::shock(){
	unschedule(schedule_selector(Fish::moveChange));
	_state == Fish::State::SHOCK;
	__fishSprite->removeFromParentAndCleanup(true);
	if (_type == cache::Fish::FishName::DISCO)
		__fishSprite = cache::Fish::getInstance()->getDiscoPressFish();
	else
		__fishSprite = cache::Fish::getInstance()->getShockFish(_type);
	addChild(__fishSprite);
}
void Fish::rage(){
	_rage = true;
	if (__umgame)
		__umgame->setVisible(false);
	__fishSprite->removeFromParentAndCleanup(true);

	__fishSprite = cache::Fish::getInstance()->getRageFish();

	unschedule(schedule_selector(Fish::moveChange));
	schedule(schedule_selector(Fish::moveChange), MOTION_DURATION_RAGE);
	moveChange(0);
	addChild(__fishSprite);
}

void Fish::pull(Vec2 v){
	__fishSprite->removeFromParentAndCleanup(true);
	if (_type == cache::Fish::FishName::DISCO)
		__fishSprite = cache::Fish::getInstance()->getDiscoNormalFish();
	else
	{
		if (_change)
			__fishSprite = cache::Fish::getInstance()->getSmileFish(_type);
		else
			__fishSprite = cache::Fish::getInstance()->getNormalFish(_type);
	}
	addChild(__fishSprite);
	CallFunc* done = CallFunc::create([&](){
		move();
	});
	this->runAction(Sequence::create(DelayTime::create(2), done, NULL));
	//cache::Music::getInstance()->playEffect(cache::Music::EffectName::PULL);
	_state = Fish::State::MOVE;
	_arrest = Fish::Arrest::NONE;
	getPhysicsBody()->setEnable(true);
	getPhysicsBody()->setVelocity(Vec2(getPositionX() - v.x, getPositionY() - v.y));
}
void Fish::beRound(){
	_arrest = Fish::Arrest::ROUND;
}
void Fish::beCapture(){
	_arrest = Fish::Arrest::CAPTURE;
	getPhysicsBody()->setEnable(false);
}
void Fish::beBomb(){
	_arrest = Fish::Arrest::BOMB;
}
void Fish::beRage(){
	_arrest = Fish::Arrest::RAGE;
	getPhysicsBody()->setEnable(false);
}
int Fish::getID(){
	return _id;
}
int Fish::getType()
{
	return _type;
}
int Fish::getState()
{
	return _state;
}
std::string Fish::getAward()
{
	return _award;
}
bool Fish::isBomb(){
	return (_type == cache::Fish::FishName::DISCO);
}
bool Fish::isCanCatch(){
	//if (_type == Fish::BOMB_FISH) return false;
	if (_state == MOVE){
		return true;
	}
	return false;
}
bool Fish::isCanRound(){
	if (_state == MOVE){
		return true;
	}
	return false;
}
FishData Fish::getFishData(){
	FishData data{ _id, _type, _arrest, _award };
	return data;
}
Rect Fish::getCollision(){
	Size size = Size(260, 180);
	float x = getPositionX() - size.width / 2;
	float y = getPositionY() - size.height / 2;
	Rect rect = Rect(x, y, size.width, size.height);
	return rect;
}

void Fish::shining()
{
	_shing = true;
	unschedule(schedule_selector(Fish::moveChange));
	schedule(schedule_selector(Fish::moveChange), MOTION_DURATION_RAGE);
	moveChange(0);
}
