//
//  SpecialOfferLayer.cpp
//  jelly3.5
//
//  Created by mac on 15/9/2.
//
//

#include "SpecialOfferLayer.h"
#include <time.h>
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;

namespace popup{
    SpecialOfferLayer::~SpecialOfferLayer()
    {
        _eventDispatcher->removeEventListener(_goldlistener);

    }
    SpecialOfferLayer * SpecialOfferLayer::createWithType(PackageGiftType type)
    {
        SpecialOfferLayer *specialOffer = new SpecialOfferLayer();
        if (specialOffer && specialOffer->init(type)) {
            specialOffer->autorelease();
            return specialOffer;
        }
        else
        {
            delete specialOffer;
            specialOffer = NULL;
            return NULL;
        }
    }
    
    bool SpecialOfferLayer::init(PackageGiftType type)
    {
        if (!Layer::init()) {
            return false;
        }
        this->moving = true;
        m_bNotPushToColse = false;
        m_PackageType = type;
        
        Size visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height*0.5);
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
        
        
        if (m_PackageType == FirstChargePacksType) {
            m_pPanel = CSLoader::createNode("csb/popup/goldshop_0.csb");
            
            this->showFirstChargePacks();
            
        }
        else if (m_PackageType == SpecialOffersType)
        {
            m_pPanel = CSLoader::createNode("csb/popup/goldshop_1.csb");
            this->showSpecialOffers();
            
        }
        
        m_pPanel->setPosition(Vec2(0, visibleSize.height));
        addChild(m_pPanel, 100);
        auto done = CallFuncN::create([=](Ref* ref)
                                      {
                                          this->moving = false;
                                      });
        
        Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))),done, NULL);
        m_pPanel->runAction(Seq);
        return true;
    }
    
    void SpecialOfferLayer::showFirstChargePacks()
    {
        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
        
        Widget* close = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "close");
        close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(SpecialOfferLayer::closeBtnClick, this)));
        
        Widget* goldTip = (Widget*)Main::seekNodeByName(m_pPanel, "tip");

        TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "label");
        int gold = data::User::getInstance()->getGold();
        std::stringstream str;
        str << gold;
        moneyText->setString(str.str().c_str());
        
        //设置监听..
        _goldlistener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
            //金钱显示改变..
            int gold = data::User::getInstance()->getGold();
            TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "label");
            std::stringstream str;
            str << gold;
            moneyText->setString(str.str().c_str());
        });
        
        Widget *_libao = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "libao");
        Widget* anniu = cocos2d::ui::Helper::seekWidgetByName(_libao, "pay");
        anniu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(SpecialOfferLayer::goodsClick, this)));
        
    }
    
    void SpecialOfferLayer::showSpecialOffers()
    {
        time_t now = time(0);
        tm *timeData = localtime(&now);
        
        m_WeekType = (WeekType)timeData->tm_wday;
        m_WeekType = (WeekType)(((int)m_WeekType)?m_WeekType:7);
        CCLOG("SpecialOfferLayer 星期 %d",((int)m_WeekType)?m_WeekType:7);
        
        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
        
        Widget* close = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "close");
        close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(SpecialOfferLayer::closeBtnClick, this)));
        
        Widget* goldTip = (Widget*)Main::seekNodeByName(m_pPanel, "tip");
        
        TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "label");
        int gold = data::User::getInstance()->getGold();
        std::stringstream str;
        str << gold;
        moneyText->setString(str.str().c_str());
        
        //设置监听..
        _goldlistener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
            //金钱显示改变..
            int gold = data::User::getInstance()->getGold();
            TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "label");
            std::stringstream str;
            str << gold;
            moneyText->setString(str.str().c_str());
        });
        
        Widget *_libao = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "libao");
        Widget* anniu = cocos2d::ui::Helper::seekWidgetByName(_libao, "pay");
        anniu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(SpecialOfferLayer::goodsClick, this)));
        
        this->setDisPlayWithWeek(m_WeekType);
        
    }
    
    void SpecialOfferLayer::setDisPlayWithWeek(int week)
    {
        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
        Widget *_libao = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "libao");
        Widget *Sprite_5 = (Widget*)Main::seekNodeByName(_libao, "Sprite_5");
        
        Text *weekText = (Text *)cocos2d::ui::Helper::seekWidgetByName(Sprite_5, "Text_1");
        
        int productIndex = m_WeekType + kProductIndexSpecialOffers_1 - 1;
        int getCoins = PurchaseManager::getInstance()->getProductCount(productIndex);
        int price = (int)PurchaseManager::getInstance()->getProductPrice(productIndex);
        std::string weekStr;
        switch (week) {
            case 1:
                weekStr = "周一..";
                break;
            case 2:
                weekStr = "周二..";
                break;
            case 3:
                weekStr = "周三..";
                break;
            case 4:
                weekStr = "周四..";
                break;
            case 5:
                weekStr = "周五..";
                break;
            case 6:
                weekStr = "周六..";
                break;
            case 7:
                weekStr = "周日..";
                break;
                
            default:
                break;
        }
        weekText->setString(weekStr);
        
        Text *Text_24 = (Text *)cocos2d::ui::Helper::seekWidgetByName(_libao, "Text_24");
        std::string Text_24Str = Value(getCoins).asString() + "金币.";
        Text_24->setString(Text_24Str);
        
        Text *Text_12 = (Text *)cocos2d::ui::Helper::seekWidgetByName(_libao, "Text_12");
        std::string Text_12Str = "￥." + Value(price).asString();
        Text_12->setString(Text_12Str);
        
        Text *Text_2 = (Text *)cocos2d::ui::Helper::seekWidgetByName(_libao, "Text_2");
        Text_2->setString(weekStr);
        
        Text *Text_3 = (Text *)cocos2d::ui::Helper::seekWidgetByName(_libao, "Text_3");
        String *Text_3Str = String::createWithFormat("（内含%d枚金币）..",getCoins);
        Text_3->setString(Text_3Str->getCString());

        
    }
    
    void SpecialOfferLayer::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
        
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
    
    void SpecialOfferLayer::closePop()
    {
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
        Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
        Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), NULL);
        m_pPanel->runAction(seq1);
