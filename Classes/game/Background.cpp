/****************************************************************************
*	@       	       
*	@desc	背景类
*	@date	2014-11-17
*	@author	120102
*	@       	       
*	@file	game/Background.cpp
*	@modify	null
******************************************************************************/
#include "game/Background.h"
USING_NS_CC;
bool Background::init()
{
	if (!Layer::init())
	{
		return false;
	}
	randBg();
	changeBgState();
	return true;
}
void Background::changeBgState(State state)
{
	if (_bg) this->removeAllChildren();
	ParticleSystemQuad* particle;
	Size size = Director::getInstance()->getVisibleSize();
	
	Sprite*sprite;
	TintTo*tint1;
	TintTo*tint2;
	TintTo*tint3;
	Sequence*seq;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	switch (state)
	{
	case Background::NORMAL:
#ifdef LONGBAO
		_bg = Sprite::create("map/map7.jpg");
#endif
#ifdef CANDY
		_bg = Sprite::create(_pis);
#endif
		break;
	case Background::BOMB:
		_bg = Sprite::create(_pis);
		break;
	case Background::SHOCK:
#ifdef LONGBAO
		_bg = Sprite::create("map/map3_blur.jpg");
#endif
#ifdef CANDY
		_bg = Sprite::create("map/map3_blur.jpg");
#endif
		_bg->setOpacity(0);
		particle = ParticleSystemQuad::create("particle/shock.plist");
		particle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		particle->setPosition(Vec2(size.width / 2, size.height / 2));
		this->addChild(particle, 20);
		particle->setScale(1.5);
		_bg->runAction(FadeIn::create(1));
		break;
	case Background::SHING:
		_bg = Sprite::create("map/map2_blur.jpg");
		particle = ParticleSystemQuad::create("particle/shing.plist");
		particle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		particle->setPosition(Vec2(size.width / 2, size.height / 2));
		this->addChild(particle, 20);
		particle->setScale(1.5);
		_bg->setOpacity(0);
		_bg->runAction(FadeIn::create(1));
		break;
	case Background::RAGE:
		_bg = Sprite::create("map/map6_blur.jpg");
		_bg->setOpacity(0);
		_bg->runAction(Sequence::create(FadeIn::create(1),NULL));
#ifdef CANDY
		particle = ParticleSystemQuad::create("particle/rage.plist");
		particle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		particle->setPosition(Vec2(size.width / 2, size.height / 2));
		this->addChild(particle, 20);
#endif
		//particle->setScale(1.5);
		break;
	case Background::MAIN:
#ifdef LONGBAO
		_bg = Sprite::create("map/map7.jpg");
#endif
#ifdef CANDY
		_bg = Sprite::create("map/map2_blur.jpg");
#endif		
		break;
	case Background::LOADING:
#ifdef LONGBAO
		_bg = Sprite::create("map/map7.jpg");
#endif
#ifdef CANDY
		_bg = Sprite::create("map/map2_blur.jpg");
#endif		
		break;
	case Background::NEWBIE:
		_bg = Sprite::create("map/map5_blur.jpg");
		break;
		
	default:
		break;
	}
	Size winsize = Director::sharedDirector()->getVisibleSize();
	_bg->setPosition(ccp(winsize.width / 2, winsize.height / 2));
	float scaleX = visibleSize.width / _bg->getContentSize().width;
	float scaleY = visibleSize.height / _bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	_bg->setScale(scale);
	this->addChild(_bg, 1);

}

void Background::randBg()
{

	int randNum = rand() % 5 + 1;

	sprintf(_pis, "map/map%d_blur.jpg", randNum);
}
