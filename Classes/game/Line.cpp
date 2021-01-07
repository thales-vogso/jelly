/****************************************************************************
*	@       	       
*	@desc	在鱼之间画线
*	@date	2014-10-27
*	@author	110101
*	@       	       
*	@file	game/Line.h
*	@modify	null
******************************************************************************/
#include "game/Line.h"//  画线层..
#include "math.h"
USING_NS_CC;

bool Line::init()
{
	if (!Layer::init())
	{
		return false;
	}

	_isShing = false;

	_factLine = Layer::create();
	addChild(_factLine, 1);
#ifdef CANDY
    _drawLine = Sprite::create("pic/candy/candy_tiao.png");
#endif
#ifdef LONGBAO
    _drawLine = Sprite::create("pic/longbao/candy_tiao.png");
#endif
	LINE_WIDTH = _drawLine->getContentSize().width;
	addChild(_drawLine, 2);
	_particle = Layer::create();
	addChild(_particle, 3);

	_drawLine->setAnchorPoint(Vec2((float)LINE_ANCHOR_X / LINE_WIDTH, 0.5));

	_drawLine->setVisible(false);
	_drawLine->setScaleY(0.8);

	_drawShingLine = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::DISCO);
	addChild(_drawShingLine, 2);
	_drawShingLine->setAnchorPoint(Vec2((float)LINE_ANCHOR_X / LINE_WIDTH, 0.5));
	_drawShingLine->setVisible(false);

	return true;
}
void Line::drawing(Vec2 point){
	if (_nodes.size() == 0){
		return;
	}
	if (_isShing)
	{
		_dragPoint = point;
		Vec2 local = _nodes.at(_nodes.size() - 1);
		float dis = local.getDistance(point);
		float l = atan2(point.y - local.y, point.x - local.x);
		//float l = local.getAngle(v);
		float d = CC_RADIANS_TO_DEGREES(l);
		d = -d;
		_drawShingLine->setPosition(local);
		_drawShingLine->setVisible(true);
		_drawShingLine->setRotation(d);
		float scale = (float)dis / LINE_WIDTH;
		_drawShingLine->setScaleX(scale);
	}
	else
	{
		_dragPoint = point;
		Vec2 local = _nodes.at(_nodes.size() - 1);
		float dis = local.getDistance(point);
		float l = atan2(point.y - local.y, point.x - local.x);
		//float l = local.getAngle(v);
		float d = CC_RADIANS_TO_DEGREES(l);
		d = -d;
		_drawLine->setPosition(local);
		_drawLine->setVisible(true);
		_drawLine->setRotation(d);
		float scale = (float)dis / LINE_WIDTH;
		_drawLine->setScaleX(scale);
	}
}
void Line::drawNode(Vec2 point, int type){
	Sprite* sprite1;
	Sprite*sprite;
	_nodes.push_back(point);
	switch (type)
	{
	case cache::Fish::FishName::DISCO:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::DISCO);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		_isShing = true;
		break;
	case cache::Fish::FishName::GREEN:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::GREEN);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::RED:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::RED);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::BLUE:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BLUE);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::EYE:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::EYE);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::PINK:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PINK);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::YELLOW:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::YELLOW);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::PURPLE:
		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PURPLE);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	case cache::Fish::FishName::BROWN:

		sprite = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BROWN);
		_drawLine->setTexture(sprite->getTexture());
		_drawLine->setColor(sprite->getColor());
		break;
	}

	drawFact(type);
}
void Line::drawFact(int type){

	Sprite* line0;
	Sprite* line1;
	switch (type)
	{
	case cache::Fish::FishName::GREEN:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::GREEN);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::GREEN);
		break;
	case cache::Fish::FishName::RED:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::RED);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::RED);
		break;
	case cache::Fish::FishName::BLUE:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BLUE);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BLUE);
		break;
	case cache::Fish::FishName::EYE:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::EYE);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::EYE);
		break;
	case cache::Fish::FishName::PINK:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PINK);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PINK);
		break;
	case cache::Fish::FishName::YELLOW:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::YELLOW);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::YELLOW);
		break;
	case cache::Fish::FishName::PURPLE:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PURPLE);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::PURPLE);
		break;
	case cache::Fish::FishName::BROWN:
		line0 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BROWN);
		line1 = (Sprite*)cache::Fish::getInstance()->getLine(cache::Fish::FishName::BROWN);
		break;
	}
	if (_nodes.size() < 2) return;
	Vec2 offset = *(_nodes.end() - 1);
	Vec2 origin = *(_nodes.end() - 2);
	float distance = origin.getDistance(offset);

	line0->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);

	line1->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
	line1->setScaleX(-1);

	Sprite* line = Sprite::create();
	line->addChild(line0);
	line->addChild(line1);

	line->setPosition(origin.getMidpoint(offset));
	float scale = (float)distance / ((LINE_WIDTH - LINE_ANCHOR_X) * 2);
	line->setScaleX(scale);
	line->setScaleY(0.8);
	PhysicsBody* body = PhysicsBody::createBox(Size(distance, 20));

	body->setMass(PHYSICS_INFINITY);
	body->setRotationEnable(false);
	line->setPhysicsBody(body);
	float l = atan2(offset.y - origin.y, offset.x - origin.x);
	float d = CC_RADIANS_TO_DEGREES(l);
	d = -d;
	line->setRotation(d);
	_factLine->addChild(line);

}
void Line::drawEnd(){
	_drawLine->setVisible(false);
	_drawShingLine->setVisible(false);
	_isShing = false;
	_factLine->removeAllChildrenWithCleanup(true);
	//effect();
	_nodes.clear();
}
void Line::effect(){
	for (Node* node : _factLine->getChildren()){
		Sequence*seq = Sequence::create(DelayTime::create(1.0f), FadeOut::create(1.0f), RemoveSelf::create(true), NULL, NULL);
		node->runAction(seq);
	}
}
bool Line::isSynezesis(){
	return (*_nodes.begin() == *(_nodes.end() - 1));
}
bool Line::isWebify(cocos2d::Vec2 point){

	if (!_drawLine->isVisible()) return false;
	if (_nodes.size() == 0) return false;
	Vec2 offset = _dragPoint;
	Vec2 origin = *(_nodes.end() - 1);
	float a = point.getDistance(origin);
	float b = point.getDistance(offset);
	float c = origin.getDistance(offset);
	//if (a > c) return false;
	//if (b > c) return false;
	if (a + b - c < HOT_SCOPE){
		float d = a + b - c;
		return true;
	}
	return false;
}
bool Line::isRounded(Vec2 point){
	int nCross = 0;
	int nCount = _nodes.size();
	Vec2 v = point;
	for (int i = 0; i < nCount; i++){
		Vec2 p1 = _nodes[i];
		Vec2 p2 = _nodes[(i + 1) % nCount];
		if (p1.y == p2.y) continue;
		if (v.y < std::min(p1.y, p2.y)) continue;
		if (v.y >= std::max(p1.y, p2.y)) continue;
		double x = (double)(v.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if (x > v.x) nCross++;
	}
	return (nCross % 2 == 1);
}
bool Line::isPointInPolygon(cocos2d::Vec2 point, std::vector<Vec2> vertexs){
	int nCross = 0;
	int nCount = vertexs.size();
	for (int i = 0; i < nCount; i++){
		Vec2 p1 = vertexs[i];
		Vec2 p2 = vertexs[(i + 1) % nCount];
		if (p1.y == p2.y) continue;
		if (point.y < std::min(p1.y, p2.y)) continue;
		if (point.y >= std::max(p1.y, p2.y)) continue;
		double x = (double)(point.y - p1.y) * (double)(p2.x - p1.x) / (double)(p2.y - p1.y) + p1.x;
		if (x > point.x) nCross++;
	}
	return (nCross % 2 == 1);
}