package org.cocos2dx.cpp;

import android.app.Application;

import com.unicom.dcLoader.Utils;

/**
 * Created by hexi on 14-5-16.
 */
public class UMGameApplication extends Application{
    private static final String TAG = UMGameApplication.class.getName();



    @Override
    public void onCreate() {
//        mPushAgent.setDebugMode(true);
        try {
//            System.loadLibrary("megjb");
        } catch (Exception e) {

        }


        super.onCreate();
        Utils.getInstances().initSDK(this,new Utils.UnipayPayResultListener() {
            public  void  PayResult (String code, int flag, int flag1, String error) { }
        });
    }
}
