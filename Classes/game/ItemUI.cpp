/****************************************************************************
*	@       	       
*	@desc	道具的ui
*	@date	2014-11-4
*	@author	120102
*	@       	       
*	@file	game/ItemUI.h
*	@modify	null
******************************************************************************/
#include "game/ItemUI.h"
#include "popup/ItemShop.h"
USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
using namespace cocos2d::extension;

const std::string ItemUI::ITEM_CLICK = "itemclick";
const std::string ItemUI::MAINITEMUI = "mainitemui";
const std::string ItemUI::GAMEITEMUI = "gameitemui";
const std::string ItemUI::ITEMSHOCK = "itemshock";

ItemUI* ItemUI::create(Type type)
{
	ItemUI* fish = new ItemUI();
	fish->init(type);
	fish->autorelease();
	return fish;
}

bool ItemUI::init(Type type)
{
	if (!Layer::init())
	{
		return false;
	}
	_evt = new EventDispatcher();
	_evt->setEnabled(true);
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/**  cocostuido原件  */
#ifdef LONGBAO
	PANEL_NAME = "csb/longbao/ui/item.csb";
#endif
#ifdef CANDY
	PANEL_NAME = "csb/game/item.csb";
#endif	
	Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
	_panel = (Widget*)Main::seekNodeByName(panel, "panel");
	this->addChild(panel);
	_panel->setPosition(Vec2(visibleSize.width / 2 - _panel->getContentSize().width / 2, 0));

	// 	_shock = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocknum");
	// 	_bomb = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bombnum");
	// 	_magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magicnum");

	if (type == MAINUI)
	{
		//Widget* bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, BG1);
		//Widget* plus = cocos2d::ui::Helper::seekWidgetByName(_panel, PLUSITEM);
		//bg1->setVisible(false);
		//plus->setVisible(false);
	}
	else
	{
		//setGray();
		// 		int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
		// 		int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
		// 		int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
		// 		int magiclength = magicnum / 10;
		// 		int shocklength = shocknum / 10;
		// 		int bomblength = bombnum / 10;
		//_plusmenu = cocos2d::ui::Helper::seekWidgetByName(_panel, PLUSITEM);
		//Widget* plusbtn = cocos2d::ui::Helper::seekWidgetByName(_panel, "plusbtn");
		//按钮的点击事件..
		//plusbtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemUI::clickPlus, this)));
		_bombmenu = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB);
		_shockmenu = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK);
		_magicmenu = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC);

		_bombui = cocos2d::ui::Helper::seekWidgetByName(_panel, BOMBUI);
		_shockui = cocos2d::ui::Helper::seekWidgetByName(_panel, SHOCKUI);
		_magicui = cocos2d::ui::Helper::seekWidgetByName(_panel, MAGICUI);
		
		_ragegray = cocos2d::ui::Helper::seekWidgetByName(_panel, MAGICGRAY);

		_text = cocos2d::ui::Helper::seekWidgetByName(_panel, TEXT);
		_text->setVisible(false);
		_text4 = cocos2d::ui::Helper::seekWidgetByName(_panel, TEXT4);
		_text4->setVisible(false);

