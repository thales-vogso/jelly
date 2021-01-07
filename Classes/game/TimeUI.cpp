/****************************************************************************
*	@       	       
*	@desc	时间和暂停的ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/TimeUI.h
*	@modify	null
******************************************************************************/
#include "game/TimeUI.h"
#include "popup/Pause.h"
USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
const std::string TimeUI::TIMEUISHOCK = "timeuishock";
bool TimeUI::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	/**  cocostuido原件  */
	Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
	_panel = (Widget*)Main::seekNodeByName(panel, "panel");
	_adblockui = (Widget*)Main::seekNodeByName(panel, ADBLOCK.c_str());
	this->addChild(panel);
	panel->setPosition(Vec2(23,visibleSize.height-125));
	Widget* pause = cocos2d::ui::Helper::seekWidgetByName(_panel, PAUSES);

	Node*second = cocos2d::ui::Helper::seekWidgetByName(_panel, SECOND);
	Node*minute = cocos2d::ui::Helper::seekWidgetByName(_panel, MINUTE);
	Node*secondzero = cocos2d::ui::Helper::seekWidgetByName(_panel, SECONDZERO);
	Node*minutezero = cocos2d::ui::Helper::seekWidgetByName(_panel, MINUTEZERO);
	Node*colon = cocos2d::ui::Helper::seekWidgetByName(_panel, COLON);
    Node*adblock=cocos2d::ui::Helper::seekWidgetByName(_panel, ADBLOCK);
    
    
    if (data::User::getInstance()->getAdblock()) {
        adblock->setVisible(false);
    }
	float scale = second->getScale();

	EventListenerCustom* _listener = EventListenerCustom::create(TimeUI::TIMEUISHOCK, [=](EventCustom* e){
		
		Sequence* a1 = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);
		Sequence* a2 = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);
		Sequence* a3 = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);
		Sequence* a4 = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);
		Sequence* a5 = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);

		second->runAction(a1);
		minute->runAction(a2);
		secondzero->runAction(a3);
		minutezero->runAction(a4);
		colon->runAction(a5);
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

	return true;
}
void TimeUI::clickPause(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	//增加音效..
	cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		this->addChild(Pause::create(), 2000);
	}
}
void TimeUI::timeChange(EventCustom*e)
{
	int time = *(int*)e->getUserData();
	int minute = time / 60;
	int second = time - minute * 60;
	Node* blockMIN = cocos2d::ui::Helper::seekWidgetByName(_panel, MINUTE);
	String* nsMIN = String::createWithFormat("%d", minute);
	const char* smin = nsMIN->getCString();
	TextAtlas  *lamin = dynamic_cast<TextAtlas*>(blockMIN);
	lamin->setString(smin);
	Node* block = cocos2d::ui::Helper::seekWidgetByName(_panel, SECOND);
	String* ns = String::createWithFormat("%d", second);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);
}
TimeUI::~TimeUI()
{
	_eventDispatcher->removeCustomEventListeners(TimeUI::TIMEUISHOCK);
}
void TimeUI::setEndless(bool isendless/*=false*/)
{
	Node*second = cocos2d::ui::Helper::seekWidgetByName(_panel, SECOND);
	Node*minute = cocos2d::ui::Helper::seekWidgetByName(_panel, MINUTE);
	Node*secondzero = cocos2d::ui::Helper::seekWidgetByName(_panel, SECONDZERO);
	Node*minutezero = cocos2d::ui::Helper::seekWidgetByName(_panel, MINUTEZERO);
	Node*colon = cocos2d::ui::Helper::seekWidgetByName(_panel, COLON);
	Node*endless = cocos2d::ui::Helper::seekWidgetByName(_panel, ENDLESS);
	if (isendless)
	{
		secondzero->setVisible(false);
		second->setVisible(false);
		minute->setVisible(false);
		minutezero->setVisible(false);
		colon->setVisible(false);
		endless->setVisible(true);
	}
	else
	{
		secondzero->setVisible(true);
		second->setVisible(true);
		minute->setVisible(true);
		minutezero->setVisible(true);
		colon->setVisible(true);
		endless->setVisible(false);
	}
}