//        _goldTip->runAction(seq2);
        //背景图片..
        Sprite* sprite = (Sprite*)getChildByTag(10);
        sprite->runAction(FadeTo::create(0.5, 0));
        
//        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);
    }
    void SpecialOfferLayer::goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
        
        if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
        {

//            Widget* money = (Widget*)ref;
            int productIndex = 0;

            if (m_PackageType == FirstChargePacksType) {
                productIndex = kProductIndexFirstCharge;
                if (UserDefault::getInstance()->getBoolForKey("buy_first_charge")) {
                    return;
                }
            }else if(m_PackageType == SpecialOffersType) { 
                productIndex = m_WeekType + kProductIndexSpecialOffers_1 - 1;
                if (m_WeekType == UserDefault::getInstance()->getIntegerForKey("open_specialoffer")) {
                    return;
                }
            }
            int coinnum = PurchaseManager::getInstance()->getProductCount(productIndex);
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//            coinFly(money);
//            data::User::getInstance()->goldPlus(coinnum);
            PurchaseManager::getInstance()->makePurchase(productIndex);

#endif
//            int source = 3;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//            umeng::MobClickCpp::pay(cash, source, coinnum);
#endif
            
            
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//            coinFly(money);
            PurchaseManager::getInstance()->makePurchase(productIndex);
#endif
            //金钱显示改变..
//            int gold = data::User::getInstance()->getGold();
////            Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
//            Widget* goldTip = (Widget*)Main::seekNodeByName(m_pPanel, "tip");
//
//            TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "label");
//            std::stringstream str;
//            str << gold;
//            moneyText->setString(str.str().c_str());
//            //增加音效..
//            cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
//
//
//            Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
//            Widget* moneyIcon = (Widget*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "moneyIcon");
//            Sequence* a = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
//            moneyIcon->runAction(a);
            
//            if (m_PackageType == FirstChargePacksType) {
//                UserDefault::getInstance()->setBoolForKey("buy_first_charge",true);
////                Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(data::User::BUY_FIRST_CHARGE, nullptr);
//                
//                //            //弹窗层关闭弹窗..
//                auto done = CallFuncN::create([=](Ref* ref){
//                    PopUp* popup = (PopUp*)getParent();
//                    popup->closeTopPop();
//                });
//                this->runAction(Sequence::create(DelayTime::create(0.8),done, NULL));
//            }else if(m_PackageType == SpecialOffersType) {
//                UserDefault::getInstance()->setIntegerForKey("open_specialoffer",m_WeekType);
//                auto done = CallFuncN::create([=](Ref* ref){
            
            //弹窗层关闭弹窗..
            if (m_bNotPushToColse) {
                this->closePop();
            }else{
                PopUp* popup = (PopUp*)getParent();
                popup->closeTopPop();
            }
//                });
//                this->runAction(Sequence::create(DelayTime::create(0.8),done, NULL));
//            }

        }
    }
    
    
//    void SpecialOfferLayer::coinFly(cocos2d::ui::Widget* ref)
//    {
//        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
//        Widget* goldTip = (Widget*)Main::seekNodeByName(m_pPanel, "tip");
//
//
//
//
//        Widget* moneyIcon = (Widget*)cocos2d::ui::Helper::seekWidgetByName(goldTip, "moneyIcon");
//
//        auto done1 = CallFuncN::create([=](Ref* ref){
//            
//            auto done = CallFuncN::create([=](Ref* ref){
//                coinClone->removeFromParentAndCleanup(true);
//                Sequence* a = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
//                moneyIcon->runAction(a);
//            });
//        });
//        
//        auto done2 = CallFuncN::create([=](Ref* ref){
////            Widget* coinClone = coin->clone();
////            coinClone->setPosition(coin->getWorldPosition());
////            addChild(coinClone, 100);
//            auto done = CallFuncN::create([=](Ref* ref){
////                coinClone->removeFromParentAndCleanup(true);
//                Sequence* a = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
//                moneyIcon->runAction(a);
//            });
//        });
//        this->runAction(Sequence::create(Repeat::create(Sequence::create(done1, DelayTime::create(0.05f), NULL), 1), NULL));
//    }
}
