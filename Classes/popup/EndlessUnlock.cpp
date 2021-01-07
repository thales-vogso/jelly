/****************************************************************************
*	@       	2015,青岛UMGame
*	@desc	无尽模式解锁
*	@date	2015-01-21
*	@author	120102
*	@       	       
*	@file	popup/EndlessUnlock.cpp
*	@modify	null
******************************************************************************/
#include "popup/EndlessUnlock.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "Purchase/IOSiAPBridge.h"
#endif

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
#endif
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"

using namespace cocos2d;
using namespace cocostudio;
using namespace  ui;
namespace popup
{
	const std::string EndlessUnlock::ENDLESSBUYSCUUESS = "endlessbuyscuesss";
	bool EndlessUnlock::init()
	{
		if (!Layer::init())
		{
			return false;
		}
        m_bNotPushToColse = false;

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
        //礼包版注释
        bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
#ifdef PACKAGE_VETSION
#else
        isOver = true;
#endif
        if (isOver)
        {
            _panel = CSLoader::createNode(PANEL_NAME.c_str());
            m_bIsDiscount = false;
        }else{
            _panel = CSLoader::createNode("csb/popup/wujinjiesuo.csb");
            m_bIsDiscount = true;
            this->showDiscountWithEndless();
        }

        

		_panel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height*1.5));
		addChild(_panel, 100, 11);
		Widget*closebtn = (Widget*)Main::seekNodeByName(_panel, "closebtn");
		Widget*buybtn = (Widget*)Main::seekNodeByName(_panel, "buybtn");
		Widget*recoverbtn = (Widget*)Main::seekNodeByName(_panel, "recoverbtn");
		Widget*candylabel = (Widget*)Main::seekNodeByName(_panel, "candy");
		Widget*longbaolabel = (Widget*)Main::seekNodeByName(_panel, "xiaolongbao");
		Widget*androidbuy = (Widget*)Main::seekNodeByName(_panel, "androidbuy");

#ifdef LONGBAO
		candylabel->setVisible(false);
		longbaolabel->setVisible(true);

#endif
#ifdef CANDY
		candylabel->setVisible(true);
		longbaolabel->setVisible(false);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		androidbuy->setVisible(true);
		buybtn->setVisible(false);
		recoverbtn->setVisible(false);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
        if (m_bIsDiscount) {
            androidbuy->setVisible(true);
            buybtn->setVisible(false);
            recoverbtn->setVisible(false);
        }
        else
        {
            androidbuy->setVisible(false);
            buybtn->setVisible(true);
            recoverbtn->setVisible(true);
        }

#endif
//#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
//		androidbuy->setVisible(true);
//		buybtn->setVisible(false);
//		recoverbtn->setVisible(false);
//#endif

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);
		_panel->runAction(Seq);


		closebtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(EndlessUnlock::closeBtnClick, this)));
		buybtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(EndlessUnlock::buyClick, this)));
		recoverbtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(EndlessUnlock::recoverClick, this)));
		androidbuy->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(EndlessUnlock::buyClick, this)));

		return true;
	}

	void EndlessUnlock::recoverClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e==cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//TODO
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)

			Size visibleSize = Director::getInstance()->getVisibleSize();
			IOSiAPBridge*bridge = new IOSiAPBridge();
			bridge->requestProducts(12, true);

			auto swallowTouch = HintInfo::create();
			this->addChild(swallowTouch, 200, 1023);

			LabelTTF*paula = LabelTTF::create("正在恢复购买中", "", 100);
			paula->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));
			this->addChild(paula, 201, 1024);
			// paula->runAction(Sequence::create(DelayTime::create(3),RemoveSelf::create(), NULL));

			auto purchaseoverlisenter = [=](EventCustom*e)
			{
				if (getChildByTag(1023) == NULL)
				{
					return;
				}
				auto done = CallFuncN::create([=](Ref* ref){
					Node*node = getChildByTag(1023);
					if (node != NULL)
					{
						getChildByTag(1023)->removeFromParentAndCleanup(true);
					}

				});
				auto dones = CallFuncN::create([=](Ref* ref){
					if (getChildByTag(1024)) {
						getChildByTag(1024)->removeFromParentAndCleanup(true);
					}
				});
				LabelTTF*paula = LabelTTF::create("恢复购买失败..", "", 100);
				paula->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));
				this->addChild(paula, 201);
				paula->runAction(Sequence::create(dones, DelayTime::create(0.4), RemoveSelf::create(), done, NULL));
			};
			_eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEFAIL, purchaseoverlisenter);

			auto purchaseoverlisenters = [=](EventCustom*e)
			{
				if (getChildByTag(1023) == nullptr)
				{
					return;
				}
				auto done = CallFuncN::create([=](Ref* ref){
					Node*node = getChildByTag(1023);
					if (node != NULL)
					{
						getChildByTag(1023)->removeFromParentAndCleanup(true);
                        
                        data::User::getInstance()->setEndlesslock(false);
                        CallFuncN*func = CallFuncN::create([=](Ref*e){
                            PopUp* popup = (PopUp*)getParent();
                            //发送事件  购买成功  通知主界面去掉锁。。。
                            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EndlessUnlock::ENDLESSBUYSCUUESS, nullptr);
                            popup->closeTopPop();
                        });
                        this->runAction(Sequence::create(DelayTime::create(1), func, NULL));
                        
                        
					}

				});
				auto dones = CallFuncN::create([=](Ref* ref){
					if (getChildByTag(1024)) {
						getChildByTag(1024)->removeFromParentAndCleanup(true);
					}
				});
				LabelTTF*paula = LabelTTF::create("恢复购买成功", "", 100);
                data::User::getInstance()->setEndlesslock(false);
                
				paula->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));
				this->addChild(paula, 201);
				paula->runAction(Sequence::create(dones, DelayTime::create(0.6), RemoveSelf::create(), done, NULL));
                
                

				// getChildByTag(1023)->removeFromParentAndCleanup(true);
				// getChildByTag(1024)->removeFromParentAndCleanup(true);

			};
			_eventDispatcher->addCustomEventListener(IOSiAPBridge::RECOVERSUCCESS, purchaseoverlisenters);