// 		Widget* bombtouch = cocos2d::ui::Helper::seekWidgetByName(_bombmenu, "touch");
// 		Widget* shocktouch = cocos2d::ui::Helper::seekWidgetByName(_shockmenu, "touch");
// 		Widget* magictouch = cocos2d::ui::Helper::seekWidgetByName(_magicmenu, "touch");
		_bombmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemUI::clickBomb, this)));
		_shockmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemUI::clickShock, this)));
		_magicmenu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemUI::clickMagic, this)));
		_ragegray->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(ItemUI::clickMagic, this)));



		_bg = cocos2d::ui::Helper::seekWidgetByName(_panel, BG1);
		// 		this->setLength(shocklength, ITESHOCK);
		// 		this->setLength(bomblength, ITEMBOMB);
		// 		this->setLength(magiclength, ITEMMAGIC);	

		//setBgSize();
		//this->beginCountDown(100, _shockbg);

		//设置监听..
		_listener = EventListenerCustom::create(ItemUI::ITEMSHOCK, [=](EventCustom* e){
			int id = *(int*)e->getUserData();
			Widget* magic = NULL;
			switch (id)
			{
			case Icon::magic:
			{
				magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magiclabel");
				break;
			}
			case Icon::bomb:
			{
				magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bomblabel");
				break;
			}
			case Icon::shock:
			{
				magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocklabel");
				break;
			}

			}
			Sequence* seq = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
			magic->runAction(seq);
		});
		_eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
	}
	return true;
}
void ItemUI::setGray()
{
#ifdef CANDY
	int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magiclabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magiclabel2");
		Node*gray = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg_gray");
		Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg1");
		Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg2");
		Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg3");
		if (magicnum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
			gray->setVisible(true);
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(false);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
			gray->setVisible(false);
		}
	}
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bomblabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bomblabel2");
		Node*gray = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg_gray");
		Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg1");
		Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg2");
		Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg3");
		if (bombnum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
			gray->setVisible(true);
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(false);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
			gray->setVisible(false);
		}
	}
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocklabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocklabel2");
		Node*gray = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg_gray");
		Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg1");
		Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg2");
		Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg3");
		if (shocknum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
			gray->setVisible(true);
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(false);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
			gray->setVisible(false);
		}
	}
#endif

#ifdef LONGBAO
	int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magiclabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magiclabel2");

		if (magicnum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
		}
	}
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bomblabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bomblabel2");

		if (bombnum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
		}
	}
	{
		Node*magic = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocklabel");
		Node*magic2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("shocklabel2");

		if (shocknum == 0)
		{
			magic->setVisible(false);
			magic2->setVisible(true);
		}
		else
		{
			magic->setVisible(true);
			magic2->setVisible(false);
		}
	}
#endif
}
void ItemUI::setLength(int num, std::string str)
{
#ifdef CANDY
	if (str == ITEMMAGIC)
	{
		if (num == 0){

			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg2");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg3");
			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + bg3->getContentSize().width + 45, _magicmenu->getPosition().y + 50));

			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
		else if (num <= 9)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg2");
			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + bg3->getContentSize().width + 50, _magicmenu->getPosition().y + 50));
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
		else if (num >= 10)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg2");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("bg1");
			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + bg3->getContentSize().width + 50, _magicmenu->getPosition().y + 50));
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
	}
	else if (str == ITEMBOMB)
	{
		if (num == 0){
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg2");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg3");
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + bg3->getContentSize().width + 125, _bombmenu->getPosition().y + 20));
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
		else if (num <= 9)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg2");
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + bg3->getContentSize().width + 120, _bombmenu->getPosition().y + 20));

			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
		else if (num >= 10)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg2");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bg1");
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + bg3->getContentSize().width + 130, _bombmenu->getPosition().y + 20));

			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
		}
	}
	else if (str == ITESHOCK)
	{
		if (num == 0){
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg2");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg3");
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);

		}
		else if (num <= 9)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg1");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg2");
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
			_bombmenu->setPosition(Vec2(_shockmenu->getPosition().x + bg3->getContentSize().width + 34, _bombmenu->getPosition().y));

		}
		else if (num >= 10)
		{
			Node*bg1 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg2");
			Node*bg2 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg3");
			Node*bg3 = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("bg1");
			bg1->setVisible(false);
			bg2->setVisible(false);
			bg3->setVisible(true);
			_bombmenu->setPosition(Vec2(_shockmenu->getPosition().x + bg3->getContentSize().width + 34, _bombmenu->getPosition().y));
		}
	}
#endif

