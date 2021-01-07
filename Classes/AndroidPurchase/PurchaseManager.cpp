//
//  PurchaseManager.cpp
//  jelly
//
//  Created by mac on 15/7/27.
//
//

#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
#include "popup/EndlessUnlock.h"
#include "json/document.h"//rapidjson
#include "HttpManager/HttpManager.h"
#include "json/document.h"
#include "MD5/CMD5Checksum.h"
#include "AndroidPurchase/AndroidSDKHelper.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include <jni.h>
#include <android/log.h>
#endif
using namespace popup;
using namespace ui;

using namespace cocos2d;

const std::string PurchaseManager::kProductUniqueID = "id";
const std::string PurchaseManager::kProductID = "unid";
const std::string PurchaseManager::kProductBuyMethod = "buy_way";
const std::string PurchaseManager::kProductName = "name";
const std::string PurchaseManager::kProductNameEN = "name_en";
const std::string PurchaseManager::kProductCount = "num";
const std::string PurchaseManager::kProductPrice = "price";
const std::string PurchaseManager::kProductOriginPrice = "value";
const std::string PurchaseManager::kProductExtraData = "extra_data";
const std::string PurchaseManager::kProductOrderId = "order_id";
const std::string PurchaseManager::kProductUmGameKey = "umgameKey";
const std::string PurchaseManager::kProductAliasKey = "AliasKey";



static bool m_isBuying = false;

PurchaseManager *PurchaseManager::s_pSharedManager = NULL;

PurchaseManager::PurchaseManager()
:m_nProductIndex(0)
{
    this->initProductData();
    
}

PurchaseManager::~PurchaseManager()
{
}

PurchaseManager* PurchaseManager::getInstance()
{
    if(NULL == s_pSharedManager)
    {
        s_pSharedManager = new PurchaseManager();
    }
    return s_pSharedManager;
}

void PurchaseManager::initProductData()
{
    // 默认数据...
    const int array_count = kProductIndexMax - kProductIndexNone - 1;
#if TARGET_CHANNEL == TTARGET_CHANNE_PZPAY
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id           购买方式          中文名称         英文名称                数量        价格        原价  额外数据...
        {	1	,"1001",    kBuyMethodPZPay,   "30枚金币",    	"30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"1002",    kBuyMethodPZPay,   "70枚金币",  	    "70 coins" ,                70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"1003",    kBuyMethodPZPay,   "150枚金币",       "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"1004",    kBuyMethodPZPay,   "300枚金币",        "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"1005",    kBuyMethodPZPay,   "5折大礼包",  	"half price spree",             200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"1006",    kBuyMethodPZPay,   "解锁无尽模式",  	"endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"1007",    kBuyMethodPZPay,   "首充礼包",           "",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"1008",    kBuyMethodPZPay,   "限时解锁无尽模式",     "",                    1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"1009",    kBuyMethodPZPay,   "周一特惠礼包",  	""          ,			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"1010",    kBuyMethodPZPay,   "周二特惠礼包",  	""          ,			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"1011",    kBuyMethodPZPay,   "周三特惠礼包",  	""          ,			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"1012",    kBuyMethodPZPay,   "周四特惠礼包",  	""          ,			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"1013",    kBuyMethodPZPay,   "周五特惠礼包",  	""          ,			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"1014",    kBuyMethodPZPay,   "周六特惠礼包",  	""          ,			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"1015",    kBuyMethodPZPay,   "周日特惠礼包",  	""          ,			400	,		15.0,       0,      0,      "SpecialOffers_7"        },


    };
#elif TARGET_CHANNEL == TARGET_CHANNE_AND_GAME//移动...

    ProductInfo productInfo[array_count] =
    {
        //id   计费点id            购买方式          中文名称                  英文名称                  数量        价格        原价  额外数据...
        {	1	,"001",    kBuyMethodAndGame,   "30枚金币",              "30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"002",    kBuyMethodAndGame,   "70枚金币",              "70 coins" ,               70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"003",    kBuyMethodAndGame,   "150枚金币",             "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"004",    kBuyMethodAndGame,   "300枚金币",             "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"005",    kBuyMethodAndGame,   "5折大礼包",       "half price spree",            200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"006",    kBuyMethodAndGame,   "解锁无尽模式",         "endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"007",    kBuyMethodAndGame,   "首充礼包",           "首充礼包",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"008",    kBuyMethodAndGame,   "限时解锁无尽模式",     "限时解锁无尽模式",               1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"009",    kBuyMethodAndGame,   "周一特惠礼包",           "周一特惠礼包",			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"010",    kBuyMethodAndGame,   "周二特惠礼包",           "周二特惠礼包",			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"011",    kBuyMethodAndGame,   "周三特惠礼包",           "周三特惠礼包",			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"012",    kBuyMethodAndGame,   "周四特惠礼包",           "周四特惠礼包",			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"013",    kBuyMethodAndGame,   "周五特惠礼包",           "周五特惠礼包",			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"014",    kBuyMethodAndGame,   "周六特惠礼包",           "周六特惠礼包",			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"015",    kBuyMethodAndGame,   "周日特惠礼包",           "周日特惠礼包" ,            400,		15.0,       0,      0,      "SpecialOffers_7"        },
        
        
    };