#endif
		}

	}

	void EndlessUnlock::buyClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
            /**
             *  注释 安卓不需要的 谢涛注释
             */
            /*
#if (CC_TARGET_PLATFORM!=CC_PLATFORM_IOS)
			//TODO
			Size visibleSize=Director::getInstance()->getVisibleSize();
			IOSiAPBridge*bridge=new IOSiAPBridge();
			bridge->requestProducts(12,false);

			auto swallowTouch = HintInfo::create();
			this->addChild(swallowTouch, 200,1023);

			LabelTTF*paula=LabelTTF::create("正在购买中", "", 100);
			paula->setPosition(Vec2(visibleSize.width/2,visibleSize.height/1.8));
			this->addChild(paula,201,1024);
			// paula->runAction(Sequence::create(DelayTime::create(3),RemoveSelf::create(), NULL));

			auto purchaseoverlisenter = [=](EventCustom*e)
			{
				if (getChildByTag(1023) == NULL)
				{
					return;
				}
				auto done = CallFuncN::create([=](Ref* ref){
					Node*node = getChildByTag(1023);
					if (node != NULL)
					{
						getChildByTag(1023)->removeFromParentAndCleanup(true);
					}
				});
				auto dones = CallFuncN::create([=](Ref* ref){
					if (getChildByTag(1024)) {
						getChildByTag(1024)->removeFromParentAndCleanup(true);
					}
				});
				LabelTTF*paula = LabelTTF::create("付款失败..", "", 100);
				paula->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));
				this->addChild(paula, 201);
				paula->runAction(Sequence::create(dones, DelayTime::create(0.4), RemoveSelf::create(), done, NULL));


			};
			_eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEFAIL, purchaseoverlisenter);


			auto purchaseoverlisenters = [=](EventCustom*e)
			{
				if (getChildByTag(1023) == nullptr)
				{
					return;
				}
				getChildByTag(1023)->removeFromParentAndCleanup(true);
				getChildByTag(1024)->removeFromParentAndCleanup(true);

                data::User::getInstance()->setEndlesslock(false);
                CallFuncN*func = CallFuncN::create([=](Ref*e){
                    PopUp* popup = (PopUp*)getParent();
                    //发送事件  购买成功  通知主界面去掉锁。。。
                    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EndlessUnlock::ENDLESSBUYSCUUESS, nullptr);
                    popup->closeTopPop();
                });
                this->runAction(Sequence::create(DelayTime::create(1), func, NULL));


				data::User::getInstance()->setEndlesslock(false);

			};
			_eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEOVER, purchaseoverlisenters);

#endif
             */
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
            
//            int count = PurchaseManager::getInstance()->getProductCount(kProductIndexEndlessMode);
//            const char *productID = PurchaseManager::getInstance()->getProductID(kProductIndexEndlessMode).c_str();
//            const char *orderId91 = Value((int)time(NULL)).asString().c_str();
//            PurchaseManager::getInstance()->makePurchase(kProductIndexEndlessMode, count, NULL, kBuyMethod91, orderId91);
//            PopUp* popup = (PopUp*)getParent();
//            popup->closeTopPop();
            
            bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
#ifdef PACKAGE_VETSION
#else
            isOver = true;
