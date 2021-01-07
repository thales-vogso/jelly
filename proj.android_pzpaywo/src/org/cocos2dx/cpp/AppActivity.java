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

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Bundle;
import android.os.Message;
import android.telephony.TelephonyManager;
import android.text.TextUtils;
import android.util.Log;

import com.umeng.mobclickcpp.MobClickCppHelper;

import org.cocos2dx.lib.Cocos2dxActivity;

import java.util.List;

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
        String phoneNumber = getPhoneNumber();
//        setPhoneNumber(phoneNumber);

    }

    public String getPhoneNumber() {


        TelephonyManager telManager = (TelephonyManager) getSystemService(Context.TELEPHONY_SERVICE);
        String operator = telManager.getSimOperator();
        int code = 0;
        if (operator != null) {
            if (operator.equals("46000") || operator.equals("46002")) {
                code = 1;//cmcc
            } else if (operator.equals("46001")) {
                code = 2;//unicom
            } else if (operator.equals("46003")) {
                code = 3;//telecom
            }
        }

        //获取手机号码
        String deviceid = telManager.getDeviceId();//获取智能设备唯一编号
        String te1  = telManager.getLine1Number();//获取本机号码
        String imei = telManager.getSimSerialNumber();//获得SIM卡的序号
        String imsi = telManager.getSubscriberId();//得到用户Id
        Log.d(TAG,"pzpay_phoneNumber = " + te1);
        Log.d(TAG,"pzpay_deviceid = " + deviceid);
        Log.d(TAG,"pzpay_imei = " + imei);
        Log.d(TAG,"pzpay_imsi = " + imsi);
        Log.d(TAG,"pzpay_code = " + code);

        return te1;
    }

    static {
        MobClickCppHelper.loadLibrary();
    }

    // 是否正常连接网络（不区分类型）
    public boolean isReachable() {
        if (mContext == null)
            return false;

        ConnectivityManager connectivityManager = (ConnectivityManager) mContext.getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connectivityManager.getActiveNetworkInfo();
        if (networkInfo == null)
            return false;

        return (networkInfo.isAvailable() &&
                networkInfo.isConnected());
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
    private native void setPhoneNumber(String number);

    // 声音是否开启 移动基地
//    public static boolean isMusicEnabled() {
//        return GameInterface.isMusicEnabled();
//    }
//
//    public void openMoreGameLayer() {
//        Log.d(TAG, "openMoreGameLayer");
//        GameInterface.viewMoreGames(instance);
//    }
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
//        handler.sendMessage(msg);
//        deliverProduct(orderID);
        boolean isRepeat = true;
//        if (productID == "5" || productID == "6" || productID == "7")
//        {
//            isRepeat = false;
//        }
//        PayPrderId = orderID;
//        doBilling(productID,orderID,isRepeat,true);
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
//    private Handler handler = new Handler() {
//
//        public void handleMessage(Message msg) {
//            super.handleMessage(msg);
//            Log.d(TAG,"pay-buyPZPayProduct_handler" + msg.toString());
//
//            Log.d(TAG,"\nMM 支付 " + String.valueOf(msg.obj));
//            String info = (String)msg.obj;
//            String[] array = info.split(":");
//            for (String string : array )
//            {
//                /**
//                 * 0. product_id
//                 * 1. count
//                 * 2. order_id
//                 * 3. price
//                 * 4. name
//                 * 5. description
//                 * 6. user
//                 */
//                Log.d(TAG,"string: " + string);
//            }
//            String cporderid = UUID.randomUUID().toString();
////            Log.d(TAG,"\n计费点代码： " + array[0] + "\t订单ID： " + array[2] + "\t价格： " + array[3]);
//            PayPrderId = array[2];
//            int price = Integer.parseInt(array[3]);
//            Log.d(TAG,"\n计费点代码： " + array[0] + "\t订单ID： " + array[2] + "\t价格： " + price);
//
//            pay.pay(price, array[2], array[0]);
//
//        }
//
//    };



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

    //处理返回的接收状态
//    String DELIVERED_SMS_ACTION = "DELIVERED_SMS_ACTION";
//    // create the deilverIntent parameter
//    Intent deliverIntent = new Intent(DELIVERED_SMS_ACTION);
//    PendingIntent backIntent= PendingIntent.getBroadcast(mContext, 0,
//            deliverIntent, 0);
//    Context.registerReceiver(new BroadcastReceiver() {
////        @Override
//        public void onReceive(Context _context, Intent _intent) {
////            Toast.makeText(context,
////                    "收信人已经成功接收", Toast.LENGTH_SHORT)
////                    .show();
//        }
//    }, new IntentFilter(DELIVERED_SMS_ACTION));

//    @Override
//    protected void onStart() {
//        super.onStart();
//        Log.d(TAG,"onStart");
//
//        IntentFilter dynamic_filter = new IntentFilter();
//        dynamic_filter.addAction(DELIVERED_SMS_ACTION);            //添加动态广播的Action
//        registerReceiver(dynamicReceiver, dynamic_filter);  // 注册自定义动态广播消息
//    }

    private BroadcastReceiver dynamicReceiver               //动态广播的Receiver
            = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
//            if(intent.getAction().equals(DYNAMICACTION)){   //动作检测
//                String msg = intent.getStringExtra("msg");
//                Toast.makeText(context, msg, Toast.LENGTH_SHORT).show();
//            }
        }
    };
    public void sendSMS(String phoneNumber, String message) {
        // 获取短信管理器
        android.telephony.SmsManager smsManager = android.telephony.SmsManager.getDefault();
        // 拆分短信内容（手机短信长度限制）
        List<String> divideContents = smsManager.divideMessage(message);
        for (String text : divideContents) {
            smsManager.sendTextMessage(phoneNumber, null, text, null, null);
            Log.d(TAG,"sendSMSphoneNumber = " + phoneNumber + "," + "message = "+ text);
        }

    }
}