#elif TARGET_CHANNEL == TARGET_CHANNE_CMCC
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id            购买方式          中文名称                  英文名称                  数量        价格        原价  额外数据...
        {	1	,"30000919369801",    kBuyMethodCMCC,   "30枚金币",              "30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"30000919369802",    kBuyMethodCMCC,   "70枚金币",              "70 coins" ,               70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"30000919369803",    kBuyMethodCMCC,   "150枚金币",             "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"30000919369804",    kBuyMethodCMCC,   "300枚金币",             "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"30000919369805",    kBuyMethodCMCC,   "5折大礼包",       "half price spree",            200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"30000919369806",    kBuyMethodCMCC,   "解锁无尽模式",         "endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"007",    kBuyMethodCMCC,   "首充礼包",           "首充礼包",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"008",    kBuyMethodCMCC,   "限时解锁无尽模式",     "限时解锁无尽模式",               1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"009",    kBuyMethodCMCC,   "特惠礼包（周一）",  	"特惠礼包（周一）",			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"010",    kBuyMethodCMCC,   "特惠礼包（周二）",  	"特惠礼包（周二）",			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"011",    kBuyMethodCMCC,   "特惠礼包（周三）",  	"特惠礼包（周三）",			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"012",    kBuyMethodCMCC,   "特惠礼包（周四）",  	"特惠礼包（周四）",			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"013",    kBuyMethodCMCC,   "特惠礼包（周五）",  	"特惠礼包（周五）",			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"014",    kBuyMethodCMCC,   "特惠礼包（周六）",  	"特惠礼包（周六）",			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"015",    kBuyMethodCMCC,   "特惠礼包（周日）",  	"特惠礼包（周日）" ,            400,		15.0,       0,      0,      "SpecialOffers_7"        },
        
        
    };
#elif TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id           购买方式          中文名称         英文名称                数量        价格        原价  额外数据...
        {	1	,"1001",    kBuyMethodPZPayWo,   "30枚金币",    	"30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"1002",    kBuyMethodPZPayWo,   "70枚金币",  	    "70 coins" ,                70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"1003",    kBuyMethodPZPayWo,   "150枚金币",       "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"1004",    kBuyMethodPZPayWo,   "300枚金币",        "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"1005",    kBuyMethodPZPayWo,   "5折大礼包",  	"half price spree",             200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"1006",    kBuyMethodPZPayWo,   "解锁无尽模式",  	"endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"1007",    kBuyMethodPZPayWo,   "首充礼包",           "",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"1008",    kBuyMethodPZPayWo,   "限时解锁无尽模式",     "",                    1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"1009",    kBuyMethodPZPayWo,   "周一特惠礼包",  	""          ,			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"1010",    kBuyMethodPZPayWo,   "周二特惠礼包",  	""          ,			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"1011",    kBuyMethodPZPayWo,   "周三特惠礼包",  	""          ,			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"1012",    kBuyMethodPZPayWo,   "周四特惠礼包",  	""          ,			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"1013",    kBuyMethodPZPayWo,   "周五特惠礼包",  	""          ,			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"1014",    kBuyMethodPZPayWo,   "周六特惠礼包",  	""          ,			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"1015",    kBuyMethodPZPayWo,   "周日特惠礼包",  	""          ,			400	,		15.0,       0,      0,      "SpecialOffers_7"        },
        
    };
#elif TARGET_CHANNEL == TARGET_CHANNE_EGAME//电信...
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id           购买方式          中文名称         英文名称                数量        价格        原价  额外数据
        {	1	,"TOOL1",    kBuyMethodEgame,   "30枚金币",    	"30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"TOOL2",    kBuyMethodEgame,   "70枚金币",  	    "70 coins" ,                70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"TOOL3",    kBuyMethodEgame,   "150枚金币",       "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"TOOL4",    kBuyMethodEgame,   "300枚金币",        "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"TOOL5",    kBuyMethodEgame,   "5折大礼包",  	"half price spree",             200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"TOOL6",    kBuyMethodEgame,   "解锁无尽模式",  	"endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"TOOL7",    kBuyMethodEgame,   "首充礼包",           "",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"TOOL8",    kBuyMethodEgame,   "限时解锁无尽模式",     "",                    1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"TOOL9",    kBuyMethodEgame,   "周一特惠礼包",  	""          ,			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"TOOL10",    kBuyMethodEgame,   "周二特惠礼包",  	""          ,			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"TOOL11",    kBuyMethodEgame,   "周三特惠礼包",  	""          ,			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"TOOL12",    kBuyMethodEgame,   "周四特惠礼包",  	""          ,			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"TOOL13",    kBuyMethodEgame,   "周五特惠礼包",  	""          ,			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"TOOL14",    kBuyMethodEgame,   "周六特惠礼包",  	""          ,			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"TOOL15",    kBuyMethodEgame,   "周日特惠礼包",  	""          ,			400	,		15.0,       0,      0,      "SpecialOffers_7"        },
        
    };
