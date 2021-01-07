package org.cocos2dx.cpp;

import android.app.Application;

import com.xiaomi.gamecenter.sdk.MiCommplatform;
import com.xiaomi.gamecenter.sdk.entry.MiAppInfo;

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
        MiAppInfo appInfo = new MiAppInfo();
        appInfo.setAppId("2882303761517404466");
        appInfo.setAppKey("5421740410466");
        MiCommplatform.Init(this, appInfo);
    }
}
