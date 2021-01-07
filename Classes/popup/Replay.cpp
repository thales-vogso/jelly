/****************************************************************************
*	@       	       
*	@desc	重玩确认界面
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	game/ReplayPop.cpp
*	@modify	null
******************************************************************************/
#include "popup/Replay.h"

USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string Replay::RESUMEGAME = "resumegame_replay";
	bool Replay::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

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

		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		addChild(panel, 2);

		_savePanel = (Widget*)Main::seekNodeByName(panel, SAVEPANEL);
		_savePanel->setPosition(midPoint + Vec2(0, 441));
		_savePanel->setPosition(_savePanel->getPosition() + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);
		_savePanel->runAction(Seq);

		//添加按钮事件..
		Widget* yes = cocos2d::ui::Helper::seekWidgetByName(_savePanel, YES);
		yes->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Replay::yesClick, this)));
		Widget* no = cocos2d::ui::Helper::seekWidgetByName(_savePanel, NO);
		no->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Replay::noClick, this)));

		return true;
	}

	void Replay::noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}

	void Replay::yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			if (data::User::getInstance()->goldReduce(SAVECOST))
			{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)

				umeng::MobClickCpp::use("successResume", 1, 5);
#endif
				Size visibleSize = Director::getInstance()->getVisibleSize();
				UMGDBRow row = data::Game::getInstance()->getUserGame();
				int stagenum = row["stage"].asInt();
				data::Game::getInstance()->setStage(stagenum - 1);

				std::string str("reback");
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Replay::RESUMEGAME, &str);

				auto done = CallFuncN::create([&](Ref* ref){
					PopUp* popup = (PopUp*)getParent();
					popup->popBack();		
				});
				//金币窗口..
				Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
				_savePanel->runAction(seq);
				//背景图片..
				Sprite* sprite = (Sprite*)getChildByTag(10);
				sprite->runAction(FadeTo::create(DELTATIME, 0));
			
			}
			else
			{
				PopUp* popup = (PopUp*)getParent();
				popup->addTopPop(GoldShop::create());
			}
		}
	}

	void Replay::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
			popup->addTopPop(Success::create());
		});
		//金币窗口..
		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		_savePanel->runAction(seq);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));	
	}
}
