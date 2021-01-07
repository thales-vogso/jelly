/****************************************************************************
*	@       	       
*	@desc	umgame系统
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/UmGame.cpp
*	@modify	null
******************************************************************************/
#include "game/UmGameUI.h"
#include "game/GoldUI.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

UmGameUI* UmGameUI::create(bool guide)
{
	UmGameUI* pRet = new UmGameUI();
	pRet->_guide = guide;
	if (pRet && pRet->init())
	{		
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}

}
bool UmGameUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
	/**  cocostuido原件  */
	 _umgameUI = CSLoader::createNode(PANEL_NAME.c_str());
	_umgame = (Widget*)_umgameUI->getChildByName("panel");

	this->addChild(_umgameUI);

	changeUmGame();
	return true;
}
void UmGameUI::addUmGame(std::string str, Vec2 pos)
{
	Node* u = _umgame->getChildByName("u");
	Node* m1 = _umgame->getChildByName("m1");
	Node* g = _umgame->getChildByName("g");
	Node* a = _umgame->getChildByName("a");
	Node* m2 = _umgame->getChildByName("m2");
	Node* e = _umgame->getChildByName("e");

	if (str == "U")
		u->setOpacity(GET);
	else if (str == "M")
	{
		if (m1->getOpacity() == GET)
			m2->setOpacity(GET);
		else
			m1->setOpacity(GET);
	}
	else if (str == "G")
		g->setOpacity(GET);
	else if (str == "A")
		a->setOpacity(GET);
	else if (str == "E")
		e->setOpacity(GET);

	if (u->getOpacity() == GET && m1->getOpacity() == GET &&
		g->getOpacity() == GET && a->getOpacity() == GET &&
		m2->getOpacity() == GET && e->getOpacity() == GET)
	{
		u->setOpacity(NOGET);
		m1->setOpacity(NOGET);
		g->setOpacity(NOGET);
		a->setOpacity(NOGET);
		m2->setOpacity(NOGET);
		e->setOpacity(NOGET);
		ParticleSystemQuad * particleSystem = ParticleSystemQuad::create("particle/dead.plist");
		particleSystem->setScale(1.5f);
		particleSystem->setPosition(Vec2(_umgame->getContentSize().width*0.5, _umgame->getContentSize().height*0.5));
		particleSystem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(particleSystem);
	}
	else
	{
		ParticleSystemQuad * particleSystem = ParticleSystemQuad::create("particle/dead.plist");
		particleSystem->setScale(0.5f);
		particleSystem->setPosition(pos);
		particleSystem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		this->addChild(particleSystem);
	}
}
void UmGameUI::changeUmGame()
{
	if (_guide)
	{
		setUmgameNull();
		return;
	}

	Node* u = _umgame->getChildByName("u");
	Node* m1 = _umgame->getChildByName("m1");
	Node* g = _umgame->getChildByName("g");
	Node* a = _umgame->getChildByName("a");
	Node* m2 = _umgame->getChildByName("m2");
	Node* e = _umgame->getChildByName("e");

	UMGDBRow umgame = data::UmGame::getInstance()->getUmGame();

	if (umgame["u"].asInt() == 1)
		u->setOpacity(GET);
	else
		u->setOpacity(NOGET);

	if (umgame["m"].asInt() == 1)
	{
		m1->setOpacity(GET);
		m2->setOpacity(NOGET);
	}
	else if (umgame["m"].asInt() == 2)
	{
		m1->setOpacity(GET);
		m2->setOpacity(GET);
	}
	else
	{
		m1->setOpacity(NOGET);
		m2->setOpacity(NOGET);
	}
	if (umgame["g"].asInt() == 1)
		g->setOpacity(GET);
	else
		g->setOpacity(NOGET);
	if (umgame["a"].asInt() == 1)
		a->setOpacity(GET);
	else
		a->setOpacity(NOGET);
	if (umgame["e"].asInt() == 1)
		e->setOpacity(GET);
	else
		e->setOpacity(NOGET);
}
void UmGameUI::getLetter(std::string str)
{
	if (!_guide)
		data::UmGame::getInstance()->addLetter(str);

	int gold = 1;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
	Layer* layer = (Layer*)getParent()->getChildByName("fly");
	Node* price = CSLoader::createNode(PRICE_NAME.c_str());
	price->retain();
	if (layer->getChildrenCount() == 0)
		layer->addChild(price);
	else
	{
		auto done = CallFuncN::create([=](Ref* ref){
			layer->addChild(price);
		});
		this->runAction(Sequence::create(DelayTime::create(1.5), done, NULL));
	}
	_price = (Widget*)price->getChildByName("panel");
	_num = (Text*)_price->getChildByName("num");
	_letter = (Sprite*)_price->getChildByName("UM");
	_coin = (Widget*)_price->getChildByName("coin");

	_price->setOpacity(0);
	_price->setPosition(midPoint + Vec2(0,-150));

	Vec2 pos = Vec2::ZERO;
	Node* u = _umgame->getChildByName("u");
	Node* m1 = _umgame->getChildByName("m1");
	Node* g = _umgame->getChildByName("g");
	Node* a = _umgame->getChildByName("a");
	Node* m2 = _umgame->getChildByName("m2");
	Node* e = _umgame->getChildByName("e");
	Node* bg = _price->getChildByName("bg");
	Text* num = (Text*)_price->getChildByName("num");

	Node* des = NULL;
	if (str == "U")
	{
		des = u;
	}
	else if (str == "M")
	{
		if (m1->getOpacity() == GET)
		{
			des = m2;
		}
		else
		{
			des = m1;
		}
	}
	else if (str == "G")
	{
		des = g;
	}
	else if (str == "A")
	{
		des = a;
	}
	else if (str == "E")
	{
		des = e;
	}
	int old = des->getOpacity();
	des->setOpacity(GET);
	if (u->getOpacity() == GET && m1->getOpacity() == GET &&
		g->getOpacity() == GET && a->getOpacity() == GET &&
		m2->getOpacity() == GET && e->getOpacity() == GET)
	{
		num->setString("+10");
		gold = 10;
	}
	des->setOpacity(old);

	if (str == "U" && u->getOpacity() == NOGET)
		pos = u->getPosition();
	else if (str == "M" && m2->getOpacity() == NOGET)
	{
		if (m1->getOpacity() == GET)
			pos = m2->getPosition();
		else
			pos = m1->getPosition();
	}
	else if (str == "G" && g->getOpacity() == NOGET)
		pos = g->getPosition();
	else if (str == "A" && a->getOpacity() == NOGET)
		pos = a->getPosition();
	else if (str == "E" && e->getOpacity() == NOGET)
		pos = e->getPosition();

	std::stringstream letter;
	letter << "pic/public/UM_" << str << ".png";
	_letter->setTexture(letter.str().c_str());
	auto move = CallFuncN::create([=](Ref* ref){
		num->runAction(FadeOut::create(0.5f));
		bg->runAction(FadeOut::create(0.5f));
		if (pos == Vec2::ZERO)
			_letter->runAction(FadeOut::create(0.5f));
		if (pos != Vec2::ZERO)
		{
			auto letterdone = CallFuncN::create([=](Ref* ref){
				addUmGame(str, pos);
				_letter->setVisible(false);
			});
			ScaleTo* scale = ScaleTo::create(MOVEDELTATIME, 1);
			MoveBy* move = MoveBy::create(MOVEDELTATIME, _umgame->getPosition() - _price->getPosition() + pos - _letter->getPosition());
			_letter->runAction(Sequence::create(Spawn::create(scale, move, NULL), letterdone, NULL));
		}
		if (gold == 1)
		{
			auto done = CallFuncN::create([=](Ref* ref){
				if (!_guide){
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
					umeng::MobClickCpp::bonus(gold,1);
#endif
					data::User::getInstance()->goldPlus(gold);
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::GOLDSHOCK, nullptr);
				}
				else
				{
					int row = 1;
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::GOLDPLUS, &row);
				}
				price->removeFromParentAndCleanup(true);

			});
			GoldUI* goldUI = (GoldUI*)getParent()->getChildByName("goldUI");
			Vec2 endPos = goldUI->getIconPos();
			MoveBy* move = MoveBy::create(MOVEDELTATIME, endPos - _coin->getWorldPosition());
			_coin->runAction(Sequence::create(move, done, NULL));
		}
		else if (gold == 10)
		{
			auto done = CallFuncN::create([=](Ref* ref){
				price->removeFromParentAndCleanup(true);
			});
			_coin->runAction(Sequence::create(FadeOut::create(0.5f), DelayTime::create(1), done, NULL));
			schedule(schedule_selector(UmGameUI::moveCoin), 0.1f, 10, 0);
		}
	});
	_price->runAction(Sequence::create(Spawn::create(MoveBy::create(0.5, Vec2(0, 300)), FadeIn::create(0.5), NULL), DelayTime::create(0.5f), move, NULL));
}
void UmGameUI::setUmgameNull()
{
	Node* u = _umgame->getChildByName("u");
	Node* m1 = _umgame->getChildByName("m1");
	Node* g = _umgame->getChildByName("g");
	Node* a = _umgame->getChildByName("a");
	Node* m2 = _umgame->getChildByName("m2");
	Node* e = _umgame->getChildByName("e");

	u->setOpacity(NOGET);
	m1->setOpacity(NOGET);
	m2->setOpacity(NOGET);
	g->setOpacity(NOGET);
	a->setOpacity(NOGET);
	e->setOpacity(NOGET);
}

void UmGameUI::moveCoin(float a)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	Widget* coin = _coin->clone();
	coin->setOpacity(255);
	coin->setPosition(midPoint + Vec2(0,150));
	this->getParent()->addChild(coin, 100);
	auto done = CallFuncN::create([=](Ref* ref){
		coin->removeFromParentAndCleanup(true);

		if (!_guide)
		{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			umeng::MobClickCpp::bonus(1, 1);
#endif
			data::User::getInstance()->goldPlus(1);
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::GOLDSHOCK, nullptr);
		}
		else
		{
			int row = 1;
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::GOLDPLUS, &row);
		}
});
	GoldUI* goldUI= (GoldUI*)getParent()->getChildByName("goldUI");
	Vec2 endPos = goldUI->getIconPos();
	MoveBy* move = MoveBy::create(MOVEDELTATIME, endPos - coin->getWorldPosition());
	coin->runAction(Sequence::create(move, done, NULL));
}
Node* UmGameUI::getUmgameUI()
{
	return _umgameUI;
}