#elif TARGET_CHANNEL == TARGET_CHANNE_UNIPAY//联通...
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id            购买方式          中文名称                  英文名称                  数量        价格        原价  额外数据...
        {	1	,"001",    kBuyMethodAndGame,   "30枚金币",              "30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"002",    kBuyMethodAndGame,   "70枚金币",              "70 coins" ,               70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"003",    kBuyMethodAndGame,   "150枚金币",             "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"004",    kBuyMethodAndGame,   "300枚金币",             "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"005",    kBuyMethodAndGame,   "5折大礼包",       "half price spree",            200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"006",    kBuyMethodAndGame,   "解锁无尽模式",         "endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"007",    kBuyMethodAndGame,   "首充礼包",           "首充礼包",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"008",    kBuyMethodAndGame,   "限时解锁无尽模式",     "限时解锁无尽模式",               1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"009",    kBuyMethodAndGame,   "周一特惠礼包",           "周一特惠礼包",			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"010",    kBuyMethodAndGame,   "周二特惠礼包",           "周二特惠礼包",			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"011",    kBuyMethodAndGame,   "周三特惠礼包",           "周三特惠礼包",			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"012",    kBuyMethodAndGame,   "周四特惠礼包",           "周四特惠礼包",			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"013",    kBuyMethodAndGame,   "周五特惠礼包",           "周五特惠礼包",			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"014",    kBuyMethodAndGame,   "周六特惠礼包",           "周六特惠礼包",			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"015",    kBuyMethodAndGame,   "周日特惠礼包",           "周日特惠礼包" ,            400,		15.0,       0,      0,      "SpecialOffers_7"        },
    };
#elif TARGET_CHANNEL == TARGET_CHANNE_SWSDK//三网SDK
    ProductInfo productInfo[array_count] =
    {
        //id   计费点id            购买方式..          中文名称. .                 英文名称..                  数量..        价格..        原价..  额外数据....
        {	1	,"001",    kBuyMethodAndGame,   "30枚金币..",              "30 coins" ,				30	,		2.0	,       0,      0,     "coin30"                  },
        {	2	,"002",    kBuyMethodAndGame,   "70枚金币..",              "70 coins" ,               70	,		4.0	,       0,      0,      "coin70"                 },
        {	3	,"003",    kBuyMethodAndGame,   "150枚金币..",             "150 coins",				150	,		8.0	,       0,      0,      "coin100"                },
        {	4	,"004",    kBuyMethodAndGame,   "300枚金币..",             "300 coins",				300	,		15.0,       0,      0,      "coin300"                },
        {	5	,"005",    kBuyMethodAndGame,   "5折大礼包..",       "half price spree",            200	,		6.0	,       0,      0,      "5offgift"               },
        {	6	,"006",    kBuyMethodAndGame,   "解锁无尽模式..",         "endless mode",             1	,		12.0,       0,      0,      "endlessmode"            },
        
        {	7	,"007",    kBuyMethodAndGame,   "首充礼包..",           "首充礼包..",                     30	,		1.0,        0,      0,      "firstcharge"            },
        {	8	,"008",    kBuyMethodAndGame,   "限时解锁无尽模式..",     "限时解锁无尽模式..",               1	,		6.0,        0,      0,      "LimitedTimeEndlessMode" },
        {	9	,"009",    kBuyMethodAndGame,   "周一特惠礼包..",           "周一特惠礼包..",			20	,		1.0,        0,      0,      "SpecialOffers_1"        },
        {	10	,"010",    kBuyMethodAndGame,   "周二特惠礼包..",           "周二特惠礼包..",			40	,		2.0,        0,      0,      "SpecialOffers_2"        },
        {	11	,"011",    kBuyMethodAndGame,   "周三特惠礼包..",           "周三特惠礼包..",			60	,		3.0,        0,      0,      "SpecialOffers_3"        },
        {	12	,"012",    kBuyMethodAndGame,   "周四特惠礼包..",           "周四特惠礼包..",			80	,		4.0,        0,      0,      "SpecialOffers_4"        },
        {	13	,"013",    kBuyMethodAndGame,   "周五特惠礼包..",           "周五特惠礼包..",			100	,		5.0,        0,      0,      "SpecialOffers_5"        },
        {	14	,"014",    kBuyMethodAndGame,   "周六特惠礼包..",           "周六特惠礼包..",			240	,		10.0,       0,      0,      "SpecialOffers_6"        },
        {	15	,"015",    kBuyMethodAndGame,   "周日特惠礼包..",           "周日特惠礼包.." ,            400,		15.0,       0,      0,      "SpecialOffers_7"        },
    };
	std::string productAlias[array_count] =
	{
		"TOOL1",
		"TOOL2",
		"TOOL3",
		"TOOL4",
		"TOOL5",
		"TOOL6",
		"TOOL7",
		"TOOL8",
		"TOOL9",
		"TOOL10",
		"TOOL11",
		"TOOL12",
		"TOOL13",
		"TOOL14",
		"TOOL15",
	};
