/****************************************************************************
*	@       	       
*	@desc	道具商店
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	shop/ItemShop.h
*	@modify	null
******************************************************************************/
#include "popup/ItemShop.h"

USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;

namespace popup
{
	const std::string ItemShop::GAMERESUME = "gamesesume";
	bool ItemShop::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		this->moving = true;

		/**  场景背景图片  */
		auto bg = Sprite::create("map/mask2048.png");
		float scaleX = visibleSize.width / bg->getContentSize().width;
		float scaleY = visibleSize.height / bg->getContentSize().height;
		float scale = scaleX > scaleY ? scaleX : scaleY;
		bg->setScale(scale);
		bg->setOpacity(0);
		FadeTo* fade = FadeTo::create(DELTATIME, 255 * 0.5);
		bg->runAction(fade);
		bg->setPosition(midPoint);
		addChild(bg, 0, 10);

		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		panel->setPosition(Vec2(0, visibleSize.height));
		addChild(panel, 2);
		_itemPanel = (Widget*)Main::seekNodeByName(panel, ITEMPANEL);
		_itemPanel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 30));
		_itemTip = (Widget*)Main::seekNodeByName(panel, TIP);
		_itemTip->setPosition(Vec2(26 + 10, visibleSize.height - 26 - 10));
		TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_itemTip, "label");
		TextAtlas* addTouch = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_itemTip, "touch");
		addTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::changeGoldShop, this)));
		int gold = data::User::getInstance()->getGold();
		std::stringstream str;
		str << gold;
		moneyText->setString(str.str().c_str());

		//给三个条目加事件..
		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar");
			Widget* bar_money = cocos2d::ui::Helper::seekWidgetByName(bar, "money");
			Widget* bar_add = cocos2d::ui::Helper::seekWidgetByName(bar, "add");
			Widget* add_touch = cocos2d::ui::Helper::seekWidgetByName(bar_add, "touch");
			Widget* bar_min = cocos2d::ui::Helper::seekWidgetByName(bar, "min");
			Widget* min_touch = cocos2d::ui::Helper::seekWidgetByName(bar_min, "touch");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			{
				int num = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
				if (num > 999)
					num = 999;
				std::stringstream str;
				str << num;
				bar_item->setString(str.str().c_str());
			}
			bar_money->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::goodsClick, this)));
			add_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::addClick, this)));
			min_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::minClick, this)));
		}
		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_0");
			Widget* bar_money = cocos2d::ui::Helper::seekWidgetByName(bar, "money");
			Widget* bar_add = cocos2d::ui::Helper::seekWidgetByName(bar, "add");
			Widget* add_touch = cocos2d::ui::Helper::seekWidgetByName(bar_add, "touch");
			Widget* bar_min = cocos2d::ui::Helper::seekWidgetByName(bar, "min");
			Widget* min_touch = cocos2d::ui::Helper::seekWidgetByName(bar_min, "touch");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			{
				int num = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
				if (num > 999)
					num = 999;
				std::stringstream str;
				str << num;
				bar_item->setString(str.str().c_str());
			}
			bar_money->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::goodsClick, this)));
			add_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::addClick, this)));
			min_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::minClick, this)));
		}
		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_1");
			Widget* bar_money = cocos2d::ui::Helper::seekWidgetByName(bar, "money");
			Widget* bar_add = cocos2d::ui::Helper::seekWidgetByName(bar, "add");
			Widget* add_touch = cocos2d::ui::Helper::seekWidgetByName(bar_add, "touch");
			Widget* bar_min = cocos2d::ui::Helper::seekWidgetByName(bar, "min");
			Widget* min_touch = cocos2d::ui::Helper::seekWidgetByName(bar_min, "touch");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			{
				int num = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
				if (num > 999)
					num = 999;
				std::stringstream str;
				str << num;
				bar_item->setString(str.str().c_str());
			}
			bar_money->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::goodsClick, this)));
			add_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::addClick, this)));
			min_touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::minClick, this)));
		}

		refreshItemBar();

		//关闭按钮加事件..
		Widget* close = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, CLOSE);
		close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemShop::closeBtnClick, this)));

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);

		panel->runAction(Seq);

		//设置监听..
		_goldlistener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
			//金钱显示改变..
			int gold = data::User::getInstance()->getGold();
			TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_itemTip, "label");
			std::stringstream str;
			str << gold;
			moneyText->setString(str.str().c_str());
		});
		_eventDispatcher->addEventListenerWithFixedPriority(_goldlistener, 1);

		//禁止触摸层..
// 		Widget* touchLayer = Widget::create();
// 		touchLayer->setTouchEnabled(true);
// 		touchLayer->setSwallowTouches(true);
// 		touchLayer->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
// 		touchLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
// 		addChild(touchLayer, 1);

		return true;
	}

	void ItemShop::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}

	void ItemShop::goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Widget* buy = (Widget*)ref;
			Widget* bar = (Widget*)buy->getParent();
			Text* bar_id = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "id");
			Text* bar_num = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "num");
			TextAtlas* bar_money = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "label");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int id = atoi(bar_id->getString().c_str());
			//道具的数量..
			int num = atoi(bar_num->getString().c_str());
			int money = atoi(bar_money->getString().c_str());
			UMGDBRow goodData = data::Shop::getInstance()->getGoodById(id);
			//TODO
			//道具的ID..
			int itemNum=goodData["goodid"].asInt();	
			
			//道具的单价..
			int price = money / num;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			if (itemNum == 1)
			{
				umeng::MobClickCpp::buy("shock", num, price);
			}
			else if (itemNum == 2)
			{
				umeng::MobClickCpp::buy("bomb", num, price);
			}
			else if (itemNum == 3)
			{
				umeng::MobClickCpp::buy("rage", num, price);
			}
