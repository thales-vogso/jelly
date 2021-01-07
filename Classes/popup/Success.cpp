/****************************************************************************
*	@       	       
*	@desc	游戏胜利界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	popup/Success.app
*	@modify	null
******************************************************************************/
#include "popup/Success.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string Success::NEXTLEVEL = "nextlevel";
	const std::string Success::RESUMEGAME = "resumegame_success";
	bool Success::init()
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

		/**  cocostuido原件  */
		Node* success = CSLoader::createNode(PANEL_NAME.c_str());
		addChild(success, 2, 11);
		Widget* menu = (Widget*)Main::seekNodeByName(success, SUCCESS);
		Widget* nextBtn = cocos2d::ui::Helper::seekWidgetByName(menu, NEXTBTN);
		Widget* saveBtn = cocos2d::ui::Helper::seekWidgetByName(menu, SAVEBTN);
		Widget* replayBtn = cocos2d::ui::Helper::seekWidgetByName(menu, REPLAYBTN);

		//设置按钮的位置   ..

		success->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5) + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))), done, NULL);
		success->runAction(Seq);


		//按钮的点击事件..
		nextBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Success::clickReback, this)));
		saveBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Success::clickSave, this)));
		replayBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Success::clickResume, this)));
		return true;
	}

	//重玩本关..
	void Success::clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			auto done = CallFuncN::create([&](Ref* ref){
				UMGDBRow row = data::Game::getInstance()->getUserGame();
				int stagenum = row["stage"].asInt();
				if (stagenum==2)
				{
					//
					data::Game::getInstance()->setStage(1);
					std::string str("reback");
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Success::RESUMEGAME, &str);
					this->moving = true;
					Size visibleSize = Director::getInstance()->getVisibleSize();
					auto done = CallFuncN::create([=](Ref* ref){
						this->moving = false;

						PopUp* popup = (PopUp*)this->getParent();
						popup->popBack();						
					});
					Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
					Sprite* menu = (Sprite*)getChildByTag(11);
					menu->runAction(seq);
					//背景图片..
					Sprite* sprite = (Sprite*)getChildByTag(10);
					sprite->runAction(FadeTo::create(0.5f, 0));					
				}
				else if (stagenum>=3)
				{
					this->moving = true;
					Size visibleSize = Director::getInstance()->getVisibleSize();
					auto done = CallFuncN::create([=](Ref* ref){
						this->moving = false;
						PopUp* popup = (PopUp*)this->getParent();
						popup->popBack();
						popup->addTopPop(Replay::create());
					});
					Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
					Sprite* menu = (Sprite*)getChildByTag(11);
					menu->runAction(seq);
					//背景图片..
					Sprite* sprite = (Sprite*)getChildByTag(10);
					sprite->runAction(FadeTo::create(0.5f, 0));		
				}				
			});
			this->runAction(done);
		}
	}
	// 下一关..
	void Success::clickReback(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){

			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}
	void Success::clickSave(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
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
				popup->addTopPop(Save::create());
			});
			Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
			Sprite* menu = (Sprite*)getChildByTag(11);
			menu->runAction(seq);
			//背景图片..
			Sprite* sprite = (Sprite*)getChildByTag(10);
			sprite->runAction(FadeTo::create(0.5f, 0));
		}
	}
	void Success::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

		std::string str("next");
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Success::NEXTLEVEL, &str);

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