#elif TARGET_CHANNEL == TARGET_CHANNE_TIANYI//电信...
ProductInfo productInfo[array_count] =
{
	//id   计费点id           购买方式          中文名称         英文名称                数量        价格        原价  额外数据..
	{ 1, "21A5D51D06592714E0530100007F5DC0", kBuyMethodTianYi, "30枚金币", "30 coins", 30, 2.0, 0, 0, "coin30" },
	{ 2, "21A5D51D06592714E0530100007F5DC0", kBuyMethodTianYi, "70枚金币", "70 coins", 70, 4.0, 0, 0, "coin70" },
	{ 3, "21A5D51D065A2714E0530100007F5DC0", kBuyMethodTianYi, "150枚金币", "150 coins", 150, 8.0, 0, 0, "coin100" },
	{ 4, "21A6535227AB184FE0530100007FB6D2", kBuyMethodTianYi, "300枚金币", "300 coins", 300, 15.0, 0, 0, "coin300" },
	{ 5, "21A65BC2761B298FE0530100007F722F", kBuyMethodTianYi, "5折大礼包", "half price spree", 200, 6.0, 0, 0, "5offgift" },
	{ 6, "21A65F73E0F83092E0530100007F802F", kBuyMethodTianYi, "解锁无尽模式", "endless mode", 1, 12.0, 0, 0, "endlessmode" },
	{ 7, "21A663A404663816E0530100007F8338", kBuyMethodTianYi, "首充礼包", "", 30, 1.0, 0, 0, "firstcharge" },
	{ 8, "21A6680B42C44092E0530100007F91E3", kBuyMethodTianYi, "限时解锁无尽模式", "", 1, 6.0, 0, 0, "LimitedTimeEndlessMode" },
	{ 9, "21A66C07848B48D5E0530100007FEE17", kBuyMethodTianYi, "特惠礼包（周一）", "", 20, 1.0, 0, 0, "SpecialOffers_1" },
	{ 10, "21A66F2D9B3E4DCEE0530100007F540F", kBuyMethodTianYi, "特惠礼包（周二）", "", 40, 2.0, 0, 0, "SpecialOffers_2" },
	{ 11, "21A671A97B8D52B0E0530100007F13C0", kBuyMethodTianYi, "特惠礼包（周三）", "", 60, 3.0, 0, 0, "SpecialOffers_3" },
	{ 12, "21A673CACC1C55E7E0530100007F110C", kBuyMethodTianYi, "特惠礼包（周四）", "", 80, 4.0, 0, 0, "SpecialOffers_4" },
	{ 13, "21A676330B475AE0E0530100007F7335", kBuyMethodTianYi, "特惠礼包（周五）", "", 100, 5.0, 0, 0, "SpecialOffers_5" },
	{ 14, "21A67BEBF06A66A1E0530100007F34AD", kBuyMethodTianYi, "特惠礼包（周六）", "", 240, 10.0, 0, 0, "SpecialOffers_6" },
	{ 15, "21A67BEBF06B66A1E0530100007F34AD", kBuyMethodTianYi, "特惠礼包（周日）", "", 400, 15.0, 0, 0, "SpecialOffers_7" },

};

#else
#error 没有渠道
#endif
    for (int i=0; i<array_count; ++i)
    {
        ValueMap product;
        int index = i + kProductIndexNone + 1;
        std::string key = Value(index).asString();
        
        ProductInfo pi = productInfo[i];
        product[kProductUniqueID] = pi.uid;
        product[kProductID] = pi.productId;
        product[kProductBuyMethod] = pi.buyMethodCode;
        product[kProductName] = pi.productName;
        product[kProductNameEN] = pi.productNameEN;
        product[kProductUmGameKey] = pi.umgameKey;
        product[kProductCount] = pi.productCount;
        product[kProductPrice] = pi.productPrice;
        product[kProductOriginPrice] = pi.originPrice;
        product[kProductExtraData] = pi.extraData;
#if TARGET_CHANNEL == TARGET_CHANNE_SWSDK//三网SDK
		product[kProductAliasKey] = productAlias[i];
#endif
        

        
        m_pProductInfo[key] = product;
        
        m_pBillingIndexInfo[pi.productId.c_str()] = key;

        
    }

//    for (int i=0; i<array_count; ++i)
//    {
//        int index = i + kProductIndexNone + 1;
//
//        std::string key = Value(index).asString();
//        ValueMap product = m_pProductInfo[key].asValueMap();
//        log("uid = %d,productId = %s,buyMethodCode = %d,productName = %s,productNameEN = %s,productCount = %d,productPrice = %f,originPrice = %f,extraData = %f",product[kProductUniqueID].asInt(),product[kProductID].asString().c_str(),product[kProductBuyMethod].asInt(),product[kProductName].asString().c_str(),product[kProductNameEN].asString().c_str(),product[kProductCount].asInt(),product[kProductPrice].asFloat(),product[kProductOriginPrice].asFloat(),product[kProductExtraData].asFloat());
//    }
    
}

#pragma mark - product info

std::string PurchaseManager::getProductID(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();


#if TARGET_CHANNEL == TARGET_CHANNE_SWSDK//三网SDK
    std::string productID = product[kProductID].asString();

    int code = AndroidSDKHelper::sharedHelper()->getSPCode();
    if (code == 26) {
        productID = product[kProductAliasKey].asString();
    }else{
        productID = product[kProductID].asString();
    }
    CCLOG("PurchaseManagercode = %d,productID = %s",code,productID.c_str());

#else
    std::string productID = product[kProductID].asString();
#endif
    return productID;
}

const char *PurchaseManager::getProductUniqueID(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    const char *productUniqueID = product[kProductUniqueID].asString().c_str();
    return productUniqueID;
}

int PurchaseManager::getProductBuyMethod(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    int buyMethod = product[kProductBuyMethod].asInt();
    return buyMethod;
}

std::string PurchaseManager::getProductName(int productIndex)
{
    std::string name_key = kProductName;

//    bool isChinese = (LanguageType::CHINESE == Application::getInstance()->getCurrentLanguage());
//    if (!isChinese) {
//        name_key = isChinese ? kProductName : kProductNameEN;
//    }
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    std::string productName =  product[name_key].asString();
    log("getProductName = %s",productName.c_str());
    return productName;
}

std::string PurchaseManager::getProductUmGameKey(int productIndex)
{
    std::string name_key = kProductUmGameKey;
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    std::string productUmGameKey =  product[name_key].asString();
    log("productUmGameKey = %s",productUmGameKey.c_str());
    return productUmGameKey;
}