#endif
            if (isOver)
            {
                PurchaseManager::getInstance()->makePurchase(kProductIndexEndlessMode);

            }else{
                PurchaseManager::getInstance()->makePurchase(kProductIndexLimitedTimeEndlessMode);

            }
            //弹窗层关闭弹窗..
            if (m_bNotPushToColse) {
                this->closePop();
            }else{
                PopUp* popup = (PopUp*)getParent();
                popup->closeTopPop();
            }
//            PopUp* popup = (PopUp*)getParent();
//            popup->closeTopPop();
//            //如果购买成功。。。。
//            data::User::getInstance()->setEndlesslock(false);
//            UserDefault::getInstance()-> setBoolForKey("Discount_WithEndless_IsOver",true);
//            Text* discountText = (Text*)Main::seekNodeByName(_panel, "Text_3");
//            if (discountText) {
//                discountText->setVisible(false);
//                this->unschedule(schedule_selector(EndlessUnlock::updateTime));
//            }
//            
//            CallFuncN*func = CallFuncN::create([=](Ref*e){
//                PopUp* popup = (PopUp*)getParent();
//                //发送事件  购买成功  通知主界面去掉锁。。。
//                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EndlessUnlock::ENDLESSBUYSCUUESS, nullptr);
//                popup->closeTopPop();
//            });
//            this->runAction(Sequence::create(DelayTime::create(1), func, NULL));
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
			//如果购买成功。。。。
			data::User::getInstance()->setEndlesslock(false);
            UserDefault::getInstance()-> setBoolForKey("Discount_WithEndless_IsOver",true);
            Text* discountText = (Text*)Main::seekNodeByName(_panel, "Text_3");
            if (discountText) {
                discountText->setVisible(false);
                this->unschedule(schedule_selector(EndlessUnlock::updateTime));
            }
            
			CallFuncN*func = CallFuncN::create([=](Ref*e){
//				PopUp* popup = (PopUp*)getParent();
				//发送事件  购买成功  通知主界面去掉锁。。。
				Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(EndlessUnlock::ENDLESSBUYSCUUESS, nullptr);
//				popup->closeTopPop();
                if (m_bNotPushToColse) {
                    this->closePop();
                }else{
                    PopUp* popup = (PopUp*)getParent();
                    popup->closeTopPop();
                }
			});
			this->runAction(Sequence::create(DelayTime::create(1), func, NULL));
#endif
		}
	}

	void EndlessUnlock::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
	{
		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
            if (m_bNotPushToColse) {
                this->closePop();
            }else{
                PopUp* popup = (PopUp*)getParent();
                popup->closeTopPop();
            }

		}
	}

	void EndlessUnlock::closePop()
	{
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("closeEndless", nullptr);
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
            if (m_bNotPushToColse) {
                this->removeFromParentAndCleanup(true);
            }else{
                PopUp* popup = (PopUp*)getParent();
                popup->popBack();
            }

		});
		//金币窗口..
		Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), NULL);
		_panel->runAction(seq1);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
		/*Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);*/
	}

	EndlessUnlock::~EndlessUnlock()
	{
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEOVER);
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEFAIL);
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::RECOVERSUCCESS);
#endif
	}
    

    void EndlessUnlock::showDiscountWithEndless()
    {
        std::string overTime = UserDefault::getInstance()->getStringForKey("over_times");
        int isOverTime = Value(overTime.c_str()).asInt();
        m_nUpTime = isOverTime - (int)time(0);
        
        this->setTimeWithStr(m_nUpTime);
        this->schedule(schedule_selector(EndlessUnlock::updateTime), 1);
    }
    void EndlessUnlock::updateTime(float dt)
    {
        
        std::string overTime = UserDefault::getInstance()->getStringForKey("over_times");
        int isOverTime = Value(overTime.c_str()).asInt();
        m_nUpTime = isOverTime - (int)time(0);
        if (m_nUpTime<=0) {
            UserDefault::getInstance()-> setBoolForKey("Discount_WithEndless_IsOver",true);
            Text* discountText = (Text*)Main::seekNodeByName(_panel, "Text_3");
            discountText->setVisible(false);
            this->unschedule(schedule_selector(EndlessUnlock::updateTime));
            PopUp* popup = (PopUp*)getParent();
            popup->closeTopPop();
        }
        this->setTimeWithStr(m_nUpTime);
    }
    
    void EndlessUnlock::setTimeWithStr(int number)
    {
        
        Text* discountText = (Text*)Main::seekNodeByName(_panel, "Text_3");
        if (discountText) {
            int hour=0;
            int minute=0;
            int second=0;
            hour = number/3600;
            minute = (number-(3600*hour))/60;
            second = (number-(3600*hour)-(60*minute));
            String* ns = String::createWithFormat("剩余时间：%.2d:%.2d:%.2d", hour,minute,second);
            
            //    discountText->setVisible(false);
            discountText->setString(ns->getCString());
        }
        
    }
}


