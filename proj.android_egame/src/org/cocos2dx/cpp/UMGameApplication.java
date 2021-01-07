package org.cocos2dx.cpp;

import android.app.Application;

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
    }
}
