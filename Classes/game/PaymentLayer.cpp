//
//  PaymentLayer.cpp
//  jelly3.5
//
//  Created by mac on 15/10/8.
//
//

#include "PaymentLayer.h"
using namespace cocos2d;
using namespace ui;
using namespace cocostudio;
namespace popup{
    PaymentLayer::~PaymentLayer()
    {
//        CCLOG("");
        _eventDispatcher->removeEventListener(_listener);

    }

    PaymentLayer* PaymentLayer::createWithType(ProductIndex productIndex)
    {
        PaymentLayer *paymentLayer = new PaymentLayer();
        if (paymentLayer && paymentLayer->init(productIndex)) {
            paymentLayer->autorelease();
            return paymentLayer;
        }
        else
        {
            delete paymentLayer;
            paymentLayer = NULL;
            return NULL;
        }

    }
    bool PaymentLayer::init(ProductIndex productIndex)
    {
        if (!Layer::init()) {
            return false;
        }
//        this->moving = true;
        m_ProductIndex = productIndex;
        
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
        
        
        m_pPanel = CSLoader::createNode("csb/popup/goldshopcu_0.csb");

        m_pPanel->setPosition(Vec2(0, visibleSize.height));
        addChild(m_pPanel, 100);
        auto done = CallFuncN::create([=](Ref* ref)
                                      {
//                                          this->moving = false;
                                      });
        Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(0.5f, Vec2(0, -visibleSize.height))),done, NULL);
        m_pPanel->runAction(Seq);
        
        this->setDisPlayWithType(productIndex);

        
        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
        Widget *itemLayer = (Widget*)Main::seekNodeByName(goldPanel, "itemlayer");
        Widget *buganduse = (Widget*)Main::seekNodeByName(itemLayer, "buganduse");
        Widget *buyTouch = (Widget*)Main::seekNodeByName(buganduse, "touch");

        Widget *body = (Widget*)Main::seekNodeByName(goldPanel, "body");
        Widget *getAuthTouch = (Widget*)Main::seekNodeByName(body, "touch");

        buyTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(PaymentLayer::buyButtonBtnClick, this)));
        getAuthTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(PaymentLayer::getAuthButtonBtnClick, this)));
        
        Widget* close = cocos2d::ui::Helper::seekWidgetByName(goldPanel, "close");
        close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(PaymentLayer::closeBtnClick, this)));
        
        m_pPhoneNumber = (Text*)cocos2d::ui::Helper::seekWidgetByName(itemLayer, "Text_2");
        m_pAuthNumber = (Text*)cocos2d::ui::Helper::seekWidgetByName(itemLayer, "Text_2_0");

        m_pPhoneNumber->setString("");
        m_pAuthNumber->setString("");
        
        
        Widget *image_5 = (Widget*)Main::seekNodeByName(itemLayer, "Image_5");

        auto s = Size(400, 60);  //设置编辑框大小..
        //Scale9Sprite类似android上的9图工具,可对图片进行拉伸而不失真..
        auto m9pic= cocos2d::ui::Scale9Sprite::create("pic/ui/circle_black2.png");
        
        m_pNumberEditBox = cocos2d::ui::EditBox::create(s, m9pic);
        m_pNumberEditBox->setFontSize(10);		//编辑框文本大小..
        m_pNumberEditBox->setFontColor(Color3B::WHITE);  //编辑框文本颜色..
        m_pNumberEditBox->setPlaceHolder("请输入联通手机号..");  //编辑框提示语句..
        m_pNumberEditBox->setPlaceholderFontColor(Color3B(217, 217, 217)); //编辑框提示语句颜色..
        m_pNumberEditBox->setMaxLength(11);             //编辑框文本长度..
		m_pNumberEditBox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//编辑框文本框输入类型..
		m_pNumberEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC); //编辑框文本的输入模式..
        m_pNumberEditBox->setDelegate(this);            //注册编辑框协议..

        m_pNumberEditBox->setPosition(Vec2(image_5->getContentSize().width/2 - 10, image_5->getContentSize().height/2));
        m_pNumberEditBox->setOpacity(0);
        image_5->addChild(m_pNumberEditBox,100);
        
        
        Widget *image_5_0 = (Widget*)Main::seekNodeByName(itemLayer, "Image_5_0");

		m_pAuthEditBox = cocos2d::ui::EditBox::create(s, m9pic);
        m_pAuthEditBox->setFontSize(10);		//编辑框文本大小..
        m_pAuthEditBox->setFontColor(Color3B::WHITE);  //编辑框文本颜色..
        m_pAuthEditBox->setPlaceHolder("请输入短信验证码.");  //编辑框提示语句..
        m_pAuthEditBox->setPlaceholderFontColor(Color3B(217, 217, 217)); //编辑框提示语句颜色..
        m_pAuthEditBox->setMaxLength(11);             //编辑框文本长度..
		m_pAuthEditBox->setInputFlag(cocos2d::ui::EditBox::InputFlag::INITIAL_CAPS_WORD);//编辑框文本框输入类型..
		m_pAuthEditBox->setInputMode(cocos2d::ui::EditBox::InputMode::NUMERIC); //编辑框文本的输入模式..
        m_pAuthEditBox->setDelegate(this);            //注册编辑框协议..
        
        m_pAuthEditBox->setPosition(Vec2(image_5_0->getContentSize().width/2 - 10, image_5_0->getContentSize().height/2));
        m_pAuthEditBox->setOpacity(0);
        image_5_0->addChild(m_pAuthEditBox,100);
        
        std::string phonenumber = UserDefault::getInstance()->getStringForKey("phonenumber");
        if (phonenumber.length()>0) {
            m_pNumberEditBox->setText(phonenumber.c_str());

        }
        
        //设置监听..
        _listener = EventListenerCustom::create("changecolor", [=](EventCustom* e){
            Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
            Widget *body = (Widget*)Main::seekNodeByName(goldPanel, "body");
            
            Text* title = (Text*)cocos2d::ui::Helper::seekWidgetByName(body, "Text_4");
            title->setColor(Color3B(131, 121, 255));

        });
        _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);

        return true;
    }
    
    void PaymentLayer::buyButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
    {
        if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
            cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
//            CCLOG("buyButtonBtnClick");
            std::string number = m_pNumberEditBox->getText();
            std::string Auth = m_pAuthEditBox->getText();
            if (Auth.length()>0) {
                PurchaseManager::getInstance()->verificationSecurityCode(number, Auth);
                
                //增加音效..
                cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
                //弹窗层关闭弹窗..
                //            PopUp* popup = (PopUp*)getParent();
                //            popup->closeTopPop();
                //            this->moving = true;
                
                Size visibleSize = Director::getInstance()->getVisibleSize();
                
                auto done = CallFuncN::create([&](Ref* ref){
                    //                this->moving = false;
                    //                PopUp* popup = (PopUp*)getParent();
                    //                popup->popBack();
                    this->removeFromParentAndCleanup(true);
                });
                //金币窗口..
                Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
                Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), NULL);
                m_pPanel->runAction(seq1);
                //        _goldTip->runAction(seq2);
                //背景图片..
                Sprite* sprite = (Sprite*)this->getChildByTag(10);
                sprite->runAction(FadeTo::create(0.5, 0));
                
            }else{
                PurchaseManager::getInstance()->showMessage("验证码不能为空.");

            }
            

        }
    }

    void PaymentLayer::getAuthButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
    {
        if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
            cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
//            CCLOG("getAuthButtonBtnClick");
//            bool isReachable = AndroidSDKHelper::sharedHelper()->isReachable();
//            CCLOG("isReachable = %d",isReachable?1:0);
            std::string number = m_pNumberEditBox->getText();
            Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
            Widget *body = (Widget*)Main::seekNodeByName(goldPanel, "body");
            
            Text* title = (Text*)cocos2d::ui::Helper::seekWidgetByName(body, "Text_4");
            title->setColor(Color3B(131, 121, 255));
            if (number.length()>0) {
                PurchaseManager::getInstance()->getSecurityCode(number);
                PurchaseManager::getInstance()->showMessage("正在获取验证码.");
                title->setColor(Color3B(126, 126, 126));
            }else{
                PurchaseManager::getInstance()->showMessage("手机号不能为空！.");
                title->setColor(Color3B(131, 121, 255));

            }
//            this->;

        }
    }

    void PaymentLayer::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
        
        if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
        {
            //增加音效..
            cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
            //弹窗层关闭弹窗..
//            PopUp* popup = (PopUp*)getParent();
//            popup->closeTopPop();
//            this->moving = true;
            
            Size visibleSize = Director::getInstance()->getVisibleSize();
            
            auto done = CallFuncN::create([&](Ref* ref){
//                this->moving = false;
//                PopUp* popup = (PopUp*)getParent();
//                popup->popBack();
                this->removeFromParentAndCleanup(true);
            });
            //金币窗口..
            Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
            Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), NULL);
            m_pPanel->runAction(seq1);
            //        _goldTip->runAction(seq2);
            //背景图片..
            Sprite* sprite = (Sprite*)this->getChildByTag(10);
            sprite->runAction(FadeTo::create(0.5, 0));

            
        }
    }
    
