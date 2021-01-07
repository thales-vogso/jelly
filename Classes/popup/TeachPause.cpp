/****************************************************************************
*	@       	       
*	@desc	新手教程暂停界面的ui
*	@date	2014-12-15
*	@author	120102
*	@       	       
*	@file	popup/TeachPause.cpp
*	@modify	null
******************************************************************************/
#include "popup/TeachPause.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup
{
	const std::string TeachPause::BACKGAME = "backgame";
	const std::string TeachPause::SKIPTEACH = "skipteach";
	const std::string TeachPause::RESUMETEACH = "resumeteach";
	bool TeachPause::init()
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
		addChild(panel, 1, 11);
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
	

 		//继续游戏..
 		backgame->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TeachPause::clickReback, this)));
		//返回主菜单或者是结束教程开始第一关..
		backmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TeachPause::clickSkipTeach, this)));
		//重玩游戏..
		resume->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TeachPause::clickResume, this)));

		return true;
	}

	void TeachPause::closePop()
	{		
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(BACKGAME, nullptr);
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

	void TeachPause::clickReback(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
	
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{		
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			PopUp* popup = (PopUp*)getParent();

			popup->closeTopPop();
		}
	}

	void TeachPause::clickSkipTeach(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(SKIPTEACH, nullptr);
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			this->moving = true;
			Size visibleSize = Director::getInstance()->getVisibleSize();
			auto done = CallFuncN::create([&](Ref* ref){
				this->moving = false;
				PopUp* popup = (PopUp*)getParent();
				popup->popBack();
				popup->addTopPop(Skip::create(true));
			});
			Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
			Sprite* menu = (Sprite*)getChildByTag(11);
			menu->runAction(seq);
			//背景图片..
			Sprite* sprite = (Sprite*)getChildByTag(10);
			sprite->runAction(FadeTo::create(0.5f, 0));			
		}
	}

	void TeachPause::clickResume(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RESUMETEACH, nullptr);
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
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
	}
}