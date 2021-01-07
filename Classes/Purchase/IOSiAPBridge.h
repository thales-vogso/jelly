#ifndef  __IOS_IAP_BRIDGE__
#define  __IOS_IAP_BRIDGE__

#include "cocos2d.h"
#include "IOSiAP.h"
#include "data/User.h"

class IOSiAPBridge : public IOSiAPDelegate
{
public:
	IOSiAPBridge();
	~IOSiAPBridge();
	IOSiAP *iap;
	void requestProducts(int gold,bool ad);

	virtual void onRequestProductsFinish(void);
	virtual void onRequestProductsError(int code);
	virtual void onPaymentEvent(std::string &identifier, IOSiAPPaymentEvent event, int quantity);
    
    /*
    *   付款成功事件
    */
    static  std::string PURCHASEOVER;
    /*
    *   付款取消事件
    */
    static  std::string PURCHASEFAIL;
    /*
     *   恢复购买成功
     */
    static std::string RECOVERSUCCESS;
private:
	std::vector<std::string> identifiers;
	std::string identifier;
    int _gold;
    //是否是广告的恢复购买。。。
    bool _adBlock;
    /*
     *  交易次数
     */
    int _transitionNum;
    
};

#endif // __IOS_IAP_BRIDGE__