int PurchaseManager::getProductCount(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    int productCount = product[kProductCount].asInt();
    return productCount;
}

float PurchaseManager::getProductPrice(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    float price = product[kProductPrice].asFloat();
    log("getProductPrice = %f",price);

    return price;
}

int PurchaseManager::getProductExtraData(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    int extraData = product[kProductExtraData].asInt();
    return extraData;
}

int PurchaseManager::getProductOriginPrice(int productIndex)
{
    std::string key = Value(productIndex).asString();
    ValueMap product = m_pProductInfo[key].asValueMap();
    float originPrice = product[kProductOriginPrice].asFloat();
    return originPrice;
}

int PurchaseManager::getProductIndex(const char *productID)
{
    log("product_id:%s", productID);
    int productIndex = Value(m_pBillingIndexInfo[productID]).asInt();
    log("product_index:%d", productIndex);
    return productIndex;
}

void PurchaseManager::makePurchase(int productIndex)
{
#if TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    this->makePzPayWoPurchase(productIndex);
#else
    

//    , int count, const char *description, int option, const char *uuID
    if (m_isBuying) {
        this->showMessage("正在购买......");
        return;
    }
    if (productIndex <= kProductIndexNone || productIndex >= kProductIndexMax) {
        //        购买失败...
        return;
    }
    m_isBuying = true;

    CCLOG("makePurchase");
    auto done = CallFuncN::create([=](Ref* ref){
        m_isBuying = false;
//        this->purchaseFailed();
    });
    Scene *scene = Director::getInstance()->getRunningScene();
    scene->runAction(Sequence::create(DelayTime::create(20),done, NULL));
    m_nProductIndex = productIndex;
#if TARGET_CHANNEL == TTARGET_CHANNE_PZPAY
    int option = kBuyMethodPZPay;

#elif TARGET_CHANNEL == TARGET_CHANNE_AND_GAME
    int option = kBuyMethodAndGame;

#elif TARGET_CHANNEL == TARGET_CHANNE_CMCC
    int option = kBuyMethodCMCC;
#elif TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    int option = kBuyMethodPZPayWo;
#elif TARGET_CHANNEL == TARGET_CHANNE_EGAME
    int option = kBuyMethodEgame;
#elif TARGET_CHANNEL == TARGET_CHANNE_UNIPAY
    int option = kBuyMethodUnipay;
#elif TARGET_CHANNEL == TARGET_CHANNE_SWSDK//三网SDK
    int option = kBuyMethodAndGame;
#elif TARGET_CHANNEL == TARGET_CHANNE_TIANYI//天翼SDK
	int option = kBuyMethodTianYi;
    option = AndroidSDKHelper::sharedHelper()->getSPCode();
#else
#error 没有渠道
#endif
    std::string uuID = Value((int)time(NULL)).asString();
    
#ifdef DEBUG_TEST
//    PurchaseManager::getInstance()->addSuccessPayOrderIdString(uuID.c_str());
    m_isBuying = false;

    this->didReceiveProduct(productIndex, "0", Value(kBuyMethod91).asString().c_str());

    return;
#endif

    
    
    int count = PurchaseManager::getInstance()->getProductCount(m_nProductIndex);
    std::string productNameStr = this->getProductName(productIndex);
    const char *productName = productNameStr.c_str();
    const char *productDescription = NULL;
    float unitPrice = PurchaseManager::getInstance()->getProductPrice(productIndex);

    const char *productPrice = CCString::createWithFormat("%d", (int)unitPrice)->getCString();
    const char *productID = PurchaseManager::getInstance()->getProductID(productIndex).c_str();
    log("productIndex = %d,count = %d,description = %s,option = %d,uuID = %s,name = %s",productIndex,count,productDescription,option,uuID.c_str(),productNameStr.c_str());
    log("productIndex productID = %s",productID);
    //保存订单 用来订单查询...
    UserDefault::getInstance()->setStringForKey(uuID.c_str(), Value(productID).asString());
    UserDefault::getInstance()->flush();

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

    JniMethodInfo info;
    bool isExisted = false;
    isExisted = JniHelper::getStaticMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "myInstance", "()Ljava/lang/Object;");
    jobject instance;
    
    if (isExisted) {
        instance = info.env->CallStaticObjectMethod(info.classID, info.methodID);
    }
    
    isExisted = JniHelper::getMethodInfo(info, "org/cocos2dx/cpp/AppActivity", "buyPZPayProduct", "(Ljava/lang/String;ILjava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)V");
    
//    if (isExisted) {
//        log("buyProduct-jni:存在");
//    }else{
//        log("buyProduct-jni:不存在");
//    }
//    log("productIndex1 = %d,count = %d,description = %s,option = %d,uuID = %s",productIndex,count,description,option,uuID);
//
//    return;

    if (isExisted && instance) {
        // 发起内购时暂停游戏 防止闪屏...
        Director::getInstance()->pause();

        jstring productStr = info.env->NewStringUTF(productID);
        jstring uuIDStr = info.env->NewStringUTF(uuID.c_str());
        jstring jProductPrice = info.env->NewStringUTF(productPrice);
        jstring jProductName = info.env->NewStringUTF(productName);
        jstring jProductDescription = info.env->NewStringUTF(productName);
        jstring jUserID = info.env->NewStringUTF("0");
        info.env->CallVoidMethod(instance,
                                 info.methodID,
                                 productStr,
                                 count,
                                 uuIDStr,
                                 jProductPrice,
                                 jProductName,
                                 jProductDescription,
                                 option,
                                 jUserID);

    }

    #endif
    #endif
}

