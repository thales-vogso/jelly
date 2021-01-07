/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;

import com.umeng.mobclickcpp.MobClickCppHelper;
import com.xiaomi.gamecenter.sdk.MiCommplatform;
import com.xiaomi.gamecenter.sdk.MiErrorCode;
import com.xiaomi.gamecenter.sdk.OnLoginProcessListener;
import com.xiaomi.gamecenter.sdk.OnPayProcessListener;
import com.xiaomi.gamecenter.sdk.entry.MiAccountInfo;
import com.xiaomi.gamecenter.sdk.entry.MiBuyInfo;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.UUID;

//import cn.cmgame.billing.api.BillingResult;
//import cn.cmgame.billing.api.GameInterface;

//import com.hzpz.pay.PzPay;
//import com.hzpz.pay.data.CheckOrder;
//import com.hzpz.pay.data.PayData;
public class AppActivity extends Cocos2dxActivity {
    private static AppActivity instance=null;
    private static Context mContext;
    public static String PayPrderId = "";
    public static String TAG = "candy";
    public static boolean isLogoin = false;

//    private PzPay pay;
//    CheckOrder order;
//    private List<PayData> listPayOrderInfo = new ArrayList<PayData>();

    private static AppActivity thisActivity;
    //public static Handler handler=null;
    private static int num=0;
    protected void onCreate (Bundle savedInstanceState){
        super.onCreate(savedInstanceState);
        MobClickCppHelper.init(this);
        Log.d(TAG, "开始游戏~~~~~~~");
        instance = this;
        mContext = AppActivity.this;
//        Log.d(TAG,"设备识别码：" + getDeviceInfo(AppActivity.this));
//        initPZPay();
        //andgame
//        GameInterface.initializeApp(this);
//        boolean isMusicEnabeld = isMusicEnabled();
//        setMusicEnabled(isMusicEnabeld);

    }

    static {
        MobClickCppHelper.loadLibrary();
    }
    private void logoIn()
    {
        MiCommplatform.getInstance().miLogin( instance,
                new OnLoginProcessListener()
                {
                    @Override
                    public void finishLoginProcess( int code ,MiAccountInfo arg1)
                    {
                        switch( code )
                        {
                            case MiErrorCode.MI_XIAOMI_PAYMENT_SUCCESS:
                                // 登陆成功
                                //获取用户的登陆后的UID（即用户唯一标识）
                                long uid = arg1.getUid();
//                                **/\**以下为获取session并校验流程，如果是网络游戏必须校验，如果是单机游戏或应用可选\**/**
                             //获取用户的登陆的Session（请参考[5.3.3流程校验Session有效性](#8)）
                             String session = arg1.getSessionId();
                             //请开发者完成将uid和session提交给开发者自己服务器进行session验证
                                Log.d(TAG, "登陆成功");
                                isLogoin = true;
                                break;
                             case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_LOGIN_FAIL:
                             // 登陆失败
                                 Log.d(TAG, "登陆失败");
                                 isLogoin = false;
                             break;
                             case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_CANCEL:
                             // 取消登录
                                 Log.d(TAG, "取消登录" );
                                 isLogoin = false;

                                 break;
                             case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_ACTION_EXECUTED:
                             //登录操作正在进行中
                                 Log.d(TAG, "登录失败");
                                 isLogoin = false;

                                 break;
                             default:
                             // 登录失败
                                 isLogoin = false;
                                 break;
                        }
                    }
                } );
    }
    /***PZPay
    protected void onDestroy() {
        super.onDestroy();

        Log.d(TAG, "onDestroy  Main取消支付结果接收");
        // 取消支付结果接收
        pay.unregisterPayListener();
    }

    private void initPZPay()
    {
        Log.d(TAG, "initPZPay");

        pay = PzPay.getInstanct(this, "215", 10018, null, new PzPay.PzPayingListener() {
            @Override
            public void onPayFinished(boolean successed, CheckOrder msg) {
                Log.d(TAG, "pay-Main支会返回.....");
                if (successed && msg != null) { // 支付成功
                    Log.d(TAG, "pay-支付成功" + PayPrderId);
                    deliverProduct(PayPrderId);
                } else { // 支付失败
                    Log.d(TAG, "pay-支付失败");
                    payFaile();
                }
                order = msg;
                Log.d(TAG, "pay-支付结果：" + msg.status);
                Log.d(TAG, "pay-支付结果returnmsg：" + msg.returnmsg);
                Log.d(TAG, "pay-支付结果returnvalue：" + msg.returnvalue);

                Log.d(TAG, "pay-支付结果fee：" + msg.fee);

                Log.d(TAG, "pay-支付结果toString：" + msg.toString());
                Log.d(TAG, "pay-支付结果monery：" + msg.monery);
                Log.d(TAG, "pay-支付结果orderid：" + msg.orderid);




            }

            @Override
            public void onPaying(List datas) {
                Log.d(TAG,"pay-onPaying");
                if(datas!=null){
//                    listPayOrderInfo.addAll(datas);
//                    String orderList = "";
//                    for(int i = 0;i < listPayOrderInfo.size();i++){
//                        orderList += (listPayOrderInfo.get(i).getId());
//                        if (i < listPayOrderInfo.size()-1) {
//                            orderList += ",";
//                        }
//                    }
//                    Log.d(TAG, "pay-onPaying：" + orderList.toString());

//                    adapter.notifyDataSetChanged();
                }
            }
        });

    }
*/

