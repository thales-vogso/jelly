//
//  PaymentLayer.h
//  jelly3.5
//
//  Created by mac on 15/10/8.
//
//

#ifndef __jelly3_5__PaymentLayer__
#define __jelly3_5__PaymentLayer__

#include <stdio.h>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "main/Main.h"
#include "popup/PopBase.h"
#include "data/Shop.h"
#include "data/Item.h"
#include "data/User.h"
#include "popup/PopBase.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
#include "AndroidPurchase/PurchaseManager.h"
#include "AndroidPurchase/AndroidSDKHelper.h"


USING_NS_CC;
USING_NS_CC_EXT;
namespace popup{
    class PaymentLayer :public Layer,public EditBoxDelegate

    {
    public:
        ProductIndex m_ProductIndex;
        cocos2d::Node* m_pPanel;
        cocos2d::ui::Text *m_pPhoneNumber;
        cocos2d::ui::Text *m_pAuthNumber;
        ~PaymentLayer();
        /*
         *  关闭
         */
//        void closePop() override;
		cocos2d::ui::EditBox *m_pNumberEditBox;
		cocos2d::ui::EditBox *m_pAuthEditBox;
        cocos2d::EventListenerCustom* _listener;


    public:
        static PaymentLayer *createWithType(ProductIndex productIndex);
        bool init(ProductIndex productIndex);
        void setDisPlayWithType(ProductIndex productIndex);
        void buyButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
        void getAuthButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
        void closeBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);

        //当编辑框获得焦点时将被调用..
		virtual void editBoxEditingDidBegin(cocos2d::ui::EditBox* editBox);
        //当编辑框失去焦点后将被调用..
		virtual void editBoxEditingDidEnd(cocos2d::ui::EditBox* editBox);
        //当编辑框内容发生改变将被调用..
		virtual void editBoxTextChanged(cocos2d::ui::EditBox* editBox, const std::string& text);
        //当编辑框的结束操作被调用..
		virtual void editBoxReturn(cocos2d::ui::EditBox* editBox);


    };
}
#endif /* defined(__jelly3_5__PaymentLayer__) */
