//
//  AdsmogoBanner.h
//  AdsMogoCocos2dxSample
//
//  Created by Chasel on 14-4-14.
//
//

#ifndef __AdsMogoCocos2dxSample__AdsmogoBanner__
#define __AdsMogoCocos2dxSample__AdsmogoBanner__

#include <iostream>

#endif /* defined(__AdsMogoCocos2dxSample__AdsmogoBanner__) */

typedef enum {
    AdsmogoBannerTypeUnknown          = 0,  //error
	AdsmogoBannerTypeNormalBanner     = 1,  //e.g. 320 * 50 ; 320 * 48...           iphone banner
    AdsmogoBannerTypeLargeBanner      = 2,  //e.g. 728 * 90 ; 768 * 110             ipad only
    AdsmogoBannerTypeMediumBanner     = 3,  //e.g. 468 * 60 ; 508 * 80              ipad only
    AdsmogoBannerTypeRectangle        = 4,  //e.g. 300 * 250; 320 * 270             ipad only
    AdsmogoBannerTypeSky              = 5,  //Don't support
    AdsmogoBannerTypeFullScreen       = 6,  //iphone full screen ad
    AdsmogoBannerTypeVideo            = 11, //iPad and iPhone use video ad
    AdsmogoBannerTypeiPadNormalBanner = 8,  //ipad use iphone banner
    AdsmogoBannerTypeiPadFullScreen   = 9,  //ipad full screen ad e.g. 1024*768     ipad only
    AdsmogoBannerTypeCustomSize       = 10, //iPad and iPhone use custom size
    AdsmogoBannerTypeSplash           = 12, // IOS Splash Ad
} AdsmogoBannerType;


typedef enum {
    AdMoGoPointTypeTop_left       = 1 << 0,
    AdMoGoPointTypeTop_middle     = 1 << 1,
    AdMoGoPointTypeTop_right      = 1 << 2,
    
    AdMoGoPointTypeMiddle_left    = 1 << 3,
    AdMoGoPointTypeMiddle_middle  = 1 << 4,
    AdMoGoPointTypeMiddle_right   = 1 << 5,
    
    AdMoGoPointTypeDown_left      = 1 << 6,
    AdMoGoPointTypeDown_middle    = 1 << 7,
    AdMoGoPointTypeDown_right     = 1 << 8,
    AdMoGoPointTypeCustom         = 1 << 9,
}AdMoGoPointType;

class AdsmogoBanner  {
public:
    static AdsmogoBanner *sharedBanner();
    /**
     初始化banner
     mogoid   芒果id
     AdsmogoBannerType  广告类型
     x  广告位置X坐标
     y  广告位置Y坐标
     */
    void createBanner(char* mogoid,AdsmogoBannerType type,float x, float y,bool ismanualrefresh);
    
    /**
     *  初始化banner
     *
     *  @param mogoid          芒果id
     *  @param type            请求广告类型
     *  @param pointType       广告位置类型
     *  @param ismanualrefresh 是否手动刷新
     */
    void createBanner(char * mogoid,AdsmogoBannerType type, AdMoGoPointType  pointType,bool  ismanualrefresh);
    
    
    
    //释放banner广告
    void releaseBanner();
    
    //手动刷新广告，使用此接口必须保证芒果后台配置刷新信息为禁用，否则该方法不生效。并且createBanner中ismanualrefresh 设置为YES
    void refreshBanner();
    
    //隐藏banner
    void hidenBanner();
    
    //如果调用hidenBanner()后，需要展示banner 调用showBanner()
    void showBanner();
};