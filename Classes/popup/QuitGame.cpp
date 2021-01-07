/****************************************************************************
*	@       	       
*	@desc	退出当前游戏界面
*	@date	2014-11-10
*	@author	120102
*	@       	       
*	@file	popup/QuitGame.app
*	@modify	2014-11-11 by 120101
******************************************************************************/
#include "popup/QuitGame.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string QuitGame::FUNCPAUSE = "pauselayer";
	const std::string QuitGame::ENDGAMETOMAIN = "endgametomain";
	bool QuitGame::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

		/**  场景背景图片  */
		ImageView* bg = ImageView::create("map/mask2048.png");
		bg->setTouchEnabled(true);
		bg->setSwallowTouches(true);
		float scaleX = visibleSize.width / bg->getContentSize().width;
		float scaleY = visibleSize.height / bg->getContentSize().height;
		float scale = scaleX > scaleY ? scaleX : scaleY;
		bg->setScale(scale);
		bg->setOpacity(0);
		FadeTo* fade = FadeTo::create(0.5f, 255 * 0.5);
		bg->runAction(fade);
		bg->setPosition(midPoint);
		addChild(bg, 0, 10);

		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		addChild(panel, 2);
		panel->setPosition(midPoint + Vec2(0, visibleSize.height));

		_panel = (Widget*)Main::seekNodeByName(panel, "panel");
		Widget* label = cocos2d::ui::Helper::seekWidgetByName(_panel, "label");
		Widget* yes = cocos2d::ui::Helper::seekWidgetByName(_panel, "yes");
		Widget* no = cocos2d::ui::Helper::seekWidgetByName(_panel, "no");

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);
		_panel->runAction(Seq);

		//添加按钮事件..
		yes->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(QuitGame::yesClick, this)));
		no->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(QuitGame::noClick, this)));

		return true;
	}

	void QuitGame::noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}
	void QuitGame::yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//返回主菜单   并且  从第一关开始..
			Director::getInstance()->resume();
			auto done = CallFuncN::create([&](Ref* ref){
				Scene* scene = Main::createScene();
				_eventDispatcher->removeCustomEventListeners(data::User::GOLD_CHANGE);
				_eventDispatcher->removeCustomEventListeners(data::Item::ITEM_CHANGE);
				_eventDispatcher->removeCustomEventListeners(data::Game::SCORE_CHANGE);
				_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
				_eventDispatcher->removeCustomEventListeners(Pause::BACK_YOUXI);
				_eventDispatcher->removeCustomEventListeners(Success::NEXTLEVEL);
				_eventDispatcher->removeCustomEventListeners(Fail::RESUMEGAME);
				Director::getInstance()->replaceScene(scene);
			});
			this->runAction(done);
			data::Game::getInstance()->clearUserGame();
			data::Game::getInstance()->cleatUserGameLog();
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ENDGAMETOMAIN, nullptr);
		}
	}
	void QuitGame::closePop()
	{
		this->moving = true;
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
			popup->addTopPop(Pause::create());
		});
		//金币窗口..
		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		_panel->runAction(seq);
		//发送事件  点击暂停按钮..
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(QuitGame::FUNCPAUSE, nullptr);
	}
}