void PurchaseManager::makePzPayWoPurchase(int productIndex)
{
    
    bool isReachable = AndroidSDKHelper::sharedHelper()->isReachable();
    if (!isReachable) {
        this->showMessage("网络未连接，请联网购买商品...");

        return;
    }
    if (m_isBuying) {
        this->showMessage("正在购买......");
        return;
    }
    if (productIndex <= kProductIndexNone || productIndex >= kProductIndexMax) {
        //        购买失败...
        return;
    }
    m_isBuying = true;
    
    CCLOG("makePurchase");
    auto done = CallFuncN::create([=](Ref* ref){
        m_isBuying = false;
        //        this->purchaseFailed();
    });
    Scene *scene = Director::getInstance()->getRunningScene();
    scene->runAction(Sequence::create(DelayTime::create(20),done, NULL));
    auto layer = scene->getChildByTag(1000);
    if (layer) {
        return;
    }
    m_nProductIndex = productIndex;
#if TARGET_CHANNEL == TTARGET_CHANNE_PZPAY
    int option = kBuyMethodPZPay;
    
#elif TARGET_CHANNEL == TARGET_CHANNE_AND_GAME
    int option = kBuyMethodAndGame;
    
#elif TARGET_CHANNEL == TARGET_CHANNE_CMCC
    int option = kBuyMethodCMCC;
#elif TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    int option = kBuyMethodPZPayWo;
#elif TARGET_CHANNEL == TARGET_CHANNE_EGAME
    int option = kBuyMethodEgame;
#elif TARGET_CHANNEL == TARGET_CHANNE_UNIPAY
    int option = kBuyMethodUnipay;
#elif TARGET_CHANNEL == TARGET_CHANNE_SWSDK
    int option = kBuyMethodUnipay;
#elif TARGET_CHANNEL == TARGET_CHANNE_TIANYI
	int option = kBuyMethodTianYi;
#else
#error 没有渠道
#endif
//     = Value((int)time(NULL)).asString();
    
#ifdef DEBUG_TEST
    //    PurchaseManager::getInstance()->addSuccessPayOrderIdString(uuID.c_str());
    m_isBuying = false;
    
    this->didReceiveProduct(productIndex, "0", Value(kBuyMethod91).asString().c_str());
    
    return;
#endif
    this->showMessage("正在获取数据，请稍等");

    HttpManager::getInstance()->getProductOrder([=](cocos2d::String *response){
        std::string responseStr = response->getCString();
        CCLOG("responseStr = %s",responseStr.c_str());
        rapidjson::Document m_doc;
        m_doc.Parse<0>(responseStr.c_str());
        if (m_doc.HasParseError()) {
            CCLOG("GetParaseError: %s\n",m_doc.GetParseError());
        }
        rapidjson::Value &SpNumber = m_doc["SpNumber"];
        CCLOG("pzpay_SpNumber = %s \n",SpNumber.GetString());
        //        value.IsArray()
        rapidjson::Value &SMS = m_doc["SMS"];
        CCLOG("pzpay_SMS = %s \n",SMS.GetString());
        
        rapidjson::Value &OrderId = m_doc["OrderId"];
        CCLOG("pzpay_OrderId = %s \n",OrderId.GetString());
//        std::string strFileMD5 = CMD5Checksum::GetMD5OfString(OrderId.GetString());
//        CCLOG("pzpay_strFileMD5 = %s",strFileMD5.c_str());
//        CCLOG("");
        std::string phoneNumber = AndroidSDKHelper::sharedHelper()->getPhoneNumber();
        CCLOG("pzpay_phoneNumber = %s",phoneNumber.c_str());
        std::string OrderID = OrderId.GetString();
        m_sPzPayWoOrderId = OrderId.GetString();
        
        PaymentLayer * payLayer = PaymentLayer::createWithType((ProductIndex)m_nProductIndex);
        scene->addChild(payLayer,10,1000);
        
        
        int count = PurchaseManager::getInstance()->getProductCount(m_nProductIndex);
        std::string productNameStr = this->getProductName(productIndex);
        const char *productName = productNameStr.c_str();
        const char *productDescription = NULL;
        float unitPrice = PurchaseManager::getInstance()->getProductPrice(productIndex);
        
        const char *productPrice = CCString::createWithFormat("%d", (int)unitPrice)->getCString();
        const char *productID = PurchaseManager::getInstance()->getProductID(productIndex).c_str();
        log("productIndex = %d,count = %d,description = %s,option = %d,uuID = %s,name = %s",productIndex,count,productDescription,option,OrderID.c_str(),productNameStr.c_str());
        log("productIndex productID = %s",OrderID.c_str());
        //保存订单 用来订单查询...
        UserDefault::getInstance()->setStringForKey(OrderID.c_str(), Value(productID).asString());
        UserDefault::getInstance()->flush();
        AndroidSDKHelper::sharedHelper()->sendPzPayWoSMS(SpNumber.GetString(), SMS.GetString());
//        this->addSuccessPayOrderIdString(OrderID.c_str());
    });
}

