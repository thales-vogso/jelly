/****************************************************************************
*	@       	       
*	@desc	ios 去广告的付费界面
*	@date	2015-01-16
*	@author	120102
*	@       	       
*	@file	popup/AdBlock.cpp
*	@modify	null
******************************************************************************/
#include "popup/AdBlock.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "Purchase/IOSiAPBridge.h"
#endif
using namespace cocos2d;
using namespace cocostudio;
using namespace  ui;
namespace popup
{
	bool AdBlock::init()
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
		 Widget*buybtn = (Widget*)Main::seekNodeByName(_panel, "buybtn");
		 Widget*recoverbtn = (Widget*)Main::seekNodeByName(_panel, "recoverbtn");

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);

		_panel->runAction(Seq);


		closebtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(AdBlock::closeBtnClick,this)));
		buybtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(AdBlock::buyClick, this)));
		recoverbtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(AdBlock::recoverClick,this)));




		return true;
	}

	void AdBlock::closePop()
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

	void AdBlock::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
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

	void AdBlock::buyClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
// 		umeng...
            Size visibleSize=Director::getInstance()->getVisibleSize();
            IOSiAPBridge*bridge=new IOSiAPBridge();
            bridge->requestProducts(6,false);
            
            auto swallowTouch = HintInfo::create();
            this->addChild(swallowTouch, 200,1023);
            
            LabelTTF*paula=LabelTTF::create("正在购买中", "", 100);
            paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
            this->addChild(paula,201,1024);
            // paula->runAction(Sequence::create(DelayTime::create(3),RemoveSelf::create(), NULL));
            
            auto purchaseoverlisenter = [=](EventCustom*e)
            {
                if(getChildByTag(1023)==NULL)
                {
                    return;
                }
                auto done = CallFuncN::create([=](Ref* ref){
                    Node*node=getChildByTag(1023);
                    if(node!=NULL)
                    {
                        getChildByTag(1023)->removeFromParentAndCleanup(true);
                    }
                    
                });
                auto dones = CallFuncN::create([=](Ref* ref){
                    if (getChildByTag(1024)) {
                        getChildByTag(1024)->removeFromParentAndCleanup(true);
                    }
                });
                LabelTTF*paula=LabelTTF::create("付款失败..", "", 100);
                paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
                this->addChild(paula,201);
                paula->runAction(Sequence::create(dones,DelayTime::create(0.4),RemoveSelf::create(), done,NULL));
                
                
            };
            _eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEFAIL, purchaseoverlisenter);
            
            
            auto purchaseoverlisenters = [=](EventCustom*e)
            {
                if(getChildByTag(1023)==nullptr)
                {
                    return;
                }
                getChildByTag(1023)->removeFromParentAndCleanup(true);
                getChildByTag(1024)->removeFromParentAndCleanup(true);
                data::User::getInstance()->setAdblock(true);
            };
            _eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEOVER, purchaseoverlisenters);
		}
#endif
		
	}
	void AdBlock::recoverClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
            Size visibleSize=Director::getInstance()->getVisibleSize();
            IOSiAPBridge*bridge=new IOSiAPBridge();
            bridge->requestProducts(6,true);
            
            auto swallowTouch = HintInfo::create();
            this->addChild(swallowTouch, 200,1023);
            
            LabelTTF*paula=LabelTTF::create("正在恢复购买中", "", 100);
            paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
            this->addChild(paula,201,1024);
            // paula->runAction(Sequence::create(DelayTime::create(3),RemoveSelf::create(), NULL));
            
            auto purchaseoverlisenter = [=](EventCustom*e)
            {
                if(getChildByTag(1023)==NULL)
                {
                    return;
                }
                auto done = CallFuncN::create([=](Ref* ref){
                    Node*node=getChildByTag(1023);
                    if(node!=NULL)
                    {
                        getChildByTag(1023)->removeFromParentAndCleanup(true);
                    }
                    
                });
                auto dones = CallFuncN::create([=](Ref* ref){
                    if (getChildByTag(1024)) {
                        getChildByTag(1024)->removeFromParentAndCleanup(true);
                    }
                });
                LabelTTF*paula=LabelTTF::create("恢复购买失败..", "", 100);
                paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
                this->addChild(paula,201);
                paula->runAction(Sequence::create(dones,DelayTime::create(0.4),RemoveSelf::create(), done,NULL));
                
                
            };
            _eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEFAIL, purchaseoverlisenter);
            
            
            auto purchaseoverlisenters = [=](EventCustom*e)
            {
                if(getChildByTag(1023)==nullptr)
                {
                    return;
                }
                
                auto done = CallFuncN::create([=](Ref* ref){
                    Node*node=getChildByTag(1023);
                    if(node!=NULL)
                    {
                        getChildByTag(1023)->removeFromParentAndCleanup(true);
                    }
                    
                });
                auto dones = CallFuncN::create([=](Ref* ref){
                    if (getChildByTag(1024)) {
                        getChildByTag(1024)->removeFromParentAndCleanup(true);
                    }
                });
                LabelTTF*paula=LabelTTF::create("恢复购买成功", "", 100);
                data::User::getInstance()->setAdblock(true);
                paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
                this->addChild(paula,201);
                paula->runAction(Sequence::create(dones,DelayTime::create(0.6),RemoveSelf::create(), done,NULL));
                
//                getChildByTag(1023)->removeFromParentAndCleanup(true);
//                getChildByTag(1024)->removeFromParentAndCleanup(true);
               
            };
            _eventDispatcher->addCustomEventListener(IOSiAPBridge::RECOVERSUCCESS, purchaseoverlisenters);
            
            
            
            
		}
#endif
		
	}

	AdBlock::~AdBlock()
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEOVER);
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEFAIL);
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::RECOVERSUCCESS);
#endif
	}

}