    private native void setMusicEnabled(boolean enabled);

    // 声音是否开启 移动基地
//    public static boolean isMusicEnabled() {
//        return GameInterface.isMusicEnabled();
//    }
//
    public void openMoreGameLayer() {
        Log.d(TAG, "openMoreGameLayer");
//        GameInterface.viewMoreGames(instance);
        logoIn();

    }
    public static Object myInstance() {
        return instance;
    }
    private native void deliverProduct(String orderIdListString);
    private native void andGameDeliverProduct(String orderIdListString);
    private native void payFaile();
    public void buyPZPayProduct(String productID,            // id
                               int productNum,              // 数量
                               String orderID,              // 订单id //百度91也用uuid
                               String productPrice,         // 价格
                               String productName,          // 名称
                               String productDescription,   // 描述
                               int type,                    // 购买方式
                               String userID                // 用户id
    )
    {
        Log.d(TAG,"pay-buyPZPayProduct");
        Log.d(TAG,"pay-buyProduct" + productID + "," + productNum  + "," + orderID  + "," + productPrice  + "," + productName  + "," + productDescription  + "," + type  + "," + userID);

        Message msg = new Message();
        msg.what = type;
        String product = productID + ":" +
                Integer.toString(productNum) + ":" +
                orderID + ":" +
                productPrice + ":" +
                productName + ":" +
                productDescription + ":" +
                userID;
        Log.d(TAG, "product:\t" + product);
        msg.obj = product;
//        deliverProduct(orderID);
        boolean isRepeat = true;
//        if (productID == "5" || productID == "6" || productID == "7")
//        {
//            isRepeat = false;
//        }
//        PayPrderId = orderID;
//        doBilling(productID,orderID,isRepeat,true);

        handler.sendMessage(msg);

    }

//    private void doBilling(String billingIndex, String cpparam, boolean isRepeat, boolean isSMS) {
//        // 支付或购买道具回调结果
//        final GameInterface.IPayCallback payCallback = new GameInterface.IPayCallback() {
//            @Override
//            public void onResult(int resultCode, String billingIndex, Object obj) {
//                String result;
//                switch (resultCode) {
//                    case BillingResult.SUCCESS:
//                        result = "购买道具：[" + billingIndex + "] 成功！";
//                        andGameDeliverProduct(billingIndex);
//                        break;
//                    case BillingResult.FAILED:
//                        result = "购买道具：[" + billingIndex + "] 失败！";
//                        payFaile();
//                        break;
//                    default:
//                        result = "购买道具：[" + billingIndex + "] 取消！";
//                        payFaile();
////                        andGameDeliverProduct(billingIndex);
//
//                        break;
//                }
//                Log.d(TAG,"doBilling callback result:"+result + "obj" + obj.toString());
//                String platform = "andgame";
//            }
//        };
//        Log.d(TAG, "doBilling" + billingIndex+":"+cpparam+":"+(isRepeat?"repeat":"non-repeat"));
////        if (cpparam.length() == 0)
////        {
////            cpparam = null;
////        }
//        GameInterface.doBilling(mContext, isSMS, isRepeat, billingIndex, null, payCallback);
//    }
    private Handler handler = new Handler() {

        public void handleMessage(Message msg) {
            super.handleMessage(msg);
            Log.d(TAG,"pay-buyPZPayProduct_handler" + msg.toString());

            Log.d(TAG,"\nMM 支付 " + String.valueOf(msg.obj));
            String info = (String)msg.obj;
            String[] array = info.split(":");
            for (String string : array )
            {
                /**
                 * 0. product_id
                 * 1. count
                 * 2. order_id
                 * 3. price
                 * 4. name
                 * 5. description
                 * 6. user
                 */
                Log.d(TAG,"string: " + string);
            }
//            String cporderid = UUID.randomUUID().toString();
//            Log.d(TAG,"\n计费点代码： " + array[0] + "\t订单ID： " + array[2] + "\t价格： " + array[3]);
            PayPrderId = array[2];
            int price = Integer.parseInt(array[3]);
            Log.d(TAG,"\n计费点代码： " + array[0] + "\t订单ID： " + array[2] + "\t价格： " + price);

//            pay.pay(price, array[2], array[0]);
            if (isLogoin)
            {
                MiBuyInfo miBuyInfo = new MiBuyInfo();
                miBuyInfo.setCpOrderId( UUID.randomUUID().toString() );//订单号唯一（不为空）
                miBuyInfo.setProductCode( "productCode" );//商品代码，开发者申请获得（不为空）
                miBuyInfo.setCount( 3 );//购买数量(商品数量最大9999，最小1)（不为空）
                MiCommplatform.getInstance().miUniPay(instance , miBuyInfo,
                        new OnPayProcessListener()
                        {
                            @Override
                            public void finishPayProcess( int code ) {
                                switch( code ) {
                                    case MiErrorCode.MI_XIAOMI_PAYMENT_SUCCESS:
                                        //购买成功，请处理发货
                                        break;
                                    case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_PAY_CANCEL:
                                        //取消购买
                                        break;
                                    case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_PAY_FAILURE:
                                        //购买失败
                                        break;
                                    case MiErrorCode.MI_XIAOMI_PAYMENT_ERROR_ACTION_EXECUTED:
                                        //操作正在执行
                                        break;
                                    default:
                                        //购买失败
                                        break;
                                }
                            }
                        });
            }else{
                logoIn();
            }

        }

    };


    public static String getDeviceInfo(Context context) {
        try{
            org.json.JSONObject json = new org.json.JSONObject();
            android.telephony.TelephonyManager tm = (android.telephony.TelephonyManager) context
                    .getSystemService(Context.TELEPHONY_SERVICE);

            String device_id = tm.getDeviceId();

            android.net.wifi.WifiManager wifi = (android.net.wifi.WifiManager) context.getSystemService(Context.WIFI_SERVICE);

            String mac = wifi.getConnectionInfo().getMacAddress();
            json.put("mac", mac);

            if( TextUtils.isEmpty(device_id) ){
                device_id = mac;
            }

            if( TextUtils.isEmpty(device_id) ){
                device_id = android.provider.Settings.Secure.getString(context.getContentResolver(),android.provider.Settings.Secure.ANDROID_ID);
            }

            json.put("device_id", device_id);

            return json.toString();
        }catch(Exception e){
            e.printStackTrace();
        }
        return null;
    }

}