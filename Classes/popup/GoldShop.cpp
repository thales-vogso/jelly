/****************************************************************************
*	@       	       
*	@desc	金币商店
*	@date	2014-11-3
*	@author	120101
*	@       	       
*	@file	popup/GoldShop.h
*	@modify	null
******************************************************************************/
#include "popup/GoldShop.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "Purchase/IOSiAPBridge.h"
#endif
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include <jni.h>
#include <android/log.h>
#endif
#include "platform/CCCommon.h"
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

namespace popup{
	const std::string GoldShop::GAMESUME = "gamesume";

	GoldShop* GoldShop::create(bool libao)
	{
		GoldShop* pRet = new GoldShop();
		pRet->_blibao = libao;
		if (pRet && pRet->init())
		{
			pRet->autorelease();
			return pRet;
		}
		else
		{
			delete pRet;
			pRet = NULL;
			return NULL;
		}
	}

	bool GoldShop::init()
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

		/**  加载弹窗  */
		Node* panel = CSLoader::createNode(PANEL_NAME.c_str());
		panel->setPosition(Vec2(0, visibleSize.height));
		addChild(panel, 100);
		_goldPanel = (Widget*)Main::seekNodeByName(panel, GOLDPANEL);
		_goldPanel->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height - 30));
		_goldTip = (Widget*)Main::seekNodeByName(panel, TIP);
		_goldTip->setPosition(Vec2(26 + 10, visibleSize.height - 26 - 10));
		TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "label");
		int gold = data::User::getInstance()->getGold();
		std::stringstream str;
		str << gold;
		moneyText->setString(str.str().c_str());
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		Widget* textlabel = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_goldPanel, "bottomText");
		textlabel->setVisible(false);
#endif    
		/**  加载商品条目  */
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
		std::vector<UMGDBRow> goodsData = data::Shop::getInstance()->getGoodsByType(data::Shop::GoodsType::ANDROIDMONEY);
#endif	
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		std::vector<UMGDBRow> goodsData = data::Shop::getInstance()->getGoodsByType(data::Shop::GoodsType::IOSMONEY);
#endif
#if (CC_TARGET_PLATFORM==CC_PLATFORM_WIN32)
		std::vector<UMGDBRow> goodsData = data::Shop::getInstance()->getGoodsByType(data::Shop::GoodsType::ANDROIDMONEY);
#endif
		Widget* bar = cocos2d::ui::Helper::seekWidgetByName(_goldPanel, BAR);

		Text* text = (Text*)bar->getChildByName("text");
		TextAtlas* textAtlas = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldPanel, "label");
		UMGDBRow row = goodsData[0];
		text->setString(row["name"].asString());
		textAtlas->setString(row["price"].asString());
		Widget* moneyBtn = (Widget*)bar->getChildByName("money");
		Text* gid = (Text*)moneyBtn->getChildByName("id");
		gid->setString(row["gid"].asString());
		moneyBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GoldShop::goodsClick, this)));
		for (int i = 1; i < goodsData.size(); i++)
		{
			Widget* barClone = bar->clone();
			barClone->setTouchEnabled(true);
			cocos2d::ui::Helper::seekWidgetByName(_goldPanel, SCROLLVIEW)->addChild(barClone);
			barClone->setPosition(bar->getPosition() + Vec2(0, -145 * i));
			Text* text = (Text*)barClone->getChildByName("text");
			TextAtlas* textAtlas = (TextAtlas*)barClone->getChildByName("money")->getChildByName("label");
			UMGDBRow row = goodsData[i];
			text->setString(row["name"].asString());
			textAtlas->setString(row["price"].asString());
			Widget* moneyBtn = (Widget*)barClone->getChildByName("money");
			Text* gid = (Text*)moneyBtn->getChildByName("id");
			gid->setString(row["gid"].asString());
			moneyBtn->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GoldShop::goodsClick, this)));
		}
		Widget* close = cocos2d::ui::Helper::seekWidgetByName(_goldPanel, CLOSE);
		close->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GoldShop::closeBtnClick, this)));

		auto done = CallFuncN::create([=](Ref* ref)
		{
			this->moving = false;
		});
		Sequence* Seq = Sequence::create(EaseBackOut::create(MoveBy::create(DELTATIME, Vec2(0, -visibleSize.height))), done, NULL);

		panel->runAction(Seq);

		//设置监听
		_goldlistener = EventListenerCustom::create(data::User::GOLD_CHANGE, [=](EventCustom* e){
			//金钱显示改变..
			int gold = data::User::getInstance()->getGold();
			TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "label");
			std::stringstream str;
			str << gold;
			moneyText->setString(str.str().c_str());
		});
		_eventDispatcher->addEventListenerWithFixedPriority(_goldlistener, 1);

		_scrollView = cocos2d::ui::Helper::seekWidgetByName(_goldPanel, SCROLLVIEW);
		_libao = cocos2d::ui::Helper::seekWidgetByName(_goldPanel, "libao");
		Widget* anniu = cocos2d::ui::Helper::seekWidgetByName(_libao, "pay");
		anniu->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(GoldShop::goodsClick, this)));
		if (_blibao)
		{
			_scrollView->setVisible(false);
			_libao->setVisible(true);
		}
		else
		{
			_scrollView->setVisible(true);
			_libao->setVisible(false);
			//长度
		}
		return true;
	}

	void GoldShop::closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
			//弹窗层关闭弹窗..
			PopUp* popup = (PopUp*)getParent();
			popup->closeTopPop();
            CCLOG("closeBtnClick");

		}
	}
	void GoldShop::goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){

		if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			Widget* money = (Widget*)ref;
			UMGDBRow goodData;
			if (!_blibao)
			{
				Text* gid = (Text*)money->getChildByName("id");
				int id = atoi(gid->getString().c_str());
				goodData = data::Shop::getInstance()->getGoodById(id);
			}


			Size visibleSize = Director::getInstance()->getVisibleSize();
			Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height*0.5);
			Vec2 origin = Director::getInstance()->getVisibleOrigin();
			//购买的金币的数量..
			int coinnum;
			if (_blibao)
			{
				coinnum = 200;
			}
			else
			{
				coinnum = goodData["num"].asInt();
			}

			//购买金币花费的钱..
			int cash;
			if (_blibao)
				cash = 6;
			else
				cash = goodData["price"].asInt();
            
            int propIndex = -1;
            switch (coinnum) {
                case 30:
                    propIndex = kProductIndexDirectCoin1;
                    break;
                case 70:
                    propIndex = kProductIndexDirectCoin2;
                    break;
                case 150:
                    propIndex = kProductIndexDirectCoin3;
                    break;
                case 200:
                    propIndex = kProductIndex5OffGift;
                    break;
                case 300:
                    propIndex = kProductIndexDirectCoin4;
                    break;
                default:
                    break;
            }
            if (_blibao) {
                propIndex = kProductIndex5OffGift;
            }

