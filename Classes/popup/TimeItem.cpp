/****************************************************************************
*	@       	       
*	@desc	时间道具ui
*	@date	2014-11-7
*	@author	120102
*	@       	       
*	@file	popup/TimeItem.app
*	@modify	2014-11-12 by 120101
******************************************************************************/
#include "popup/TimeItem.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string TimeItem::FAILGAME = "failgame";
	const std::string TimeItem::TIMEPLUS = "againgame";
	bool TimeItem::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		_isFirst = data::User::getInstance()->getFirstTimeItem();
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
		Node* panel1 = CSLoader::createNode(PANEL_NAME.c_str());
		panel1->setPosition(midPoint + Vec2(0, visibleSize.height));
		this->addChild(panel1, 1, 1);
		Widget* panel = (Widget*)Main::seekNodeByName(panel1, "panel");
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))), done, NULL);
		panel->runAction(Seq);

		_time = cocos2d::ui::Helper::seekWidgetByName(panel, TIME);
		_fail = cocos2d::ui::Helper::seekWidgetByName(panel, FAIL);
		_gold = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDPANEL);
		_text = cocos2d::ui::Helper::seekWidgetByName(panel, TEXTLABEL);
		_gold_image = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDIMAGE);
		_gold_text = cocos2d::ui::Helper::seekWidgetByName(panel, GOLDTEXT);
		_labeltext = cocos2d::ui::Helper::seekWidgetByName(panel, TEXTLABEL);
		_timelabel = cocos2d::ui::Helper::seekWidgetByName(panel, TIMELABEL);
		_linelabel = cocos2d::ui::Helper::seekWidgetByName(panel, LINELABEL);
		_time->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TimeItem::clickTime, this)));
		_fail->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(TimeItem::clickFail, this)));
		_guidelabel = cocos2d::ui::Helper::seekWidgetByName(panel, GUIDELABEL);
		return true;
	}
	void TimeItem::clickTime(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Widget* panel = (Widget*)getChildByTag(1);
			PopUp* popup = (PopUp*)getParent();
			if (data::User::getInstance()->getGold() > 5||_isFirst==true)
			{
				//设置时间道具只能点击一次....
				_time->setEnabled(false);
				this->moving = true;
				auto done = CallFuncN::create([=](Ref* ref){
					this->moving = false;
					popup->popBack();
				});
				data::Game::getInstance()->setUseTimeItem(true);
                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(TimeItem::TIMEPLUS, nullptr);
				Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
				panel->runAction(seq);
				//背景图片..
				Sprite* sprite = (Sprite*)getChildByTag(10);
				sprite->runAction(FadeTo::create(0.5f, 0));
			}
			else
			{
				if (data::User::getInstance()->getLibao())
					popup->addTopPop(GoldShop::create(true));
				else
					popup->addTopPop(GoldShop::create(false));
			}
		}
	}
	void TimeItem::clickFail(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}


	TimeItem::~TimeItem()
	{

		//_eventDispatcher->removeCustomEventListeners(TimeItem::TIMEPLUS);

	}
	void TimeItem::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Widget* panel = (Widget*)getChildByTag(1);
		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
			popup->addTopPop(Fail::create());
		});

		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		panel->runAction(seq);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(0.5f, 0));
	}

	void TimeItem::onEnter()
	{
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Layer::onEnter();
		bool isfirst = data::User::getInstance()->getFirstTimeItem();
		
		if (isfirst == true)
		{
			_gold->setVisible(false);
			_gold_image->setVisible(false);
			_gold_text->setVisible(false);
			//_fail->setColor(ccc3(125, 125, 125));
			//_text->setColor(ccc3(125, 125, 125));
			//_text->setVisible(false);
			_text->setVisible(false);
			_fail->setVisible(false);
			_fail->setEnabled(false);
			_guidelabel->setVisible(true);
// 			_fail->setVisible(false);
 			_linelabel->setVisible(false);
 			_time->setPosition(Vec2(_labeltext->getPositionX()-_labeltext->getContentSize().width,_time->getPositionY()));
 			_timelabel->setPosition(Vec2(_time->getPositionX(),_timelabel->getPositionY()));
		}
		else
		{
			_gold->setVisible(true);
			_gold_image->setVisible(true);
			_gold_text->setVisible(true);
			_guidelabel->setVisible(false);
		}
	}
}