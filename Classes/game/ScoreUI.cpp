/****************************************************************************
*	@       	       
*	@desc   分数的ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/ScoreUI.h
*	@modify	null
******************************************************************************/
#include "game/ScoreUI.h"
#include "main/Main.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
const std::string ScoreUI::SCOREUISHOCK = "scoreuishock";
bool ScoreUI::init()
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
	this->addChild(panel);
	_panel->setPosition(Vec2(visibleSize.width-26,visibleSize.height-26));

	_stage = cocos2d::ui::Helper::seekWidgetByName(_panel, LEVEL);
	_target = cocos2d::ui::Helper::seekWidgetByName(_panel, TOTLESCORE);
	Widget* totlescore = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, "cuscore");
	float scale = totlescore->getScale();
	EventListenerCustom* _listener = EventListenerCustom::create(ScoreUI::SCOREUISHOCK, [=](EventCustom* e){
		
		Sequence* a = Sequence::create(ScaleTo::create(0.3, scale*1.2), ScaleTo::create(0.3, scale*0.8), ScaleTo::create(0.2, scale*1.1), ScaleTo::create(0.2, scale), NULL);
        if (totlescore) {
            totlescore->runAction(a);
        }
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
	fixPosition();
	return true;
}
void ScoreUI::stageChange(EventCustom*e)
{
	int stage = *(int*)e->getUserData();
	TextAtlas* block = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_panel, LEVEL)->getChildByName("levelnum");
	Widget*dd = (Widget*)block;
	
	String* ns = String::createWithFormat("%d", stage);
	const char* s = ns->getCString();
	block->setString(s);
	this->setTotleScore(stage);
}
void ScoreUI::ScoreChange(EventCustom* e)
{
	int score = *(int*)e->getUserData();
	this->changeScore(score);
}
void ScoreUI::setTotleScore(int stage)
{
	int totle = data::Game::getInstance()->getTotleScore();
	Node* block = cocos2d::ui::Helper::seekWidgetByName(_panel, TOTLESCORE)->getChildByName("totlenum");
	String* ns = String::createWithFormat("%d", totle);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);

	fixPosition();
}

ScoreUI::~ScoreUI()
{
	_eventDispatcher->removeCustomEventListeners(TimeUI::TIMEUISHOCK);
	_eventDispatcher->removeCustomEventListeners(data::Game::SCORE_CHANGE);
	_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
    _eventDispatcher->removeCustomEventListeners(ScoreUI::SCOREUISHOCK);
//    _eventDispatcher->removeAllEventListeners();
}

void ScoreUI::setEndLess(bool  isendless/*  = false  */)
{
	if (isendless)
	{
		_target->setVisible(false);
		_stage->setVisible(false);
	}
	else
	{
		_target->setVisible(true);
		_stage->setVisible(true);
	}
}
void ScoreUI::changeScore(int score)
{
	Node* block = cocos2d::ui::Helper::seekWidgetByName(_panel, CUSCORE);
	String* ns = String::createWithFormat("%d", score);
	const char* s = ns->getCString();
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(s);

	fixPosition();
}

void ScoreUI::fixPosition()
{
	Widget* totlescore = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, "cuscore");
	Widget* totlenum = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, TOTLESCORE)->getChildByName("totlenum");
	Widget* mubiao = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, TOTLESCORE)->getChildByName("mubiao");
	Widget* tanhao = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, TOTLESCORE)->getChildByName("tanhao");
	totlenum->setPosition(tanhao->getPosition() - Vec2(totlenum->getContentSize().width*0.5 - 15, 0));
	mubiao->setPosition(totlenum->getPosition() - Vec2(totlenum->getContentSize().width*0.5 + 20, 0));
	_stage->setPosition(Vec2(totlenum->getPosition().x + 110, _stage->getPosition().y));
	totlescore->setPosition(Vec2(_stage->getPosition().x, totlescore->getPosition().y));
}

Vec2 ScoreUI::getScorePosition()
{
	Widget* totlescore = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, "cuscore");
	return totlescore->getPosition()+_panel->getPosition()-_panel->getContentSize();
}