#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
//            if (!_blibao)
//                coinFly(money);
//            data::User::getInstance()->goldPlus(coinnum);
            int count = PurchaseManager::getInstance()->getProductCount(propIndex);
//            const char *productID = PurchaseManager::getInstance()->getProductID(propIndex).c_str();
//            const char *orderId91 = Value((int)time(NULL)).asString().c_str();
//            CCLog("pay-orderId91 = %d",orderId91);

            PurchaseManager::getInstance()->makePurchase(propIndex);

			//C++代码
			    //1. 获取activity静态对象
//			    JniMethodInfo minfo;
//			    bool isHave = JniHelper::getStaticMethodInfo(minfo,
//			                                                 "org/cocos2dx/cpp/AppActivity",
//			                                                 "JniTestFunction_Static",
//			                                                 "()Ljava/lang/Object;");
//			    jobject activityObj;
//			    if (isHave)
//			    {
//			        //调用静态函数getJavaActivity，获取java类对象。
//			    	CCLog("jni:存在");
//			        activityObj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
//			    }
//			    else
//			    {
//			    	CCLog("Jni:不存在");
//			    }
//			    //2. 查找displayWebView接口，获取其函数信息，并用jobj调用..
//			    isHave = JniHelper::getMethodInfo(minfo,"org/cocos2dx/cpp/AppActivity","onClick", "(I)V");
//			    if (!isHave)
//			    {
//			        CCLog("jni:onClick 函数不存在");
//			    }
//			    else
//			    {
//			    	jint jnum=(int)coinnum;
//			        //调用此函数
//			        //调用displayWebView函数，并传入参数
//			        minfo.env->CallVoidMethod(activityObj, minfo.methodID,jnum);
//			        CCLog("jni:onClick 函数存在");
//			    }
#endif
            /**
             *  注释 谢涛注释
             * jni/../../Classes/popup/GoldShop.cpp:289:45: error: use of undeclared identifier 'IOSiAPBridge'
             _eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEFAIL, purchaseoverlisenter);
             *
             */
            /*
#if(CC_TARGET_PLATFORM!=CC_PLATFORM_IOS)
			//灰色遮罩层。。。。
			IOSiAPBridge* bridge = new IOSiAPBridge();
			bridge->requestProducts(coinnum,false);
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
				coinFly(money);

			};
			_eventDispatcher->addCustomEventListener(IOSiAPBridge::PURCHASEOVER, purchaseoverlisenters);



#endif
             */
			//支付的渠道,暂时是3..
			int source = 3;
//#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//			umeng::MobClickCpp::pay(cash, source, coinnum);
//#endif


