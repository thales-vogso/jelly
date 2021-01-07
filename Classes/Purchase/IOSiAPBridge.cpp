#include "IOSiAPBridge.h"
std::string IOSiAPBridge::PURCHASEOVER="purchaseover";
std::string IOSiAPBridge::PURCHASEFAIL="Purchasefails";
std::string IOSiAPBridge::RECOVERSUCCESS="recoversuccess";

IOSiAPBridge::IOSiAPBridge()
{
	iap = new IOSiAP();
    _transitionNum=0;
	iap->delegate = this;
    identifiers.push_back("vogso.xiaolongnv.goodsone");
	identifiers.push_back("vogso.xiaolongnv.goodtwo");
	identifiers.push_back("vogso.xiaolongnv.goodthree");
	identifiers.push_back("vogso.xiaolongnv.goodfour");
	identifiers.push_back("vogso.xiaolongnv.goodfive");
    identifiers.push_back("vogso.xiaolongnv.goodspackage");
    identifiers.push_back("vogso.xiaolongnv.noad");
    identifiers.push_back("vogso.xiaolongnv.endless");
	/*
	100
	220
	600
	2000
	16200
    200
	*/
	//identifier = identifiers.at(0);
}

IOSiAPBridge::~IOSiAPBridge()
{
	delete iap;
}

void IOSiAPBridge::requestProducts(int gold,bool ad)
{
    _gold = gold;
    _adBlock=ad;
    switch (gold) {
        case 100:
            identifier = "vogso.xiaolongnv.goodsone";
            break;
        case 220:
            identifier = "vogso.xiaolongnv.goodtwo";
            break;
        case 600:
            identifier = "vogso.xiaolongnv.goodthree";
            break;
        case 2000:
            identifier = "vogso.xiaolongnv.goodfour";
            break;
        case 16200:
            identifier = "vogso.xiaolongnv.goodfive";
            break;
        case 200:
            identifier = "vogso.xiaolongnv.goodspackage";
            break;
        case 6:
            identifier = "vogso.xiaolongnv.noad";
            break;
        case 12:
            identifier="vogso.xiaolongnv.endless";
            break;
        default:
            identifier = "vogso.xiaolongnv.goodsone";
            break;
    }
    iap->requestProducts(identifiers);
    CCLOG("requestProducts");
}

void IOSiAPBridge::onRequestProductsFinish(void)
{
	//必须在onRequestProductsFinish后才能去请求iAP产品数据。..
	IOSProduct *product = iap->iOSProductByIdentifier(identifier);
	// 然后可以发起付款请求。..
    
    if (_adBlock) {
        iap->paymentWithADProduct(product);
    }
    else
    {
         iap->paymentWithProduct(product);
    }
	//iap->paymentWithProduct(product, quantity);
    CCLOG("onRequestProductsFinish");
}

void IOSiAPBridge::onRequestProductsError(int code)
{
	//这里requestProducts出错了，不能进行后面的所有操作。..
    CCLOG("onRequestProductsError");
}

void IOSiAPBridge::onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity)
{
    _transitionNum++;
   
	if (event == IOSIAP_PAYMENT_PURCHAED) {
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PURCHASEOVER, nullptr);
		//付款成功了，可以吧金币发给玩家了。..
        if (_transitionNum==1) {
            CCLOG("onPaymentEvent success");
            if (_gold>=100) {
                data::User::getInstance()->goldPlus(_gold);
            }
        }
	}
    else if(event==IOSIAP_PAYMENT_FAILED){
        CCLOG("onPaymentEvent cancel");
        //付款失败或者取消付款。。..
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(PURCHASEFAIL,nullptr);
    }
    else if(event==IOSIAP_PAYMENT_RESTORED)
    {
        //恢复购买成功。。。..
        
        cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(RECOVERSUCCESS,nullptr);
    }
    
	//其他状态依情况处理掉。..
    CCLOG("onPaymentEvent event:%d", event);
}