#endif
			if (!data::User::getInstance()->goldReduce(money))
			{
				//弹窗层增加弹窗..
				PopUp* popup = (PopUp*)getParent();
				popup->addTopPop(GoldShop::create());
				return;
			}
			bar_num->setString("5");
			//金钱显示改变..
			int gold = data::User::getInstance()->getGold();
			TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_itemTip, "label");
			std::stringstream str;
			str << gold;
			moneyText->setString(str.str().c_str());
			//物品改变..
			data::Item::getInstance()->add(goodData["goodid"].asInt(), num, data::Item::MethodType::BUY);
			int itemnum = data::Item::getInstance()->getUserItemNumByItemID(goodData["goodid"].asInt());
			if (itemnum > 999)
				itemnum = 999;
			std::stringstream str1;
			str1 << itemnum;
			bar_item->setString(str1.str().c_str());
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			refreshItemBar();
			//物品飞行..
			Widget* item = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "item");
			Widget* icon = (Widget*)cocos2d::ui::Helper::seekWidgetByName(item, "icon");
			Widget* icon_clone = icon->clone();
			addChild(icon_clone,100);
			icon_clone->setPosition(icon->getWorldPosition());
			Node* parent = getParent()->getParent()->getChildByName("gateway");
			if (parent == NULL)
				parent = getParent()->getParent();
			ItemUI* itemUI = (ItemUI*)parent->getChildByName("itemUI");
			Vec2 endPos = itemUI->getPos(id);	 
			auto done = CallFuncN::create([=](Ref* ref)
			{
				icon_clone->removeFromParentAndCleanup(true);
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ItemUI::ITEMSHOCK,(void*)&id);
			});
			icon_clone->runAction(Sequence::create(MoveTo::create(1, endPos), done, NULL));
		}
	}

	void ItemShop::minClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Widget* buy = (Widget*)ref;
			Widget* bar = (Widget*)buy->getParent()->getParent();
			Text* bar_id = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "id");
			Text* bar_num = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "num");
			TextAtlas* bar_money = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "label");
			int id = atoi(bar_id->getString().c_str());
			int num = atoi(bar_num->getString().c_str());
			if (num == 5)
				return;
			int num1 = num - 5;

			UMGDBRow goodData = data::Shop::getInstance()->getGoodById(id);

			int money1 = atoi(bar_money->getString().c_str());
			int money2 = goodData["price"].asInt();
			int money3 = money1 - money2;
			{
				std::stringstream str;
				str << money3;
				bar_money->setString(str.str().c_str());
			}
			{
				std::stringstream str;
				str << num1;
				bar_num->setString(str.str().c_str());
			}
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
	}

	void ItemShop::addClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Widget* buy = (Widget*)ref;
			Widget* bar = (Widget*)buy->getParent()->getParent();
			Text* bar_id = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "id");
			Text* bar_num = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, "num");
			TextAtlas* bar_money = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "label");
			int id = atoi(bar_id->getString().c_str());
			int num1 = atoi(bar_num->getString().c_str());
			if (num1 == 100)
				return;
			int num = num1 + 5;

			UMGDBRow goodData = data::Shop::getInstance()->getGoodById(id);

			int money1 = atoi(bar_money->getString().c_str());
			int money2 = goodData["price"].asInt();
			int money3 = money1 + money2;
			{
				std::stringstream str;
				str << money3;
				bar_money->setString(str.str().c_str());
			}
			{
				std::stringstream str;
				str << num;
				bar_num->setString(str.str().c_str());
			}
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
	}

	void ItemShop::changeGoldShop(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//弹窗层增加弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->addTopPop(GoldShop::create());
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
	}

	ItemShop::~ItemShop()
	{
		_eventDispatcher->removeEventListener(_goldlistener);
	}

	void ItemShop::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
		});
		//金币窗口..
		Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), NULL);
		_itemPanel->runAction(seq1);
		_itemTip->runAction(seq2);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ItemShop::GAMERESUME, nullptr);
	}

	void ItemShop::refreshItemBar()
	{
#ifdef CANDY
		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar");
			Widget* bar_blue = cocos2d::ui::Helper::seekWidgetByName(bar, "blue");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black1");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_blue->setContentSize(Size(98, 75));
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_blue->setContentSize(Size(98, 75) + Size(33, 0));
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_blue->setContentSize(Size(98, 75) + Size(66, 0));
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}

		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_0");
			Widget* bar_blue = cocos2d::ui::Helper::seekWidgetByName(bar, "red");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black2");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_blue->setContentSize(Size(98, 75));
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_blue->setContentSize(Size(98, 75) + Size(33, 0));
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_blue->setContentSize(Size(98, 75) + Size(66, 0));
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}

		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_1");
			Widget* bar_blue = cocos2d::ui::Helper::seekWidgetByName(bar, "yellow");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black3");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_blue->setContentSize(Size(98, 75));
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_blue->setContentSize(Size(98, 75) + Size(33, 0));
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_blue->setContentSize(Size(98, 75) + Size(66, 0));
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}
#endif

#ifdef LONGBAO
		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black1");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}

		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_0");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black2");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}

		{
			Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_itemPanel, "bar_1");
			Widget* bar_black = cocos2d::ui::Helper::seekWidgetByName(bar, "black3");
			TextAtlas* bar_item = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(bar, "itemnum");
			int num = atoi(bar_item->getString().c_str());
			if (num < 10)
			{
				bar_black->setContentSize(Size(240, 140));
			}
			else if (num < 100)
			{
				bar_black->setContentSize(Size(240, 140) + Size(33, 0));
			}
			else
			{
				bar_black->setContentSize(Size(240, 140) + Size(66, 0));
			}
		}
#endif
	}
}