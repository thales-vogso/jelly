/****************************************************************************
*	@       	       
*	@desc	游戏失败界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	game/FailPop.h
*	@modify	null
******************************************************************************/
#include "popup/Fail.h"
#include "popup/Quit.h"

USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
const std::string Fail::RESUMEGAME = "resumegame_fail";
const std::string Fail::ENDGAMETOMAIN = "endgametomain";
namespace popup{
	bool Fail::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

		this->moving = true;

		/**  场景背景图片  */
		ImageView* bg = ImageView::create("map/mask2048.png");
		bg->setTouchEnabled(true);
		bg->setSwallowTouches(true);
		float scaleX = visibleSize.width / bg->getContentSize().width;
		float scaleY = visibleSize.height / bg->getContentSize().height;
		float scale = scaleX > scaleY ? scaleX : scaleY;
		bg->setScale(scale);
		bg->setOpacity(0);
		FadeTo* fade = FadeTo::create(0.5f, 255 * 0.8);
		bg->runAction(fade);
		bg->setPosition(midPoint);
		addChild(bg, 0, 10);

		/**  cocostuido原件  */
		Node* fail = CSLoader::createNode(PANEL_NAME.c_str());
		Widget* menu = (Widget*)Main::seekNodeByName(fail, FAIL);
		_replayBton = cocos2d::ui::Helper::seekWidgetByName(menu, REPLAYBTN);
		_replayBtonCopy = cocos2d::ui::Helper::seekWidgetByName(menu, "replayBtn_Copy");
		_closeBtn = cocos2d::ui::Helper::seekWidgetByName(menu, CLOSEBTN);
		_goldpanel = _replayBton->getChildByName(GOLDPANEL);
		_guidelabel = cocos2d::ui::Helper::seekWidgetByName(menu, "guidelabel");
		_line = cocos2d::ui::Helper::seekWidgetByName(menu, "line");
		//设置按钮的位置   ..
		addChild(fail, 2,11);
		fail->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5) + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))), done, NULL);
		fail->runAction(Seq);

		//按钮的点击事件..
		_replayBtonCopy->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Fail::clickResume, this)));
		_replayBton->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Fail::clickResume, this)));
		_closeBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Fail::clickMainMenu, this)));

		return true;

	}

	void Fail::clickResume(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			Size visibleSize = Director::getInstance()->getVisibleSize();
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

	        bool row = data::User::getInstance()->getFirstFail();
			

			Sprite* sprite = (Sprite*)getChildByTag(11);

			if (row == true)
			{
				this->moving = true;
				std::string str("reback");
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Fail::RESUMEGAME, &str);
				auto done = CallFuncN::create([&](Ref* ref){
					this->moving = false;
					PopUp* popup = (PopUp*)getParent();
					popup->popBack();
				});
				Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
				sprite->runAction(seq);
				//背景图片..
				Sprite* sprite1 = (Sprite*)getChildByTag(10);
				sprite1->runAction(FadeTo::create(0.5f, 0));
			}
			else
			{
				if (data::User::getInstance()->goldReduce(10))
				{
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
					umeng::MobClickCpp::use("failResume", 1, 10);
#endif
					this->moving = true;
					std::string str("reback");
					Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Fail::RESUMEGAME, &str);
					auto done = CallFuncN::create([&](Ref* ref){
						this->moving = false;
						PopUp* popup = (PopUp*)getParent();
						popup->popBack();
					});
					Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
					sprite->runAction(seq);
					//背景图片..
					Sprite* sprite1 = (Sprite*)getChildByTag(10);
					sprite1->runAction(FadeTo::create(0.5f, 0));
				}
				else
				{
					PopUp* popup = (PopUp*)getParent();
					popup->addTopPop(GoldShop::create());
				}
			}
		}
	}

	void Fail::clickMainMenu(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}

	void Fail::closePop()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){

			Scene* scene = Main::createScene();

			_eventDispatcher->removeCustomEventListeners(data::User::GOLD_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Item::ITEM_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Game::SCORE_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Game::STAGE_CHANGE);
			_eventDispatcher->removeCustomEventListeners(data::Game::TIME_CHANGE);
			Director::getInstance()->replaceScene(scene);
		});
		this->runAction(done);
		data::Game::getInstance()->clearUserGame();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ENDGAMETOMAIN, nullptr);
		
	}

	void Fail::onEnter()
	{
		Size size = Director::getInstance()->getVisibleSize();
		Layer::onEnter();
		bool  row = data::User::getInstance()->getFirstFail();
		if (row==true)
		{
			_goldpanel->setVisible(false);
			_closeBtn->setVisible(false);
			_guidelabel->setVisible(true);
			_guidelabel->setVisible(true);
			_replayBtonCopy->setVisible(true);
			_line->setVisible(false);
			_replayBton->setVisible(false);
			//_replayBton->setPosition(Vec2(size.width / 2, _goldpanel->getPositionY()));
		}
		else
		{
			_line->setVisible(true);
			_goldpanel->setVisible(true);
			_guidelabel->setVisible(false);
			_guidelabel->setVisible(false);
		}
	}
}
 