void PurchaseManager::getSecurityCode(std::string mobile)
{
    float price = this->getProductPrice(m_nProductIndex);
    std::string priceStr = String::createWithFormat("%.1f",price)->getCString();
    std::string Subject = this->getProductName(m_nProductIndex);
    HttpManager::getInstance()->getSecurityCode(m_sPzPayWoOrderId, mobile, priceStr, Subject, [=](cocos2d::String *response){
        std::string responseStr = response->getCString();
        CCLOG("responseStr = %s",responseStr.c_str());
        rapidjson::Document m_doc;
        m_doc.Parse<0>(responseStr.c_str());
        if (m_doc.HasParseError()) {
        }
        rapidjson::Value &resultCode = m_doc["resultCode"];
        std::string code = resultCode.GetString();
        if (code == "0") {
            rapidjson::Value &resultDescription = m_doc["resultDescription"];
            UserDefault::getInstance()->setStringForKey("phonenumber", mobile);
        }
        else{
//            rapidjson::Value &resultDescription = m_doc["resultDescription"];
//
//            rapidjson::Value &errorInfo = m_doc["errorInfo"];
            std::string message = "获取验证码失败！";
            this->showMessage(message);
            Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("changecolor", nullptr);

//            this
        }


    });
}

void PurchaseManager::verificationSecurityCode(std::string mobile,std::string codesms)
{
    float price = this->getProductPrice(m_nProductIndex);
    std::string priceStr = String::createWithFormat("%.1f",price)->getCString();
    HttpManager::getInstance()->verificationSecurityCode(m_sPzPayWoOrderId, mobile, priceStr, codesms, [=](cocos2d::String *response){
        
        std::string responseStr = response->getCString();
        CCLOG("responseStr = %s",responseStr.c_str());
        rapidjson::Document m_doc;
        m_doc.Parse<0>(responseStr.c_str());
        if (m_doc.HasParseError()) {
        }
        rapidjson::Value &resultCode = m_doc["resultCode"];
        std::string code = resultCode.GetString();
        if (code == "0") {
//            rapidjson::Value &resultDescription = m_doc["resultDescription"];
            this->addSuccessPayOrderIdString(m_sPzPayWoOrderId.c_str());

        }
        else{
            //            rapidjson::Value &resultDescription = m_doc["resultDescription"];
            //
            //            rapidjson::Value &errorInfo = m_doc["errorInfo"];
            std::string message = "验证码失败,请重新获取验证码";

            this->showMessage(message);

            //            this
        }

    });
}

void PurchaseManager::purchaseFinished(int payCode, const char *tradeID, const char *orderType)
{
    m_isBuying = false;
    Director::getInstance()->resume();
    auto done = CallFunc::create([=](){
        this->didReceiveProduct(payCode,tradeID,orderType);
    });

    Scene *scene = Director::getInstance()->getRunningScene();
    scene->runAction(CCSequence::create(DelayTime::create(0.1),done,NULL));
}

void PurchaseManager::purchaseFailed()
{
    Director::getInstance()->resume();
    CCLOG("purchaseFailed");
    m_isBuying = false;
    Scene *scene = Director::getInstance()->getRunningScene();
    auto done = CallFunc::create([=](){
        this->showMessage("购买失败");
    });
    scene->runAction(Sequence::create(done, NULL));
}
//kProductIndexDirectCoin1,//30金币
//kProductIndexDirectCoin2,//70金币
//kProductIndexDirectCoin3,//100金币
//kProductIndexDirectCoin4,//300金币
//
//kProductIndex5OffGift,// 5折礼包
//
//kProductIndexEndlessMode,//无尽模式
// 充值.
//void umeng::MobClickCpp::pay(double cash, int source, double coin);
//// 充值并购买道具.
//void umeng::MobClickCpp::pay(double cash, int source, const char * item, int amount, double price);
void PurchaseManager::addSuccessPayOrderIdStringForAndGame(const char *formattedOrderIdString)
{
    int productIndex = this->getProductIndex(formattedOrderIdString);
    this->purchaseFinished(productIndex, "", "");
}

void PurchaseManager::validateResult(const char *pPayCode, const char *pOrderID, const char *pTradeID, int options)
{
    if (options == 0) {
        int productIndex = this->getProductIndex(pPayCode);
        this->purchaseFinished(productIndex, "", "");
    }else{
        this->purchaseFailed();
    }

}


void PurchaseManager::didReceiveProduct(int payCode, const char *tradeID, const char *orderType)
{
    log("didReceiveProduct %d",payCode);
    int productIndex = payCode;

    if (productIndex <= kProductIndexNone || productIndex >= kProductIndexMax ) {
//        购买失败...
        return;
    }
    int price = this->getProductPrice(productIndex);
    int count = this->getProductCount(productIndex);

    std::string umgameKey = this->getProductUmGameKey(productIndex);
    if ((productIndex >= kProductIndexDirectCoin1 && productIndex <= kProductIndexDirectCoin4) ||
        (productIndex >= kProductIndexSpecialOffers_1 && productIndex <= kProductIndexSpecialOffers_7) ||
        productIndex == kProductIndexFirstCharge
        ) {//金币购买发放
        
        int coinnum = this->getProductCount(productIndex);
        data::User::getInstance()->goldPlus(coinnum);
        if (productIndex == kProductIndexFirstCharge) {
            UserDefault::getInstance()->setBoolForKey("buy_first_charge",true);
        }
        else if (productIndex >= kProductIndexSpecialOffers_1 && productIndex <= kProductIndexSpecialOffers_7)
        {
            int weekType = productIndex - kProductIndexSpecialOffers_1 + 1;
            UserDefault::getInstance()->setIntegerForKey("open_specialoffer",weekType);
        }
        
    }
    else if (productIndex == kProductIndex5OffGift)// 5折礼包发放...
    {
        int coinnum = this->getProductCount(productIndex);
        data::User::getInstance()->goldPlus(coinnum);

    }
    else if (productIndex == kProductIndexEndlessMode || productIndex == kProductIndexLimitedTimeEndlessMode)//无尽模式发放...
    {
        
        //如果购买成功....
        data::User::getInstance()->setEndlesslock(false);
        Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(popup::EndlessUnlock::ENDLESSBUYSCUUESS, nullptr);
    }
        std::string str = this->getProductName(productIndex);
    std::string message = "Purchase succeed, you've got" + str;
    bool isChinese = (LanguageType::CHINESE == Application::getInstance()->getCurrentLanguage());
    if (isChinese) {
        message =  str + "购买成功";
    }
    this->showMessage(message);
    
	#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		umeng::MobClickCpp::pay(price, kBuyMethodPZPay, umgameKey.c_str(), 1, count);
	#endif
   

//    Purchase succeed, you've got
}