#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//			if (!_blibao)
//				coinFly(money);
//			data::User::getInstance()->goldPlus(coinnum);
            switch (coinnum) {
                case 100:
                    propIndex = kProductIndexDirectCoin1;
                    break;
                case 220:
                    propIndex = kProductIndexDirectCoin2;
                    break;
                case 600:
                    propIndex = kProductIndexDirectCoin3;
                    break;
                case 2000:
                    propIndex = kProductIndex5OffGift;
                    break;
                case 16200:
                    propIndex = kProductIndexDirectCoin4;
                    break;
                default:
                    break;
            }
            PurchaseManager::getInstance()->makePurchase(propIndex);

#endif
			//金钱显示改变..
			int gold = data::User::getInstance()->getGold();
			TextAtlas* moneyText = (TextAtlas*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "label");
			std::stringstream str;
			str << gold;
			moneyText->setString(str.str().c_str());
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			if (_blibao)
			{
				data::User::getInstance()->setLibao(false);
				//增加音效..
				cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
				//弹窗层关闭弹窗..
				PopUp* popup = (PopUp*)getParent();
				popup->closeTopPop();
			}
		}
	}
	GoldShop::~GoldShop()
	{
		_eventDispatcher->removeEventListener(_goldlistener);
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEOVER);
		_eventDispatcher->removeCustomEventListeners(IOSiAPBridge::PURCHASEFAIL);
#endif
	}
	void GoldShop::closePop()
	{
        CCLOG("closePop");
        Director::getInstance()->resume();
		this->moving = true;
		Size visibleSize = Director::getInstance()->getVisibleSize();

		auto done = CallFuncN::create([&](Ref* ref){
			this->moving = false;
			PopUp* popup = (PopUp*)getParent();
			popup->popBack();
            CCLOG("closepopBack");

		});
		//金币窗口..
		Sequence* seq1 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), done, NULL);
		Sequence* seq2 = Sequence::create(EaseIn::create(MoveBy::create(DELTATIME, Vec2(0, visibleSize.height)), 2.5f), NULL);
        if (_goldPanel) {
            CCLOG("closepopBack_goldPanel");

        }
        
        if (_goldTip) {
            CCLOG("closepopBack_goldTip");

        }
		_goldPanel->runAction(seq1);
		_goldTip->runAction(seq2);
		//背景图片..
		Sprite* sprite = (Sprite*)getChildByTag(10);
		sprite->runAction(FadeTo::create(DELTATIME, 0));
        
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(GoldShop::GAMESUME, nullptr);
	}
	void GoldShop::coinFly(cocos2d::ui::Widget* ref)
	{
		Widget* coin = (Widget*)ref->getParent()->getChildByName("coin");
		Widget* moneyIcon = (Widget*)cocos2d::ui::Helper::seekWidgetByName(_goldTip, "moneyIcon");

		auto done1 = CallFuncN::create([=](Ref* ref){
			Widget* coinClone = coin->clone();
			//coinClone->setScale(1.5);
			coinClone->setPosition(coin->getWorldPosition());
			addChild(coinClone, 100);

			auto done = CallFuncN::create([=](Ref* ref){
				coinClone->removeFromParentAndCleanup(true);
				Sequence* a = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
				moneyIcon->runAction(a);
			});
			coinClone->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-100, 100)), MoveTo::create(0.5, moneyIcon->getWorldPosition()), done, NULL));
		});

		auto done2 = CallFuncN::create([=](Ref* ref){
			Widget* coinClone = coin->clone();
			coinClone->setPosition(coin->getWorldPosition());
			addChild(coinClone, 100);
			auto done = CallFuncN::create([=](Ref* ref){
				coinClone->removeFromParentAndCleanup(true);
				Sequence* a = Sequence::create(ScaleTo::create(0.3, 1.2), ScaleTo::create(0.3, 0.8), ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1), NULL);
				moneyIcon->runAction(a);
			});
			coinClone->runAction(Sequence::create(MoveBy::create(0.5, Vec2(-100, 100)), MoveTo::create(0.5, moneyIcon->getWorldPosition()), done, NULL));
			//coinClone->runAction(Sequence::create(EaseIn::create(MoveBy::create(0.5, moneyIcon->getWorldPosition() - coinClone->getWorldPosition()), 1.5f), done, NULL));
		});
		this->runAction(Sequence::create(Repeat::create(Sequence::create(done1, DelayTime::create(0.05f), NULL), 1), NULL));
	}
}
/**
 *  注释 谢涛注释
 * jni/../../Classes/popup/GoldShop.cpp:408:8: error: use of undeclared identifier '_blibao'
   if (!_blibao)
 *
 */
/*
#if (CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
extern "C"
{
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_paySuccess(JNIEnv*  env, jobject thiz)
	{
		if (!_blibao)
			coinFly(20);
		data::User::getInstance()->goldPlus(coinnum);
	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_payError(JNIEnv*  env, jobject thiz)
	{

	}
	JNIEXPORT void JNICALL Java_org_cocos2dx_cpp_wrapper_payCancel(JNIEnv*  env, jobject thiz)
	{

	}
}

#endif
  */
