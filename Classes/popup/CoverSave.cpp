/****************************************************************************
*	@       	       
*	@desc	覆盖存档确认界面
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	game/CoverSavePop.cpp
*	@modify	null
******************************************************************************/
#include "popup/CoverSave.h"

USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;

namespace popup{
	CoverSave* CoverSave::create(int id)
	{
		CoverSave *pRet = new CoverSave();
		if (pRet && pRet->init(id))
		{
			pRet->autorelease();
			return pRet;
		}
	}

	bool CoverSave::init(int id)
	{
		if (!Layer::init())
		{
			return false;
		}
		this->moving = true;
		_ID = id;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);
		Vec2 origin = Director::getInstance()->getVisibleOrigin();

		/**  场景背景图片  */
		ImageView* bg = ImageView::create("map/mask2048.png");
		bg->setTouchEnabled(true);
		bg->setSwallowTouches(true);
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
		addChild(panel, 2);

		_savePanel = (Widget*)Main::seekNodeByName(panel, SAVEPANEL);
		_savePanel->setPosition(midPoint + Vec2(0,500));
		_savePanel->setPosition(_savePanel->getPosition() + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);
		_savePanel->runAction(Seq);
		
		Node* bar1 = Main::seekNodeByName(panel,BAR);
		Widget* panel1 = (Widget*)Main::seekNodeByName(bar1, "panel");
		Widget* bar2 = (Text*)cocos2d::ui::Helper::seekWidgetByName(panel1, "bar");
		Widget* bar = bar2->clone();
		bar->setPosition(Vec2(-421,-500));
		_savePanel->addChild(bar);
		std::vector<UMGDBRow> saveData = data::Game::getInstance()->getGameSaves();
		UMGDBRow row = saveData[_ID - 1];
		Text* text = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, LEVEL_TEXT);
		text->setString(row["stage"].asString());
		Text* text_score = (Text*)cocos2d::ui::Helper::seekWidgetByName(bar, SCORE_TEXT);
		text_score->setString(row["score"].asString());
		//调整框大小..
		int stage = row["stage"].asInt();
		Widget* fly = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "fly");
		Widget* whitebar = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "whitebar");
		Widget* scorelabel = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "scorelabel");
		Widget* score = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "score");
		Widget* guan = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "guan");
		Widget* level = (Widget*)cocos2d::ui::Helper::seekWidgetByName(bar, "level");
		if (stage < 10)
		{
			fly->setContentSize(Size(232, 90));
			whitebar->setContentSize(Size(160, 90));
		}
		else if (stage < 100)
		{
			fly->setContentSize(Size(232, 90) + Size(27, 0));
			whitebar->setContentSize(Size(160, 90) + Size(27, 0));
		}
		else
		{
			fly->setContentSize(Size(232, 90) + Size(54, 0));
			whitebar->setContentSize(Size(160, 90) + Size(54, 0));
		}
		scorelabel->setPosition(Vec2(fly->getContentSize().width + 36, 46));
		score->setPosition(scorelabel->getPosition() + Vec2(120, 0));
		guan->setPosition(guan->getPosition() + Vec2(level->getContentSize().width - 22, 0));

		//添加按钮事件..
		Widget* yes = cocos2d::ui::Helper::seekWidgetByName(_savePanel, YES);
		yes->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(CoverSave::yesClick, this)));
		Widget* no = cocos2d::ui::Helper::seekWidgetByName(_savePanel, NO);
		no->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(CoverSave::noClick, this)));

		return true;
	}

	void CoverSave::noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}

	void CoverSave::yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			if (data::User::getInstance()->goldReduce(SAVECOST))
			{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
				umeng::MobClickCpp::use("save", 1, 5);
#endif
				this->moving = true;
				//增加存档..
				data::Game::getInstance()->modifyGameSave(_ID);

				Size visibleSize = Director::getInstance()->getVisibleSize();

				auto done = CallFuncN::create([&](Ref* ref){
					this->moving = false;
					PopUp* popup = (PopUp*)getParent();
					popup->popBack();
					popup->addTopPop(Success::create());
				});
				//金币窗口..
				Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
				_savePanel->runAction(seq);
				//背景图片..
				Sprite* sprite = (Sprite*)getChildByTag(10);
				sprite->runAction(FadeTo::create(DELTATIME, 0));
			}
			else
			{
				PopUp* popup = (PopUp*)getParent();
				popup->addTopPop(GoldShop::create());
			}
		}
	}
	void CoverSave::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
			popup->addTopPop(Save::create());
		});
		//金币窗口..
		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		_savePanel->runAction(seq);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
	}

}