/****************************************************************************
*	@       	       
*	@desc	跳过界面
*	@date	2014-11-7
*	@author	120101
*	@       	       
*	@file	popup/Skip.cpp
*	@modify	null
******************************************************************************/
#include "popup/Skip.h"
#include "main/Main.h"
namespace popup
{
	USING_NS_CC;
	using namespace ui;
	using namespace cocostudio;
    Skip::~Skip()
    {
        CCLOG("Skip");
        _eventDispatcher->removeEventListener(_listener);

    }

	bool Skip::init(bool isteachlevel)
	{
		if (!Layer::init())
		{
			return false;
		}
        m_bNotPushToColse = false;

		_isTeachLevel = isteachlevel;
		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		addChild(panel, 2,11);

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		Point midPoint = ccp(visibleSize.width * 0.5, visibleSize.height * 0.5);

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

		panel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5) + Vec2(0, visibleSize.height));
		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))), done, NULL);
		panel->runAction(Seq);



		_savePanel = (Widget*)Main::seekNodeByName(panel, "panel");
		Widget* yes = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "yes");
		Widget* no = cocos2d::ui::Helper::seekWidgetByName(_savePanel, "no");
		panel->setPosition(midPoint + Vec2(0, visibleSize.height));
	

		yes->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Skip::yesClick, this)));
		no->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Skip::noClick, this)));

		return true;
	}

	void Skip::noClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			
            if (m_bNotPushToColse) {
                this->closePop();
            }else{
                PopUp* popup = (PopUp*)getParent();
                popup->closeTopPop();
            }
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
	}
	void Skip::yesClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			if (data::User::getInstance()->getFirst())
			{

#ifdef GIFT_POPUE_VETSION
                bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
                
                data::User::getInstance()->setGuide(Guide::FINISH);
                data::User::getInstance()->setFirst(false);
                
                if (isOver) {
                    Scene* scene = Game::createScene();
                    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
                }
                else{
                    //设置监听
                    _listener = EventListenerCustom::create("closeEndless", [=](EventCustom* e){
                        Scene* scene = Game::createScene();
                        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
                    });
                    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
                    
                    EndlessUnlock *endless = EndlessUnlock::create();
                    endless->m_bNotPushToColse = true;
                    this->addChild(endless, 10);
                    
                }
#else
                data::User::getInstance()->setGuide(Guide::FINISH);
                data::User::getInstance()->setFirst(false);
                Scene* scene = Game::createScene();
                Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
#endif
			}
			else
			{
#ifdef GIFT_POPUE_VETSION
                bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
                

                if (isOver) {
                    Scene* scene = Main::createScene();
                    Director::getInstance()->replaceScene(scene);
                }
                else{
                    //设置监听
                    _listener = EventListenerCustom::create("closeEndless", [=](EventCustom* e){
                        Scene* scene = Main::createScene();
                        Director::getInstance()->replaceScene(scene);
                    });
                    _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
                    
                    EndlessUnlock *endless = EndlessUnlock::create();
                    endless->m_bNotPushToColse = true;
                    this->addChild(endless, 10);
                    
                }
#else
                Scene* scene = Main::createScene();
                Director::getInstance()->replaceScene(scene);
#endif
            
//                
//#ifdef GIFT_POPUE_VETSION
//
//                bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
//                if (!isOver) {
//                    Scene* scene = Main::createScene(true);
//                    Director::getInstance()->replaceScene(scene);
//                }
//                else{
//                    Scene* scene = Main::createScene();
//                    Director::getInstance()->replaceScene(scene);
//                }
//#else
//                Scene* scene = Main::createScene();
//                Director::getInstance()->replaceScene(scene);
//#endif
                
                
			}
		}
	}
	void Skip::closePop()
	{
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();
		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			if (_isTeachLevel)
			{
                
                if (m_bNotPushToColse) {
                    this->removeFromParentAndCleanup(true);
                }else{
                    popup->popBack();
                }
                popup->addTopPop(TeachPause::create());
			}
			else
			{
                if (m_bNotPushToColse) {
                    this->removeFromParentAndCleanup(true);
                }else{
                    popup->popBack();
                }
            }
		});
		Sequence* seq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		Sprite* menu = (Sprite*)getChildByTag(11);
		menu->runAction(seq);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(0.5f, 0));
	}
    
    
	Skip* Skip::create(bool/*=false*/ isteach)
	{
		auto pRet = new Skip();
		if (pRet&&pRet->init(isteach))
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			CC_SAFE_DELETE(pRet);
			return nullptr;
		}
	}

}