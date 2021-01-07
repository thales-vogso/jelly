//
//  PurchaseManager.h
//  jelly
//
//  Created by mac on 15/7/27.
//
//

#ifndef __jelly3_5__PurchaseManager__
#define __jelly3_5__PurchaseManager__

#include "cocos2d.h"
#include <stdio.h>
#if(CC_TARGET_PLATFORM==CC_PLATFORM_ANDROID)
#include "platform/android/jni/JniHelper.h"
#include <jni.h>
#endif
#include "data/User.h"
#include "data/Shop.h"
#include "game/PaymentLayer.h"

typedef struct
{
    int uid;                    // 对应数据的id，一定唯一..
    std::string productId;      // 对应计费点id，不一定唯一..
    int buyMethodCode;
    std::string productName;
    std::string productNameEN;
    int productCount;
    float productPrice;
    float originPrice;
    float extraData;
    std::string umgameKey;

}
ProductInfo;



class PurchaseManager
{
private:
    static PurchaseManager *s_pSharedManager;

    static const std::string kProductUniqueID;  // 对应数据记录id，绝对唯一..
    static const std::string kProductID;        // 对应计费点id，未必唯一..
    static const std::string kProductBuyMethod;
    static const std::string kProductName;
    static const std::string kProductNameEN;
    static const std::string kProductCount;
    static const std::string kProductPrice;
    static const std::string kProductOriginPrice;
    static const std::string kProductExtraData;
    static const std::string kProductUmGameKey;
    static const std::string kProductAliasKey;
    

private:
    int m_nProductIndex;
    std::string m_sPzPayWoOrderId;
    cocos2d::ValueVector m_OrderIdVector;
    cocos2d::ValueMap m_pOrderMap;
public:
    static const std::string kProductOrderId;

    PurchaseManager();
    static PurchaseManager* getInstance();
    void initProductData();
    ~PurchaseManager();
    cocos2d::ValueMap m_pProductInfo;
    cocos2d::ValueMap m_pBillingIndexInfo;
    std::string getProductID(int productIndex);
    const char *getProductUniqueID(int productIndex);
    int getProductBuyMethod(int productIndex);
    std::string getProductName(int productIndex);
    std::string getProductUmGameKey(int productIndex);

    int getProductCount(int productIndex);
    float getProductPrice(int productIndex);
    int getProductExtraData(int productIndex);
    int getProductOriginPrice(int productIndex);
    void makePurchase(int productIndex);
    void makePzPayWoPurchase(int productIndex);

    void purchaseFinished(int payCode, const char *tradeID, const char *orderType);
    void purchaseFailed();
    void didReceiveProduct(int payCode, const char *tradeID, const char *orderType);
    void addSuccessPayOrderIdString(const char *formattedOrderIdString);
    int getProductIndex(const char *productID);
    void queryOrderAndReceiveProduct();
    void removeSuccessPayOrderId(std::string orderId);
    void removeAllPayOrderId();

    void showMessage(std::string message);
    void addSuccessPayOrderIdStringForAndGame(const char *formattedOrderIdString);
    void validateResult(const char *pPayCode, const char *pOrderID, const char *pTradeID, int options);
    void getSecurityCode(std::string mobile);
    void verificationSecurityCode(std::string mobile,std::string codesms);

};

#endif /* defined(__jelly__PurchaseManager__) */
