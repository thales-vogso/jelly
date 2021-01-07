/****************************************************************************
*	@       	       
*	@desc	
*	@date	2014-11-2
*	@author	120102
*	@       	       
*	@file	
*	@modify	null
******************************************************************************/
#include "popup/ItemInfo.h"
USING_NS_CC;
using namespace cocostudio;
using namespace  ui;
namespace popup{
	const std::string ItemInfo::BACK_GAME = "iteminfobackgame";
	const std::string ItemInfo::USEITEM_BACK_GAME = "useitem_back_game";
	
	ItemInfo* popup::ItemInfo::create(ItemType type)
	{
		ItemInfo *pRet = new ItemInfo();
		if (pRet&&pRet->init(type))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}
	bool ItemInfo::init(ItemType type)
	{
		if (!Layer::init())
		{
			return false;
		}

		_evt = new EventDispatcher();
		_evt->setEnabled(true);
		_type = type;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height*0.5);
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
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
		FadeTo* fade = FadeTo::create(0.5f, 255 * 0.5);
		bg->runAction(fade);
		bg->setPosition(midPoint);
		addChild(bg, 0, 10);
		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		panel->setPosition(Vec2(0, visibleSize.height));
		addChild(panel, 100);
		_goldPanel = (Widget*)Main::seekNodeByName(panel, GOLDPANEL);
		_goldPanel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 30));
		_goldTip = (Widget*)Main::seekNodeByName(panel, TIP);
		_goldTip->setPosition(Vec2(26 + 10, visibleSize.height - 26 - 10));
		_itemLayer = (Widget*)Main::seekNodeByName(panel,ITEMLAYER);

		_itemname =cocos2d::ui::Helper::seekWidgetByName(_itemLayer, ITEMNAME);
		
		Widget* buganduse = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, BUGANDUSE.c_str());
		Widget* confirmmenu = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "buganduse_Copy");
		confirmmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemInfo::buyAndUse, this)));
		buganduse->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemInfo::buyAndUse, this)));
	
		
		Widget*touch = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "touch");
		
		touch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemInfo::showPopup, this)));


		TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "label");
		int gold = data::User::getInstance()->getGold();
		std::stringstream str;
		str << gold;
		moneyText->setString(str.str().c_str());

		setItemUI(_type);
		
		Widget* close = cocos2d::ui::Helper::seekWidgetByName(_goldPanel, CLOSE);
		close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemInfo::closeBtnClick, this)));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);

		panel->runAction(Seq);

		//设置监听
		_goldlistener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
			//金钱显示改变..
			int gold = data::User::getInstance()->getGold();
			TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "label");
			std::stringstream str;
			str << gold;
			moneyText->setString(str.str().c_str());
		});
		_eventDispatcher->addEventListenerWithFixedPriority(_goldlistener, 1);

		return true;
	}
	void ItemInfo::setItemUI(ItemType type)
	{
		ImageView* item = (ImageView*)cocos2d::ui::Helper::seekWidgetByName(_itemLayer, ITEMPIC.c_str());
		Text* moneyText = (Text*)cocos2d::ui::Helper::seekWidgetByName(_itemLayer, ITEMGOLDNUM.c_str());
		Widget* buganduse = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, BUGANDUSE.c_str());
		Widget* confirmmenu = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "buganduse_Copy");
#ifdef LONGBAO
		if (type==BOMB)
		{
			item->loadTexture("pic/longbao/ui/dasuan.png");
			moneyText->setString("X2");
			Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo5");
			moreInfo->setVisible(true);
			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo5");
			itemInfo->setVisible(true);
			buganduse->setVisible(false);
			confirmmenu->setVisible(true);
		}
		else if (type==RAGE)
		{
			item->loadTexture("pic/longbao/ui/kuaizi.png");
			moneyText->setString("X10");
			Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo6");
			moreInfo->setVisible(true);
			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo4");
			itemInfo->setVisible(true);
			buganduse->setVisible(true);
			confirmmenu->setVisible(false);
		}
		else if (type==SHOCK)
		{
			item->loadTexture("pic/longbao/ui/cuping.png");
			moneyText->setString("X6");
			Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo1");
			moreInfo->setVisible(true);
			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo1");
			itemInfo->setVisible(true);
			buganduse->setVisible(true);
			confirmmenu->setVisible(false);
		}
#endif
#ifdef CANDY
		if (type == BOMB)
		{
			item->loadTexture("pic/ui/bomb.png");
			moneyText->setString("X2");
			Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo3");
			moreInfo->setVisible(true);
			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo2");
			itemInfo->setVisible(true);
			buganduse->setVisible(false);
			confirmmenu->setVisible(true);
		}
		else if (type == RAGE)
		{
			item->loadTexture("pic/ui/magic.png");
			moneyText->setString("X10");
			Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo4");
			moreInfo->setVisible(true);
			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo3");
			itemInfo->setVisible(true);
			buganduse->setVisible(true);
			confirmmenu->setVisible(false);
		}
		else if (type == SHOCK)
		{
			item->loadTexture("pic/ui/lightning.png");
			moneyText->setString("X6");
#ifdef LANGUAGE_EN
            Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo1");
            moreInfo->setVisible(true);
#else
            Widget *moreInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "itemmoreinfo3");
            moreInfo->setVisible(true);
#endif

			Widget *itemInfo = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "iteminfo6");
			itemInfo->setVisible(true);
			buganduse->setVisible(true);
			confirmmenu->setVisible(false);
		}
#endif
	}
	void ItemInfo::closePop()
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
		_goldPanel->runAction(seq1);
		_goldTip->runAction(seq2);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);
	}

	void ItemInfo::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}
	void ItemInfo::buyAndUse(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
			//发送使用道具的事件。。。。。
			std::string str;
			if (_type==BOMB)
			{
				 str=("bomb");
			}
			else if (_type==SHOCK)
			{
				str=("shock");
			}
			else if (_type==RAGE)
			{
				str=("magic");
			}

			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ItemInfo::USEITEM_BACK_GAME, &str);
		}
	}
	ItemInfo::~ItemInfo()
	{
		_eventDispatcher->removeEventListener(_goldlistener);
	}

	void ItemInfo::showPopup(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Widget*touch = cocos2d::ui::Helper::seekWidgetByName(_itemLayer, "on");
			if (_type==BOMB)
			{
				if (data::User::getInstance()->getShowBomb())
				{
					data::User::getInstance()->setShowBomb(false);
					touch->setVisible(true);
				}
				else
				{
					data::User::getInstance()->setShowBomb(true);
					touch->setVisible(false);
				}
			}
			else if (_type==RAGE)
			{
				if (data::User::getInstance()->getShowRage())
				{
					data::User::getInstance()->setShowRage(false);
					touch->setVisible(true);
				}
				else
				{
					data::User::getInstance()->setShowRage(true);
					touch->setVisible(false);
				}
			}
			else if (_type==SHOCK)
			{
				if (data::User::getInstance()->getShowShock())
				{
					data::User::getInstance()->setShowShock(false);
					touch->setVisible(true);
				}
				else
				{
					data::User::getInstance()->setShowShock(true);
					touch->setVisible(false);
				}
			}
		}
	}

}