#ifdef LONGBAO
	if (str == ITEMMAGIC)
	{
		if (num == 0){

			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + 60 + 45, _magicmenu->getPosition().y + 50));
		}
		else if (num <= 9)
		{
			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + 90 + 45, _magicmenu->getPosition().y + 50));
		}
		else if (num >= 10)
		{
			_plusmenu->setPosition(Vec2(_magicmenu->getPosition().x + 120 + 45, _magicmenu->getPosition().y + 50));
		}
	}
	else if (str == ITEMBOMB)
	{
		if (num == 0){
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + 70 + 125, _bombmenu->getPosition().y + 17));
		}
		else if (num <= 9)
		{
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + 100 + 125, _bombmenu->getPosition().y + 17));
		}
		else if (num >= 10)
		{
			_magicmenu->setPosition(Vec2(_bombmenu->getPosition().x + 130 + 125, _bombmenu->getPosition().y + 17));
		}
	}
	else if (str == ITESHOCK)
	{
		if (num == 0){
			_bombmenu->setPosition(Vec2(_shockmenu->getPosition().x + 70 + 34, _bombmenu->getPosition().y));
		}
		else if (num <= 9)
		{
			_bombmenu->setPosition(Vec2(_shockmenu->getPosition().x + 100 + 34, _bombmenu->getPosition().y));
		}
		else if (num >= 10)
		{
			_bombmenu->setPosition(Vec2(_shockmenu->getPosition().x + 130 + 34, _bombmenu->getPosition().y));
		}
	}
#endif
}

void ItemUI::setBgSize()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point shockpoint = _shockmenu->getPosition();
	Point pluspoint = _magicmenu->getPosition();

	_bg->setContentSize(Size(pluspoint.x - shockpoint.x + 160, 140));
	_panel->setPosition(Vec2(visibleSize.width / 2 - _bg->getContentSize().width / 2, 0));
}

void ItemUI::clickBomb(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		std::string str("bomb");
		_evt->dispatchCustomEvent(ItemUI::ITEM_CLICK, &str);
	}
}
void ItemUI::clickMagic(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		std::string str("magic");
		_evt->dispatchCustomEvent(ItemUI::ITEM_CLICK, &str);
	}
}
void ItemUI::clickShock(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		std::string str("shock");
		_evt->dispatchCustomEvent(ItemUI::ITEM_CLICK, &str);
	}
}
void ItemUI::addListener(const std::string &eventName, const std::function<void(EventCustom*)>& callback){
	_evt->addCustomEventListener(eventName, callback);
}
void ItemUI::clickPlus(Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ItemUI::MAINITEMUI, nullptr);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(ItemUI::GAMEITEMUI, nullptr);
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}
void ItemUI::ItemChange(EventCustom* e)
{
	data::UserItemInfo userItem = *(data::UserItemInfo*)e->getUserData();
	std::stringstream str;
	str << userItem.num;
	Node* block;
	switch (userItem.id)
	{
	case data::Item::ITEM_SHOCK_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK)->getChildByName("lightningnum");
		break;
	case data::Item::ITEM_BOMB_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB)->getChildByName("bombnum");
		break;
	case data::Item::ITEM_RAGE_ID:
		block = cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC)->getChildByName("magicnum");
		break;
	default:
		break;
	}
	TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	la->setString(str.str().c_str());
	str.clear();
}

ItemUI::~ItemUI()
{
	_eventDispatcher->removeEventListener(_listener);
}
void ItemUI::beginCountDown(int time, Node*item)
{

}
Vec2 ItemUI::getPos(int type)
{
	Vec2 pos;
	switch (type)
	{
	case Icon::magic:
	{
		Widget* magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMMAGIC);// ->getChildByName("magiclabel");
		pos = magic->getWorldPosition();
		break;
	}
	case Icon::bomb:
	{
		Widget*magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITEMBOMB);// ->getChildByName("bomblabel");
		pos = magic->getWorldPosition();
		break;
	}
	case Icon::shock:
	{
		Widget*magic = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_panel, ITESHOCK);// ->getChildByName("shocklabel");
		pos = magic->getWorldPosition();
		break;
	}
	}
	return pos;
}
