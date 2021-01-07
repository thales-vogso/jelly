/****************************************************************************
*	@       	       
*	@desc	金币的ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/GoldUI.h
*	@modify	null
******************************************************************************/
#include "game/GoldUI.h"
#include "popup/GoldShop.h"

USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
const std::string GoldUI::MAINGOLDUI = "maingoldui";
const std::string GoldUI::GAMEGOLDUI = "gamegoldui";
const std::string GoldUI::GOLDPLUS = "goldplus";
const std::string GoldUI::GOLDSHOCK = "goldshock";
bool GoldUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/**  cocostuido原件  */
#ifdef LONGBAO
	PANEL_NAME = "csb/longbao/ui/gold.csb";
#endif
#ifdef CANDY
	PANEL_NAME = "csb/game/gold.csb";
#endif	
	_panel= CSLoader::createNode(PANEL_NAME.c_str());
	Widget* panel = (Widget*)Main::seekNodeByName(_panel, "gold");
	this->addChild(_panel);

	panel->setPosition(Vec2(visibleSize.width-panel->getContentSize().width,0));
	Widget* menu = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDMENU);
	 _num = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDNUMS);
	 _plus = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDMENUS);
	 _goldlabel = cocos2d::ui::Helper::seekWidgetByName(panel, "goldlabel");

	//按钮的点击事件..
	menu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GoldUI::clickPlus, this)));

	_goldChangeListener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
		int score = *(int*)e->getUserData();
		changeGold(score);
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_goldChangeListener, 1);

	_goldPlusListener = EventListenerCustom::create(GoldUI::GOLDPLUS, [=](EventCustom* e){
		int score = *(int*)e->getUserData();
		goldPlus(score);
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_goldPlusListener, 2);

	_goldShockListener = EventListenerCustom::create(GoldUI::GOLDSHOCK, [=](EventCustom* e){
		_goldlabel->runAction(Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL));
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_goldShockListener, 3);

	changeGold(0);
	return true;
}
void GoldUI::clickPlus(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::MAINGOLDUI, nullptr);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldUI::GAMEGOLDUI, nullptr);
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}
void GoldUI::changeGold(int num)
{	
	String* ns = String::createWithFormat("%d", num);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(_num);
	int oldnum = atoi(la->getString().c_str());
	la->setString(s);
}
void GoldUI::goldPlus(int num)
{
	TextAtlas  *la = dynamic_cast<TextAtlas*>(_num);
	int oldnum = atoi(la->getString().c_str());
	int totle = oldnum + num;
	String* ns = String::createWithFormat("%d", totle);
	const char* s = ns->getCString();	
	la->setString(s);

	_goldlabel->runAction(Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL));
}
GoldUI::~GoldUI()
{
	_eventDispatcher->removeEventListener(_goldChangeListener);
	_eventDispatcher->removeEventListener(_goldPlusListener);
	_eventDispatcher->removeEventListener(_goldShockListener);
}

Vec2 GoldUI::getIconPos()
{
	return _goldlabel->getWorldPosition();
}
