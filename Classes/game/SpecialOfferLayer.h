//
//  SpecialOfferLayer.h
//  jelly3.5
//
//  Created by mac on 15/9/2.
//
//

#ifndef __jelly3_5__SpecialOfferLayer__
#define __jelly3_5__SpecialOfferLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "main/Main.h"
#include "popup/PopBase.h"
#include "data/Shop.h"
#include "data/Item.h"
#include "data/User.h"
#include "popup/PopBase.h"
typedef enum
{
    MondayType          = 1,
    TuesdayType         = 2,
    WednesdayType       = 3,
    ThursdayType        = 4,
    FridayType          = 5,
    SaturdayType        = 6,
    SundayType          = 0
}WeekType;

typedef enum
{
    NoneType    = 0,
    FirstChargePacksType,
    SpecialOffersType,
}PackageGiftType;

namespace popup{
    class SpecialOfferLayer :public PopBase
    {
    public:
        cocos2d::Node* m_pPanel;
        ~SpecialOfferLayer();
        /*
         *  关闭
         */
        void closePop() override;
        bool m_bNotPushToColse;
        
    public:
        static SpecialOfferLayer *createWithType(PackageGiftType type);
        WeekType m_WeekType;
        PackageGiftType m_PackageType;
        bool init(PackageGiftType type);
        void showFirstChargePacks();
        void showSpecialOffers();
        cocos2d::EventListenerCustom* _goldlistener;
        /**
         *	商品点击
         */
        void goodsClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
        /**
         *	回到主菜单点击
         */
        void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
        void coinFly(cocos2d::ui::Widget* ref);
        
        void setDisPlayWithWeek(int week);

    };
}
#endif /* defined(__jelly3_5__SpecialOfferLayer__) */
