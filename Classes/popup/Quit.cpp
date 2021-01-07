/****************************************************************************
*	@       	       
*	@desc	退出确认界面
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	gateway/QuitPop.app
*	@modify	null
******************************************************************************/
#include "popup/Quit.h"
#include "AndroidPurchase/AndroidSDKHelper.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
namespace popup{
	const std::string Quit::MOVEIN = "movein";
	const std::string Quit::MOVEOUT = "moveout";
	bool Quit::init()
	{
		if (!Layer::init())
		{
			return false;
		}
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

		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		addChild(panel, 2);

		_savePanel = (Widget*)Main::seekNodeByName(panel, SAVEPANEL);
		Widget* label = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "label");
		Widget* yes = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "yes");
		Widget* no = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "no");
		label->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 458));
		yes->setPosition(Vec2(visibleSize.width*0.5 + 204, visibleSize.height - 679));
		no->setPosition(Vec2(visibleSize.width*0.5 - 204, visibleSize.height - 679));
		_savePanel->setPosition(_savePanel->getPosition() + Vec2(0, visibleSize.height));
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), NULL);
		_savePanel->runAction(Seq);

		yes->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Quit::yesClick, this)));
		no->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Quit::noClick, this)));
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Quit::MOVEIN, nullptr);
		return true;
	}

	void Quit::noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Size visibleSize = Director::getInstance()->getVisibleSize();
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Quit::MOVEOUT, nullptr);
			auto done = CallFuncN::create([&](Ref* ref){
				this->removeFromParentAndCleanup(true);
			});
			//金币窗口..
			Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
			_savePanel->runAction(seq);
			//背景图片..
			Sprite* sprite = (Sprite*)getChildByTag(10);
			sprite->runAction(FadeTo::create(DELTATIME, 0));
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
	}
	void Quit::yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//退出游戏..
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			umeng::MobClickCpp::end();
#endif

#if TARGET_CHANNEL == TARGET_CHANNE_EGAME
            AndroidSDKHelper::sharedHelper()->openQuitLayer();
#else
            Director::getInstance()->end();
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
	}

	void Quit::closePop()
	{
		this->moving = true;
	}
}