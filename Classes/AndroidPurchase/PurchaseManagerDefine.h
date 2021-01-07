//
//  PurchaseManagerDefine.h
//  jelly
//
//  Created by mac on 15/7/27.
//
//

#ifndef jelly_PurchaseManagerDefine_h
#define jelly_PurchaseManagerDefine_h

enum
{
    kBuyMethod91 = 2,
    kBuyMethodAndGame = 3,
    kBuyMethodCMCC  = 4,
    kBuyMethodPZPay = 24 ,
    kBuyMethodPZPayWo = 25,
    kBuyMethodEgame = 26,
    kBuyMethodUnipay = 27,
	kBuyMethodTianYi = 28,

};

/**
 * @note 可追加，不可更改次序和已有的枚举值
 */
typedef enum
{
    kProductIndexNone = -1,
    kProductIndexDirectCoin1,//30金币..
    kProductIndexDirectCoin2,//70金币..
    kProductIndexDirectCoin3,//100金币..
    kProductIndexDirectCoin4,//300金币..

    kProductIndex5OffGift,// 5折礼包..
    
    kProductIndexEndlessMode,//无尽模式..
    kProductIndexFirstCharge,//首充礼包..
    kProductIndexLimitedTimeEndlessMode,//限时解锁无尽模式..
    kProductIndexSpecialOffers_1,//特惠礼包 周一..
    kProductIndexSpecialOffers_2,
    kProductIndexSpecialOffers_3,
    kProductIndexSpecialOffers_4,
    kProductIndexSpecialOffers_5,
    kProductIndexSpecialOffers_6,
    kProductIndexSpecialOffers_7,//特惠礼包 周日..
    kProductIndexMax,
}ProductIndex;
#endif
