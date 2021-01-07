/****************************************************************************
*	@       	       
*	@desc	游戏暂停界面
*	@date	2014-10-22
*	@author	120102
*	@       	       
*	@file	popup/Pause.app
*	@modify	2014-11-12 by 120101
******************************************************************************/
#include "popup/Pause.h"// 暂停界面..
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string Pause::GIVEUP = "giveup";
	const std::string Pause::BACK_YOUXI = "backyouxi";
	const std::string Pause::RESUMEENDLESS = "resumeendless";
	bool Pause::init(bool isendless)
	{
		if (!Layer::init())
		{
			return false;
		}
		this->moving = true;
		
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Point midPoint = ccp(visibleSize.width * 0.5, visibleSize.height * 0.5);

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

		/**  cocostuido原件  */
		Node* panel = CSLoader::createNode(PAUSE_NAME.c_str());
		addChild(panel, 1,11);
		panel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5) + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))), done, NULL);
		panel->runAction(Seq);
		Widget* pause = (Widget*)Main::seekNodeByName(panel, "pause");
		cocos2d::ui::Widget* backmenu = cocos2d::ui::Helper::seekWidgetByName(pause, BACK_MENU);
		cocos2d::ui::Widget* backgame = cocos2d::ui::Helper::seekWidgetByName(pause, BACK_GAME);
		cocos2d::ui::Widget* resume = cocos2d::ui::Helper::seekWidgetByName(pause, RESUME);
		cocos2d::ui::Widget* giveup = cocos2d::ui::Helper::seekWidgetByName(pause, GIVEUPGAME);
		cocos2d::ui::Widget* resumelabel = cocos2d::ui::Helper::seekWidgetByName(pause, RESUMELABEL);
		cocos2d::ui::Widget* giveuplabel = cocos2d::ui::Helper::seekWidgetByName(pause, GIVEUPLABEL);

		//  暂停按钮的点击事件..
		backgame->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Pause::clickReback, this)));
		backmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Pause::clickMainMenu, this)));
		giveup->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Pause::clickGiveup, this)));
		resume->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Pause::clickResume, this)));

		if (isendless)
		{
			giveup->setEnabled(false);
			giveup->setVisible(false);
			resume->setEnabled(true);
			resume->setVisible(true);
			resumelabel->setVisible(true);
			giveuplabel->setVisible(false);

		}
		else
		{
			giveup->setEnabled(true);
			giveup->setVisible(true);
			resume->setEnabled(false);
			resume->setVisible(false);
			resumelabel->setVisible(false);
			giveuplabel->setVisible(true);
		}
		return true;
	}
	Pause*Pause::create(bool isendless)
	{
		auto ret = new Pause();

		if (ret && ret->init(isendless)) {
			ret->autorelease();
			return ret;
		}

		CC_SAFE_DELETE(ret);
		return nullptr;
	}
	void Pause::clickGiveup(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			this->moving = true;
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto done = CallFuncN::create([&](Ref* ref){
				this->moving = false;
				PopUp* popup = (PopUp*)getParent();
				popup->popBack();
				popup->addTopPop(QuitGame::create());
			});
			Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
			Sprite* menu = (Sprite*)getChildByTag(11);
			menu->runAction(seq);
		}
	}
	void Pause::clickReback(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			

			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}
	void Pause::clickMainMenu(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			auto done = CallFuncN::create([&](Ref* ref){
				this->removeFromParentAndCleanup(true);
				Scene* scene = Main::createScene();
				Director::getInstance()->replaceScene(scene);
			});
			_eventDispatcher->removeCustomEventListeners(data::User::GOLD_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Item::ITEM_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Game::SCORE_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
			_eventDispatcher->removeCustomEventListeners(Pause::BACK_YOUXI);
			_eventDispatcher->removeCustomEventListeners(Success::NEXTLEVEL);
			_eventDispatcher->removeCustomEventListeners(Fail::RESUMEGAME);
			this->runAction(done);
		}
	}
	void Pause::closePop()
	{
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Pause::BACK_YOUXI, nullptr);
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();			
		});
		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		Sprite* menu = (Sprite*)getChildByTag(11);
		menu->runAction(seq);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(0.5f, 0));		
	}
	void Pause::clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			std::string str = "endlessresume";
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Pause::RESUMEENDLESS, &str);
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
		}
	}
}