void PurchaseManager::addSuccessPayOrderIdString(const char *formattedOrderIdString)
{
    log("formattedOrderIdString = %s", formattedOrderIdString);
    UserDefault::getInstance()->setStringForKey(kProductOrderId.c_str(), Value(formattedOrderIdString).asString());
    UserDefault::getInstance()->flush();
    
    char *str = new char[strlen(formattedOrderIdString)+1];
    str = strcpy(str, formattedOrderIdString);
    
    const char *temp = strtok(str, ",");
    while(temp != NULL)
    {
        m_OrderIdVector.push_back(Value(temp));
        temp = strtok(NULL, ",");
    }
    delete [] str;
    
    for(auto valueStr:m_OrderIdVector)
    {
        std::string str = valueStr.asString();
        log("str = %s",str.c_str());
    }
    this->queryOrderAndReceiveProduct();
}

void PurchaseManager::removeSuccessPayOrderId(std::string orderId)
{

    for (int i = 0 ; i<m_OrderIdVector.size(); i++) {
        std::string str = Value(m_OrderIdVector.at(i)).asString();
        if (str == orderId)
        {
            m_OrderIdVector.erase(m_OrderIdVector.begin() + i);
            break;
        }
    }
    
    std::string allStr;
    for (int i = 0 ; i<m_OrderIdVector.size(); i++) {
        std::string str = Value(m_OrderIdVector.at(i)).asString();

        if (i == m_OrderIdVector.size()-1) {
            allStr += str;
        }else{
            allStr += str + ",";
        }
    }
    UserDefault::getInstance()->setStringForKey(kProductOrderId.c_str(), allStr);
    UserDefault::getInstance()->flush();
    for(auto valueStr:m_OrderIdVector)
    {
        std::string str = valueStr.asString();
        log("remove str = %s",str.c_str());
    }
}

void PurchaseManager::removeAllPayOrderId()
{
    for (int i = 0 ; i<m_OrderIdVector.size(); i++) {
        std::string str = Value(m_OrderIdVector.at(i)).asString();
        m_OrderIdVector.erase(m_OrderIdVector.begin() + i);
    }
}

void PurchaseManager::queryOrderAndReceiveProduct()
{
    if (m_OrderIdVector.size() > 0) {
        std::string str = Value(m_OrderIdVector.back()).asString();
        std::string productID = UserDefault::getInstance()->getStringForKey(str.c_str());
        log("queryOrderAndReceiveProduct productID = %s",productID.c_str());
        if (productID.length()>0) {
            int productIndex = this->getProductIndex(productID.c_str());
            log("productIndex = %d",productIndex);
            this->purchaseFinished(productIndex, "0", Value(kBuyMethod91).asString().c_str());
            this->removeSuccessPayOrderId(str);//移除一个订单..
            this->queryOrderAndReceiveProduct();//查询时候还有其他订单...
        }
    }

}


void PurchaseManager::showMessage(std::string message)
{
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
//    Sprite *bg = Sprite::create();
//    bg->setTextureRect(Rect(0, 0, 50, 50));
//    bg->setColor(ccBLACK);
//    LabelEffect
    Scene *scene = Director::getInstance()->getRunningScene();

    auto labelTemp = scene->getChildByTag(999);
    if (labelTemp) {
        labelTemp->stopAllActions();
        labelTemp->removeFromParentAndCleanup(true);
    }
    
    
    auto label = Label::create(message, "", 70);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 1.8));
    label->setColor(Color3B(255, 233, 68));
//    void LabelTTF::enableShadow(const Size &shadowOffset, float shadowOpacity, float shadowBlur, bool updateTexture)

    label->enableShadow(Color4B(96, 23, 0, 255),Size(0, -2));
    
    scene->addChild(label,1000,999);
    auto *fadein = FadeTo::create(0.2, 255);
    auto *move = MoveBy::create(0.5, Vec2(0, 30));
    auto *fadeout = FadeTo::create(0.5, 0);
    auto done = CallFunc::create([=](){
        label->removeFromParentAndCleanup(true);
    });
    label->runAction(Sequence::create(fadein,DelayTime::create(1.0),move,done, NULL));
    label->runAction(Sequence::create(DelayTime::create(1.2),fadeout, NULL));


}
