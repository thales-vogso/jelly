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

import android.app.Activity;
import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.text.TextUtils;
import android.util.Log;

import com.umeng.mobclickcpp.MobClickCppHelper;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.HashMap;
import java.util.Map;

import cn.egame.terminal.paysdk.EgameExitListener;
import cn.egame.terminal.paysdk.EgamePay;
import cn.egame.terminal.paysdk.EgamePayListener;

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
//    private PzPay pay;
//    CheckOrder order;
//    private List<PayData> listPayOrderInfo = new ArrayList<PayData>();

//    private static AppActivity thisActivity;
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
        EgamePay.init(this);
    }

    static {
        MobClickCppHelper.loadLibrary();
    }
    public void openMoreGameLayer() {
        Log.d(TAG, "openMoreGameLayer");
        EgamePay.moreGame(instance);
    }
    public void openQuitLayer() {
        this.exitGame();
    }
    public void exitGame() {
        Log.d(TAG, "exitGame");

        instance.runOnUiThread(new Runnable() {
            @Override
            public void run() {
                EgamePay.exit(instance, new EgameExitListener() {
                    @Override
                    public void cancel() {
                        // DO NOTHING
                    }
                    @Override
                    public void exit() {
                        instance.finish();
                        android.os.Process.killProcess(android.os.Process.myPid());
                    }
                });
            }
        });
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
        handler.sendMessage(msg);
//        deliverProduct(orderID);
//        boolean isRepeat = true;
//        if (productID == "5" || productID == "6" || productID == "7")
//        {
//            isRepeat = false;
//        }
//        PayPrderId = orderID;
//        doBilling(productID,orderID,isRepeat,true);
    }
    public static void dlog(String message) {
        if(true) {
            Log.d(TAG, message);
        }
    }
    /**
     * 电信爱游戏支付
     */
    private void makePurchaseTelecom(String alias, final String product_id) {
        dlog("telecom-make-purchase:"+product_id);

        final Activity thisActivity = this;
        HashMap map = new HashMap<String, String>();
        map.put(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS, alias);
        dlog("telecom-kv:"+map.toString());

        EgamePay.pay(thisActivity, map, new EgamePayListener() {
            @Override
            public void paySuccess(Map<String, String> map) {
                dlog("telecom-success:"+map.toString());
                String alias = map.get(EgamePay.PAY_PARAMS_KEY_TOOLS_ALIAS);
                deliverProduct(product_id);

            }

            @Override
            public void payFailed(Map<String, String> map, int i) {
                dlog("telecom-failed:"+map.toString() + "//" + String.valueOf(i));
                payFaile();
            }

            @Override
            public void payCancel(Map<String, String> map) {
                dlog("telecom-cancel:"+map.toString());
                payFaile();
            }
        });
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
            makePurchaseTelecom(array[0],PayPrderId);

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
