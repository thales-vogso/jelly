/****************************************************************************
*	@       	       
*	@desc	爱游戏的关于界面
*	@date	2015-03-30
*	@author	120102
*	@       	       
*	@file	popup/Info.cpp
*	@modify	null
******************************************************************************/
#include "popup/Info.h"
using namespace cocos2d;
using namespace cocostudio;
using namespace  ui;
namespace popup
{
	bool Info::init()
	{
		if (!Layer::init())
		{
			return false;
		}
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
		//添加弹窗..
		_panel = CSLoader::createNode(PANEL_NAME.c_str());
		_panel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*1.5));
		addChild(_panel, 100, 11);
		Widget*closebtn = (Widget*)Main::seekNodeByName(_panel, "closebtn");

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);

		_panel->runAction(Seq);


		closebtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Info::closeBtnClick, this)));
	
		return true;
	}

	void Info::closePop()
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
		_panel->runAction(seq1);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);
	}

	void Info::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}
}