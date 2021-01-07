/****************************************************************************
*	@       	       
*	@desc	存档界面
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	game/SavePop.app
*	@modify	null
******************************************************************************/
#include "popup/Save.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	bool Save::init()
	{
		if (!Layer::init())
		{
			return false;
		}
		this->moving = true;
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
		FadeTo* fade = FadeTo::create(0.5f, 255 * 0.5);
		bg->runAction(fade);
		bg->setPosition(midPoint);
		addChild(bg, 0, 10);

		/**  加载弹窗  */
		_panel = CSLoader::createNode(PANEL_NAME.c_str());
		Widget* savePanelFromFile = (Widget*)Main::seekNodeByName(_panel, SAVEPANEL);
		_savePanel = savePanelFromFile->clone();
		//创建列表容器..
		_listView = ListView::create();
		_listView->setAnchorPoint(Vec2(0, 0));
		_listView->setContentSize(Size(900, 650));
		_listView->setPosition(Vec2(-430, -955));
		_listView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);
		_listView->setItemsMargin(15);
		_savePanel->addChild(_listView);
		//确定标题..
		Widget* loadText = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "loadText");
		loadText->setVisible(false);
		Widget* emptyText = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "emptyText");
		emptyText->setVisible(false);
		_savePanel->setPosition(Vec2(visibleSize.width*0.5,visibleSize.height-30));
		_savePanel->setPosition(_savePanel->getPosition() + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);
		_savePanel->runAction(Seq);
		addChild(_savePanel, 2);

		refreshSave();

		Widget* close = cocos2d::ui::Helper::seekWidgetByName(_savePanel, CLOSE);
		close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Save::closeBtnClick, this)));

		////触摸关闭商店层..
		//Widget* touchLayer = Widget::create();
		//touchLayer->setTouchEnabled(true);
		//touchLayer->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
		//touchLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
		//touchLayer->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Save::closeBtnClick, this)));
		//addChild(touchLayer, 1);
		return true;
	}

	void Save::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
		}
	}

	void Save::goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
		if (e == cocos2d::ui::Widget::TouchEventType::BEGAN)
		{
			Node* node = (Node*)ref;
			node->setOpacity(node->getOpacity()*0.8);
		}
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Node* node = (Node*)ref;
			node->setOpacity(node->getOpacity()/0.8);
			Size visibleSize = Director::getInstance()->getVisibleSize();
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			auto done = CallFunc::create([=]{

				Widget* money = (Widget*)ref;
				Text* gid = (Text*)money->getChildByName("id");
				int id = atoi(gid->getString().c_str());
				if (id == -1)
				{
					PopUp* popup = (PopUp*)getParent();
					popup->popBack();
					popup->addTopPop(EmptySave::create());
				}
				else
				{
					PopUp* popup = (PopUp*)getParent();
					popup->popBack();
					popup->addTopPop(CoverSave::create(id));
				}
			});
			//金币窗口..
			Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
			_savePanel->runAction(seq);
			//背景图片..
			Sprite* sprite = (Sprite*)getChildByTag(10);
			sprite->runAction(FadeTo::create(DELTATIME, 0));
		}
	}

	void Save::refreshSave()
	{
		_listView->removeAllChildren();		
		Node* bar1 = Main::seekNodeByName(_panel, BAR);
		Widget* panel = (Widget*)Main::seekNodeByName(bar1, "panel");
		Widget* bar = (Text*)cocos2d::ui::Helper::seekWidgetByName(panel, "bar");
		Widget* emptybar = (Widget*)Main::seekNodeByName(_panel, EMPTYBAR);
		/**  加载存档条目  */
		std::vector<UMGDBRow> saveData = data::Game::getInstance()->getGameSaves();
		int num = saveData.size();
		for (int i = 0; i < num; i++)
		{
			Widget* barClone = bar->clone();
			barClone->setTouchEnabled(true);
			_listView->addChild(barClone);
			Text* id = (Text*)barClone->getChildByName("id");
			std::stringstream str;
			str << i + 1;
			id->setString(str.str());
			UMGDBRow row = saveData[i];
			Text* text = (Text*)cocos2d::ui::Helper::seekWidgetByName(barClone, LEVEL_TEXT);
			text->setString(row["stage"].asString());
			Text* text_score = (Text*)cocos2d::ui::Helper::seekWidgetByName(barClone, SCORE_TEXT);
			text_score->setString(row["score"].asString());
			barClone->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Save::goodsClick, this)));
			//调整框大小..
			int stage = row["stage"].asInt();
			Widget* fly = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "fly");
			Widget* whitebar = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "whitebar");
			Widget* scorelabel = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "scorelabel");
			Widget* score = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "score");
			Widget* guan = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "guan");
			Widget* level = (Widget*)cocos2d::ui::Helper::seekWidgetByName(barClone, "level");
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
			score->setPosition(scorelabel->getPosition()+Vec2(120,0));
			guan->setPosition(guan->getPosition() + Vec2(level->getContentSize().width - 22, 0));

		}
		if (num < 10)
		{
			//加载空存档..
			Widget* barClone = emptybar->clone();
			barClone->setTouchEnabled(true);
			_listView->addChild(barClone);
			barClone->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Save::goodsClick, this)));

			if (num <= 3)
			{
				for (int i = 1; i <= 2 - num; i++)
				{
					Widget* barClone = emptybar->clone();
					barClone->setTouchEnabled(true);
					_listView->addChild(barClone);
					barClone->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Save::goodsClick, this)));
				}
			}
		}
		_listView->refreshView();
	}

	void Save::closePop()
	{
		this->moving = true;
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
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}