//    void PaymentLayer::closePop()
//    {
//        this->moving = true;
//        
//        Size visibleSize = Director::getInstance()->getVisibleSize();
//        
//        auto done = CallFuncN::create([&](Ref* ref){
//            this->moving = false;
//            PopUp* popup = (PopUp*)getParent();
//            popup->popBack();
//        });
//        //金币窗口..
//        Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
//        Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, visibleSize.height)), 2.5f), NULL);
//        m_pPanel->runAction(seq1);
//        //        _goldTip->runAction(seq2);
//        //背景图片..
//        Sprite* sprite = (Sprite*)getChildByTag(10);
//        sprite->runAction(FadeTo::create(0.5, 0));
//        
//        //        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);
//    }
    
    void PaymentLayer::setDisPlayWithType(ProductIndex productIndex)
    {
        Widget *goldPanel = (Widget*)Main::seekNodeByName(m_pPanel, "goldPanel");
        Text* title = (Text*)cocos2d::ui::Helper::seekWidgetByName(goldPanel, "Text_1");
        std::string titleText = PurchaseManager::getInstance()->getProductName(productIndex);
        title->setString(titleText);
        
        Widget* itemLayer = (Widget*)Main::seekNodeByName(goldPanel, "itemlayer");
        Text* price = (Text*)cocos2d::ui::Helper::seekWidgetByName(itemLayer, "Text_1_0");
        std::string priceText = "￥." + Value(((int)PurchaseManager::getInstance()->getProductPrice(productIndex))).asString();
        price->setString(priceText);
        


    }
	void PaymentLayer::editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox){
        log("click");
    }
	void PaymentLayer::editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox){
        log("leave click");
    }
	void PaymentLayer::editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text){
        log("text change=%s", text.c_str());
        log("text =%s", m_pNumberEditBox->getText());

        
    }
	void PaymentLayer::editBoxReturn(cocos2d::ui::EditBox* editBox){
        log("returned");
    }
}