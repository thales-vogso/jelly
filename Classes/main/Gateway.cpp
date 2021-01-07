/****************************************************************************
*	@       	       
*	@desc	开始界面
*	@date	2014-10-29
*	@author	120101
*	@       	       
*	@file	gateway/Gateway.h
*	@modify	null
******************************************************************************/

#include "Gateway.h"
USING_NS_CC;
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "AdsmogoBanner.h"
#include "AdsMogoInterstitial.h"
#endif
#include "AndroidPurchase/AndroidSDKHelper.h"
#include "AndroidPurchase/PurchaseManagerDefine.h"
#include "popup/Info.h"
//#if(CC_TARGET_PLATFORM!=CC_PLATFORM_WIN32)
//#include "Cocos2dx/Common/CCUMSocialSDK.h"
//#include "Cocos2dx/ShareButton/UMShareButton.h"
//USING_NS_UM_SOCIAL;
//#endif
using namespace popup;
using namespace ui;
using namespace cocostudio::timeline;
const std::string  Gateway::ENDLESSGAME = "endlessgame";
Gateway::~Gateway()
{
	_eventDispatcher->removeEventListener(_tinyLoadinglistener);
	_eventDispatcher->removeEventListener(_goldUIListener);
	_eventDispatcher->removeCustomEventListeners(EndlessUnlock::ENDLESSBUYSCUUESS);
    _eventDispatcher->removeCustomEventListeners(data::User::BUY_FIRST_CHARGE);

	//_eventDispatcher->removeEventListener(_itemUIListener);
	//_eventDispatcher->removeCustomEventListeners(Gateway::ENDLESS_GAME);
}
Node* Gateway::getPanel(){
#ifdef LONGBAO
	PANEL_NAME = "csb/longbao/ui/gateway.csb";
#endif
#ifdef CANDY
	PANEL_NAME = "csb/main/gateway.csb";
#endif	
	_panel = CSLoader::createNode(PANEL_NAME);
	return _panel;
}
Node* Gateway::getWidgetFromPanel(std::string name){
	Node* ui = Main::seekNodeByName(_panel, name);
	return ui;
}
Widget* Gateway::getWidgetFromPanel(int id){
	std::string name = getWidgetNameByEnum(id);
	return (Widget*)getWidgetFromPanel(name);
}
std::string Gateway::getWidgetNameByEnum(int id){
	std::string str;

	switch (id)
	{
	case WidgetName::BUTTON_START:
		str = "startBtn";
		break;
	case WidgetName::BUTTON_ENDLESS:
		str = "endlessBtn";
		break;
	case WidgetName::BUTTON_SETTING:
		str = "settingBtn";
		break;
	case WidgetName::BUTTON_HELP:
		str = "helpBtn";
		break;
	case WidgetName::TEXT_START:
		str = "startText";
		break;
	case WidgetName::TEXT_SAVE:
		str = "saveText";
		break;
	case WidgetName::TEXT_ENDLESS:
		str = "endlessText";
		break;
	case WidgetName::TEXT_STARTON:
		str = "starton";
		break;
	case WidgetName::TEXT_GOON:
		str = "goon";
		break;
	case WidgetName::TEXT_GUIDE:
		str = "guide";
		break;
	case WidgetName::BLACK:
		str = "black";
    case WidgetName::IMAGE_41:
		str = "Image_41";
            
		break;
    case WidgetName::BUTTON_MOREGAME:
        str = "moregameBtn";
        break;
            
    case WidgetName::BUTTON_INFO:
        str = "infoBtn";
        break;
    case WidgetName::BUTTON_LIBAO:
        str = "Button_3";
        break;
            
	default:
		break;
	}
	return str;
}

bool Gateway::init()
{
	if (!Layer::init())
	{
		return false;
	}
	/*
	*	测试安卓代码
	*/

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width*0.5, visibleSize.height*0.5);

	/**  cocostuido原件  */
	Node* panel = getPanel();
	panel->setPosition(midPoint);
	addChild(panel, 1);

#ifdef LONGBAO
	//Node* bg1 = panel->getChildByName("gateway")->getChildByName("map1");
	//Node* bg2 = panel->getChildByName("gateway")->getChildByName("map2");
	//float scale = visibleSize.width / 2208;
	//bg1->setScaleY(scale);
	//bg2->setScaleY(scale);
	ImageView* bg = ImageView::create("map/map7.jpg");
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setPosition(midPoint);
	bg->setScale(scale);
	bg->setTouchEnabled(true);
	bg->setSwallowTouches(true);
	addChild(bg, 0);
#endif
	/*  获取元素  */
	/**  上面按钮  */
    Widget* moreButton = getWidgetFromPanel(BUTTON_MOREGAME);
	Widget* setting = getWidgetFromPanel(BUTTON_SETTING);
	Widget* settingTouch = (Widget*)Main::seekNodeByName(setting, "touch");
    Widget *moreTouch = (Widget*)Main::seekNodeByName(moreButton, "touch");
	Widget* help = getWidgetFromPanel(BUTTON_HELP);
	Widget* helpTouch = (Widget*)Main::seekNodeByName(help, "touch");
    Widget* discount = getWidgetFromPanel(IMAGE_41);
    Widget* discountTouch = (Widget*)Main::seekNodeByName(discount, "touch");
    discount->setVisible(false);

//    moreButton->setPosition(moreButton->getPosition() + Vec2(1630, 0));
    moreButton->setPosition(Vec2(2208 + visibleSize.width*0.5 - 1104 - 26 - 45 - 100, visibleSize.height - 26 - 45 ) );

    Widget* infoButton = getWidgetFromPanel(BUTTON_INFO);
    infoButton->setVisible(false);
    Widget* infoTouch = (Widget*)Main::seekNodeByName(infoButton, "touch");

    TextAtlas* discountText = (TextAtlas*)Main::seekNodeByName(discount, "Text_7");
    infoButton->setPosition(Vec2(2208 + visibleSize.width*0.5 - 1104 - 26 - 45 - 440, visibleSize.height - 26 - 45 ) );

//    discountText->setVisible(false);
#if TARGET_CHANNEL == TTARGET_CHANNE_PZPAY
    moreButton->setVisible(true);
#elif TARGET_CHANNEL == TARGET_CHANNE_AND_GAME
    moreButton->setVisible(false);
#elif TARGET_CHANNEL == TARGET_CHANNE_CMCC
    moreButton->setVisible(false);
#elif TARGET_CHANNEL == TTARGET_CHANNE_PZPAYWO
    moreButton->setVisible(true);
#elif TARGET_CHANNEL == TARGET_CHANNE_EGAME
    moreButton->setVisible(true);
    infoButton->setVisible(true);
#elif TARGET_CHANNEL == TARGET_CHANNE_UNIPAY
    moreButton->setVisible(true);
#elif TARGET_CHANNEL == TARGET_CHANNE_SWSDK
    moreButton->setVisible(true);
#elif TARGET_CHANNEL == TARGET_CHANNE_TIANYI
	moreButton->setVisible(false);
#else
#error
#endif
    Widget* libaoButton = getWidgetFromPanel(BUTTON_LIBAO);
    libaoButton->setPosition(Vec2(-(visibleSize.width*0.5 - 1104) + 26 + 45 + 100, visibleSize.height - 26 - 45));
//    libaoButton->setVisible(false);
#ifdef PACKAGE_VETSION
    this->showDiscountWithEndless();
    this->showSpecialOffer();
#else
    libaoButton->setVisible(false);
#endif
    Widget* libaoTouch = (Widget*)Main::seekNodeByName(libaoButton, "touch");
//#if (CC_TARGET_PLATFORM!=CC_PLATFORM_WIN32)
//
//	// 创建分享按钮, 参数1为按钮正常情况下的图片, 参数2为按钮选中时的图片,参数3为友盟appkey, 参数4为分享回调..
//	UMShareButton *shareButton = UMShareButton::create("pic/fenxiang.png","pic/fenxiang.png", "546c65a4fd98c52d32001daf", share_selector(shareCallback)) ;
//	// 显示在友盟分享面板上的平台..
//	vector<int>* platforms = new vector<int>();
//	platforms->push_back(SINA);
//	platforms->push_back(RENREN) ;
//	//platforms->push_back(TWITTER) ;
//	//platforms->push_back(FACEBOOK) ;
//	//platforms->push_back(QQ);
//	//platforms->push_back(WEIXIN);
//   // platforms->push_back(WEIXIN_CIRCLE);
//	//platforms->push_back(QZONE);
//    
//	// 设置友盟分享面板上显示的平台..
//	shareButton->setPlatforms(platforms);
//	// 设置文本分享内容..
//	shareButton->setShareContent("抓糖果 一款逗比，伪重口，萌萌哒小游戏!") ;
//	// 设置要分享的图片, 图片支持本地图片和url图片, 但是url图片必须以http://或者https://开头..
//	shareButton->setShareImage("http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg") ;
//	// 设置按钮的位置..
//	shareButton->setPosition(Vec2(visibleSize.width*0.88,visibleSize.height*0.945));
//	// 然后开发者需要将该按钮添加到游戏场景中..
//	// ********************** 设置平台信息 ***************************
//	CCUMSocialSDK *sdk = CCUMSocialSDK::create("546c65a4fd98c52d32001daf");
//    //sdk->setQQAppIdAndAppKey("801459370", "cb45de05e8e82aa6f1e6a56275bf3db");
//	sdk->setWeiXinAppInfo("wxbf6741a198e9f71e",
//		"1ded1d9e84f14c4bfd74d6ab64bbeb9c");
//	sdk->setRenrenAppInfo("474206","ed166b5e5317441d928d0818a9fd4920","95c08423ac314d65b28b1610eb4fb253");
//	sdk->setFacebookAppId("你的facebook appid");
//	// 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面..
//	sdk->setTargetUrl("https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
//    
//	//     // 打开或者关闭log..
//	sdk->setLogEnable(true) ;
//	// **********************   END ***************************
//
//	sdk->setSsoAuthorization(SINA,"http://sns.whalecloud.com/sina2/callback");
//    sdk->setSsoAuthorization(RENREN, "http://sns.whalecloud.com");
//    
//    
//	sdk->setPlatformShareContent(SINA, "抓糖果 一款逗比，伪重口，萌萌哒小游戏!",
//		"http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "抓糖果","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
////    sdk->setPlatformShareContent(QQ, "放开那个小笼女 一款逗比，伪重口，萌萌哒小游戏!",
////                                 "http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
//    sdk->setPlatformShareContent(WEIXIN, "抓糖果 一款逗比，伪重口，萌萌哒小游戏!",
//                                 "http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
////    sdk->setPlatformShareContent(QZONE, "放开那个小笼女 一款逗比，伪重口，萌萌哒小游戏!",
////                                 "http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
////    sdk->setPlatformShareContent(TENCENT_WEIBO, "放开那个小笼女 一款逗比，伪重口，萌萌哒小游戏!",
////                                 "http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
//    sdk->setPlatformShareContent(WEIXIN_CIRCLE, "抓糖果 一款逗比，伪重口，萌萌哒小游戏!",
//                                 "http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu/id954161097?l=zh&ls=1&mt=8");
//
//	sdk->setPlatformShareContent(RENREN, "抓糖果 一款逗比，伪重口，萌萌哒小游戏!",
//		"http://ww1.sinaimg.cn/large/eb8847betw1enyrpq8rdtj203c03cwek.jpg", "放开那个小笼女","https://itunes.apple.com/us/app/fang-kai-na-ge-xiao-long-nu///////id954161097?l=zh&ls=1&mt=8");
//	
//
//	// create menu, it's an autorelease object
//	auto menu = Menu::create(shareButton, NULL);
//	menu->setPosition(Point::ZERO);
//	this->addChild(menu, 1000);
//
//
//#endif
        CCLOG("candy-Gateway::init-5");
	/**   中间主按钮  */
	Widget* start = getWidgetFromPanel(BUTTON_START);
	Widget* endless = getWidgetFromPanel(BUTTON_ENDLESS);
#ifdef LONGBAO 
	Node*endlesslock = endless->getChildByName("circle")->getChildByName("endlesslock");
#endif
#ifdef CANDY
	Node*endlesslock=endless->getChildByName("endless")->getChildByName("endlesslock");
#endif	

	if (data::User::getInstance()->getEndlesslock())
	{
		endlesslock->setVisible(true);
	}
	else
	{
		endlesslock->setVisible(false);
	}

	/*  文字按钮  */
	Widget* startText = getWidgetFromPanel(TEXT_START);
	Widget* endlessText = getWidgetFromPanel(TEXT_ENDLESS);
	Widget* saveText = getWidgetFromPanel(TEXT_SAVE);
	Widget* startonText = getWidgetFromPanel(TEXT_STARTON);
	Widget* goonText = getWidgetFromPanel(TEXT_GOON);
	Widget* guideText = getWidgetFromPanel(TEXT_GUIDE);
	Widget* black = getWidgetFromPanel(BLACK);
	//#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
	//    //添加广告。。
	//    this->menuBannerCallback();
	//    this->hiddenBannerCallback();
	//#endif
	UMGDBRow saveData = data::Game::getInstance()->getUserGame();
	int time = saveData["time"].asInt();
	int score = saveData["score"].asInt();
	int stage = saveData["stage"].asInt();
	if (time == 61 && score == 0 && stage == 1)
	{
		startonText->setVisible(true);
		goonText->setVisible(false);
	}
	else
	{
		startonText->setVisible(false);
		goonText->setVisible(true);
	}
	if (data::User::getInstance()->getFirst())
	{
		startonText->setVisible(false);
		goonText->setVisible(false);
		guideText->setVisible(true);
	}
	startText->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::startBtnClick, this)));
	endlessText->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::endlessBtnClick, this)));
	saveText->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::saveClick, this)));

	settingTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::settingBtnClick, this)));
    
    moreTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::moreButtonBtnClick, this)));

	start->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::startBtnClick, this)));
	helpTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::helpBtnClick, this)));
    infoTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::infoBtnClick, this)));
	endless->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::endlessBtnClick, this)));
    discountTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::endlessBtnClick, this)));

    libaoTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::libaoBtnClick, this)));

//    MenuItemSprite *item = MenuItemSprite::create(Sprite::create("pic/wujin_lock.png"), Sprite::create("pic/wujin_lock.png"),this, menu_selector(Gateway::testMenuclick));
//    item->setTag(100);
//    item->setPosition(Vec2(300, 300));
//    Menu *testMenu = Menu::create(item, NULL);
//    testMenu->setPosition(Vec2(0, 0));
//    this->addChild(testMenu,100);
	//下面两个UI..
	__goldUI = GoldUI::create();
	addChild(__goldUI, 2, "goldUI");
	// 	__itemUI = ItemUI::create(ItemUI::GAMEUI);
	// 	addChild(__itemUI, 2, "itemUI");
	addChild(UmGameUI::create(), 2, "umgameUI");

	//为金币赋初始值..
	std::string goldstr =  Value(data::User::getInstance()->getGold()).asString();
	TextAtlas  *gold = dynamic_cast<TextAtlas*>(__goldUI->_num);
	gold->setString(goldstr);

	//为道具赋初始值..
	// 	int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	// 	int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	// 	int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
	// 
	// 	if (magicnum >= 999) magicnum = 999;
	// 	if (shocknum >= 999) shocknum = 999;
	// 	if (bombnum >= 999) bombnum = 999;
	// 
	// 	std::string magicstr = std::to_string(magicnum);
	// 	std::string shockstr = std::to_string(shocknum);
	// 	std::string bombstr = std::to_string(bombnum);
	// 	TextAtlas  *magic = dynamic_cast<TextAtlas*>(__itemUI->_magic);
	// 	TextAtlas  *bomb = dynamic_cast<TextAtlas*>(__itemUI->_bomb);
	// 	TextAtlas  *shock = dynamic_cast<TextAtlas*>(__itemUI->_shock);
	// 	
	// 	magic->setString(magicstr);
	// 	bomb->setString(bombstr);
	// 	shock->setString(shockstr);
	// 	
	// 	Widget*bombmenu = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMBOMB);
	// 	bombmenu->setEnabled(false);
	// 	Widget*shockmenu = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITESHOCK);
	// 	shockmenu->setEnabled(false);
	// 	Widget*magicmenu = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMMAGIC);
	// 	magicmenu->setEnabled(false);

	auto _goldlistener = [=](EventCustom* e){
		int score = *(int*)e->getUserData();
		String* ns = String::createWithFormat("%d", score);
		const char* s = ns->getCString();
		TextAtlas  *la = dynamic_cast<TextAtlas*>(__goldUI->_num);
		la->setString(s);
	};
	_eventDispatcher->addCustomEventListener(data::User::GOLD_CHANGE, _goldlistener);

	// 	监听无尽模式是否购买成功，成功后去掉锁。。
	auto endlesslocks = [=](EventCustom*e)
	{
		endlesslock->setVisible(false);
        UserDefault::getInstance()-> setBoolForKey(DISCOUNTENDLESS_ISOVER.c_str(),true);
        Widget* discount = getWidgetFromPanel(IMAGE_41);
        if (discount) {
            discount->setVisible(false);
            this->unschedule(schedule_selector(Gateway::updateTime));
        }
        Node* endlessText = Main::seekNodeByName(_panel, "text_endless");
        endlessText->setVisible(true);
        
	};
	_eventDispatcher->addCustomEventListener(popup::EndlessUnlock::ENDLESSBUYSCUUESS, endlesslocks);






	// 	auto _itemlistener = [=](EventCustom* e){
	// 		
	// 		data::UserItemInfo userItem = *(data::UserItemInfo*)e->getUserData();
	// 		std::stringstream str;
	// 		str << userItem.num;
	// 		Node* block;
	// 		
	// 		int magicnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_RAGE_ID);
	// 		int shocknum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_SHOCK_ID);
	// 		int bombnum = data::Item::getInstance()->getUserItemNumByItemID(data::Item::ITEM_BOMB_ID);
	// 
	// 		
	// 		int magiclength = magicnum / 10;
	// 		int shocklength = shocknum / 10;
	// 		int bomblength= bombnum / 10;
	// 		__itemUI->setGray();
	// 		__itemUI->setLength(shocklength, __itemUI->ITESHOCK);
	// 		__itemUI->setLength(bomblength, __itemUI->ITEMBOMB);
	// 		__itemUI->setLength(magiclength, __itemUI->ITEMMAGIC);
	// 		__itemUI->setBgSize();
	// 	
	// 		switch (userItem.id)
	// 		{
	// 		case data::Item::ITEM_SHOCK_ID:
	// 			block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITESHOCK)->getChildByName("shocknum");
	// 			
	// 			break;
	// 		case data::Item::ITEM_BOMB_ID:
	// 			block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMBOMB)->getChildByName("bombnum");
	// 			break;
	// 		case data::Item::ITEM_RAGE_ID:
	// 			block = cocos2d::ui::Helper::seekWidgetByName(__itemUI->_panel, __itemUI->ITEMMAGIC)->getChildByName("magicnum");
	// 			break;
	// 		default:
	// 			break;
	// 		}
	// 		TextAtlas  *la = dynamic_cast<TextAtlas*>(block);
	// 		int itemnum = atoi(str.str().c_str());
	// 		if (itemnum>=999)
	// 		{
	// 			itemnum = 999;
	// 		}
	// 		la->setString(std::to_string(itemnum));	
	// 
	// 		str.clear();
	// 	};
	// 	_eventDispatcher->addCustomEventListener(data::Item::ITEM_CHANGE, _itemlistener);

	//设置监听..
	_goldUIListener = EventListenerCustom::create(GoldUI::MAINGOLDUI, [=](EventCustom* e){
		//往弹窗层里加弹窗..
		PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
		popup->addTopPop(GoldShop::create());
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_goldUIListener, 1);

	// 	_itemUIListener = EventListenerCustom::create(ItemUI::MAINITEMUI, [=](EventCustom* e){
	// 		//往弹窗层里加弹窗..
	// 		PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
	// 		popup->addTopPop(ItemShop::create());
	// 	});
	// 	_eventDispatcher->addEventListenerWithFixedPriority(_itemUIListener, 1);

	setting->setPosition(Vec2(-(visibleSize.width*0.5 - 1104) + 26 + 45, visibleSize.height - 26 - 45) + Vec2(0, 180));
	setting->setOpacity(0);
	help->setPosition(Vec2(2208 + visibleSize.width*0.5 - 1104 - 26 - 45, visibleSize.height - 26 - 45) + Vec2(0, 180));
	help->setOpacity(0);
    libaoButton->setPosition(libaoButton->getPosition() + Vec2(0, 180));
    libaoButton->setOpacity(0);

    moreButton->setPosition(moreButton->getPosition() + Vec2(0, 180));
    moreButton->setOpacity(0);
    infoButton->setPosition(infoButton->getPosition() + Vec2(0, 180));
    infoButton->setOpacity(0);

	//进入动画..
	Widget* umgame = (Widget*)getChildByName("umgameUI");
	//Widget* itemui = (Widget*)getChildByName("itemUI");
	Widget* goldui = (Widget*)getChildByName("goldUI");
	umgame->setPosition(umgame->getPosition() + Vec2(0, -140));
	umgame->setOpacity(0);
	//itemui->setPosition(itemui->getPosition() + Vec2(0, -140));
	//itemui->setOpacity(0);
	goldui->setPosition(goldui->getPosition() + Vec2(0, -140));
	goldui->setOpacity(0);
	ActionTimeline *action = CSLoader::createTimeline(PANEL_NAME.c_str());
	_panel->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 ..
	//播放动画： ..
	action->gotoFrameAndPlay(0, false);
	action->setFrameEventCallFunc([=](Frame* frame){
		EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
		if (!evnt)
			return;

		std::string str = evnt->getEvent();
		if (str == "end")
		{
			if (data::User::getInstance()->getFirst())
			{
				guideText->runAction(FadeOut::create(0.5f));
				//startText->runAction(FadeOut::create(0.5f));
				Node* panel = CSLoader::createNode("csb/main/black.csb");
				Node* black = panel->getChildByName("black");
				panel->setPosition(midPoint);
				Widget* text = (Widget*)panel->getChildByName("black")->getChildByName("panel")->getChildByName("text");
				Widget* circle = (Widget*)panel->getChildByName("black")->getChildByName("panel")->getChildByName("circle");
				text->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::startBtnClick, this)));
				circle->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Gateway::startBtnClick, this)));
				addChild(panel, 100);
				black->runAction(FadeIn::create(0.5f));
			}

			float dt = 0.4f;
			Spawn* settingSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, -180)), NULL);
			Spawn* helpSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, -180)), NULL);
            Spawn* libaoSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, -180)), NULL);

            Spawn* moreSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, -180)), NULL);
            Spawn* infoSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, -180)), NULL);

			Spawn* umgameSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, 140)), NULL);
			//Spawn* itemuiSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, 140)), NULL);
			Spawn* golduiSeq = Spawn::create(FadeIn::create(dt), MoveBy::create(dt, Vec2(0, 140)), NULL);
			setting->runAction(settingSeq);
			help->runAction(helpSeq);
            libaoButton->runAction(libaoSeq);
            moreButton->runAction(moreSeq);
            infoButton->runAction(infoSeq);
			umgame->runAction(umgameSeq);
			//itemui->runAction(itemuiSeq);
			goldui->runAction(golduiSeq);
		}
	});

	return true;
}

//void Gateway::testMenuclick(cocos2d::Ref *item)
//{
//    MenuItem *getItem = (MenuItem *)item;
//    int tag = getItem->getTag();
//    SpecialOfferLayer *specialOfferLayer = SpecialOfferLayer::createWithType(FirstChargePacksType);
//    this->addChild(specialOfferLayer,100);
//    CCLOG("testMenuclick");
//}


void Gateway::moveIn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*  获取元素  */
	/** 上面按钮*/
	Widget* setting = getWidgetFromPanel(BUTTON_SETTING);
	Widget* help = getWidgetFromPanel(BUTTON_HELP);
    Widget* libaoButton = getWidgetFromPanel(BUTTON_LIBAO);

    Widget* moreButton = getWidgetFromPanel(BUTTON_MOREGAME);
    Widget* infoButton = getWidgetFromPanel(BUTTON_INFO);
    
	/**  中间主按钮  */
	Widget* start = getWidgetFromPanel(BUTTON_START);
	Widget* endless = getWidgetFromPanel(BUTTON_ENDLESS);
	Node* startText = Main::seekNodeByName(_panel, "text_start");
	Node* endlessText = Main::seekNodeByName(_panel, "text_endless");
	Node* saveText = Main::seekNodeByName(_panel, "text_save");
    
    Widget* discount = getWidgetFromPanel(IMAGE_41);

	/**  下面按钮  */
	Widget* umgame = (Widget*)getChildByName("umgameUI");
	//Widget* itemui = (Widget*)getChildByName("itemUI");
	Widget* goldui = (Widget*)getChildByName("goldUI");

	/**   缓动事件   */
	Sequence* settingSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, -180))), NULL);
	Sequence* helpSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, -180))), NULL);
    Sequence* libaoSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, -180))), NULL);

    Sequence*  moreSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, -180))), NULL);
    Sequence* infoSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, -180))), NULL);

	Sequence* umgameSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, 140))), NULL);
	//Sequence* itemuiSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, 140))), NULL);
	Sequence* golduiSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, 140))), NULL);

	auto done = CallFuncN::create([=](Ref* ref)
	{Main* main = (Main*)this->getParent();
	main->switchToMain(); });
	Sequence* startSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 2), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), done, NULL);
	Sequence* endlessSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 1), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), NULL);
	Sequence* startTextSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 2), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), NULL);
	Sequence* endlessTextSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 1), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), NULL);
	Sequence* saveTextSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 2), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), NULL);

    Sequence* discounttSeq = Sequence::create(DelayTime::create(MOVEINDELAYTIME + DELAYTIME * 1), EaseOut::create(MoveBy::create(DELTATIME, Vec2(visibleSize.width, 0)), 2.5f), NULL);
    
	setting->runAction(settingSeq);
	help->runAction(helpSeq);
    libaoButton->runAction(libaoSeq);
    moreButton->runAction(moreSeq);
    infoButton->runAction(infoSeq);
	start->runAction(startSeq);
	endless->runAction(endlessSeq);
	startText->runAction(startTextSeq);
	endlessText->runAction(endlessTextSeq);
    discount->runAction(discounttSeq);

	saveText->runAction(saveTextSeq);
	umgame->runAction(umgameSeq);
	//itemui->runAction(itemuiSeq);
	goldui->runAction(golduiSeq);

}

void Gateway::moveOut(){

	Size visibleSize = Director::getInstance()->getVisibleSize();
	/*  获取元素  */
	/**  上面按钮  */
	Widget* setting = getWidgetFromPanel(BUTTON_SETTING);
	Widget* help = getWidgetFromPanel(BUTTON_HELP);
    Widget* libaoButton = getWidgetFromPanel(BUTTON_LIBAO);

    Widget* moreButton = getWidgetFromPanel(BUTTON_MOREGAME);
    Widget* infoButton = getWidgetFromPanel(BUTTON_INFO);
    
	/**  中间主按钮  */
	Widget* start = getWidgetFromPanel(BUTTON_START);
	Widget* endless = getWidgetFromPanel(BUTTON_ENDLESS);
	Node* startText = Main::seekNodeByName(_panel, "text_start");
	Node* endlessText = Main::seekNodeByName(_panel, "text_endless");
	Node* saveText = Main::seekNodeByName(_panel, "text_save");
    Widget* discount = getWidgetFromPanel(IMAGE_41);

	/**  下面按钮  */
	Widget* umgame = (Widget*)getChildByName("umgameUI");
	//Widget* itemui = (Widget*)getChildByName("itemUI");
	Widget* goldui = (Widget*)getChildByName("goldUI");


	/**   缓动事件   */
	Sequence* settingSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)), 2.5f), NULL);
	Sequence* helpSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)), 2.5f), NULL);
    Sequence* libaoSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)), 2.5f), NULL);

    Sequence* moreSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)), 2.5f), NULL);
    Sequence* infoSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)), 2.5f), NULL);

	Sequence* startSeq = Sequence::create(DelayTime::create(DELAYTIME * 1), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);
	Sequence* endlessSeq = Sequence::create(DelayTime::create(DELAYTIME * 2), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);
	Sequence* startTextSeq = Sequence::create(DelayTime::create(DELAYTIME * 1), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);
	Sequence* endlessTextSeq = Sequence::create(DelayTime::create(DELAYTIME * 2), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);
	Sequence* saveTextSeq = Sequence::create(DelayTime::create(DELAYTIME * 1), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);
    Sequence* discountTextSeq = Sequence::create(DelayTime::create(DELAYTIME * 2), EaseIn::create(MoveBy::create(DELTATIME, Vec2(-visibleSize.width, 0)), 2.5f), NULL);

	Sequence* umgameSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, -140)), 2.5f), NULL);
	//Sequence* itemuiSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, -140)),2.5f), NULL);
	Sequence* golduiSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, -140)), 2.5f), NULL);

	setting->runAction(settingSeq);
	help->runAction(helpSeq);
    libaoButton->runAction(libaoSeq);
    moreButton->runAction(moreSeq);
    infoButton->runAction(infoSeq);
	start->runAction(startSeq);
	endless->runAction(endlessSeq);
	startText->runAction(startTextSeq);
	endlessText->runAction(endlessTextSeq);
	saveText->runAction(saveTextSeq);
    discount->runAction(discountTextSeq);
	umgame->runAction(umgameSeq);
	//itemui->runAction(itemuiSeq);
	goldui->runAction(golduiSeq);
}

void Gateway::settingBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){

	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		Main* main = (Main*)this->getParent();
		main->clickSetting();
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}

void Gateway::moreButtonBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e)
{
    if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
        AndroidSDKHelper::sharedHelper()->openMoreGameLayer();
        cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
        
//        PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
//        popup->addTopPop(PaymentLayer::createWithType(kProductIndexDirectCoin1));

    }
    
}

void Gateway::startBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){

	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		_eventDispatcher->removeCustomEventListeners(data::User::GOLD_CHANGE);
		//_eventDispatcher->removeCustomEventListeners(data::Item::ITEM_CHANGE);		

		if (data::User::getInstance()->getFirst())
		{
			_guide = data::User::getInstance()->getGuide();
			int state;
			switch (_guide)
			{
			case Guide::STEP1:
				state = Guide::CSBSTEP1;
				break;
			case Guide::STEP2:
				state = Guide::CSBSTEP2;
				break;
			case Guide::STEP3:
				state = Guide::CSBSTEP3;
				break;
			case Guide::STEP4:
				state = Guide::CSBSTEP4;
				break;
			}
			Scene* scene = Guide::createScene(state);

			Director::getInstance()->replaceScene(scene);
		}
		else
		{
			Scene* scene = Game::createScene();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.3, (Scene*)scene));
		}
	}
}
void Gateway::endlessBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){

	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		//获取无尽模式是否是锁住的。。。
		if (data::User::getInstance()->getEndlesslock())
		{

			PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
			popup->addTopPop(EndlessUnlock::create());
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		}
		else
		{
			//增加音效..
			cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

			_eventDispatcher->removeCustomEventListeners(data::User::GOLD_CHANGE);
			//_eventDispatcher->removeCustomEventListeners(data::Item::ITEM_CHANGE);		

			Scene* scene = Game::createScene();
			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));

			NotificationCenter::getInstance()->postNotification(ENDLESSGAME, nullptr);
		}
	}
}
void Gateway::helpBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){

	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){

		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

		//	Scene* scene = NewbieTeach::createScene(NewbieTeach::TeachLevel::LETTER);
		//Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));

		Scene* scene = Guide::createScene(1);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	}
}

void Gateway::infoBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
    
    if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
        
        //增加音效..
        cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
        PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
        popup->addTopPop(Info::create());

    }
}



void Gateway::saveClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){

	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
		popup->addTopPop(LoadSave::create());
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}

void shareCallback(int platform, int stCode, std::string& errorMsg)
{
//#if (CC_TARGET_PLATFORM!=CC_PLATFORM_WIN32)
//
//
//	if (stCode == 100)
//	{
//		CCLOG("#### HelloWorld 开始分享");
//	}
//	else if (stCode == 200)
//	{
//		CCLOG("#### HelloWorld 分享成功");
//	}
//	else
//	{
//		CCLOG("#### HelloWorld 分享出错");
//	}
//
//	CCLOG("platform num is : %d.", platform);
//#endif
}
//#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
//void Gateway::menuBannerCallback(){
//    char mogoid []="61884ac510f4454fadd245f11a8ff025";
//    //  使用芒果广告位置
//    //  可以通过修改AdMoGoPointTypeDown_middle 变化 位置
//    AdsmogoBanner::sharedBanner()->createBanner(mogoid, AdsmogoBannerTypeNormalBanner, AdMoGoPointTypeTop_middle,false);
//}
//
//void Gateway::hiddenBannerCallback(){
//    
//    AdsmogoBanner::sharedBanner()->hidenBanner();
//}
//#endif



#pragma mark-----礼包版
void Gateway::showSpecialOffer()
{
    this->setTitleDisPlay(0);
    this->schedule(schedule_selector(Gateway::setTitleDisPlay), 1);
}

void Gateway::showDiscountWithEndless()
{
    bool isOver = UserDefault::getInstance()->getBoolForKey(DISCOUNTENDLESS_ISOVER.c_str());
    Node* endlessText = Main::seekNodeByName(_panel, "text_endless");

    if (isOver)
    {
        endlessText->setVisible(true);
        return;
    }
    endlessText->setVisible(false);

    Widget* discount = getWidgetFromPanel(IMAGE_41);
    discount->setVisible(true);

    std::string overTime = UserDefault::getInstance()->getStringForKey(OVER_TIMES.c_str());
    if (overTime.length() <= 0) {
        int nowTime = (int)time(0) + 3600 * 48;
        UserDefault::getInstance()->setStringForKey(OVER_TIMES.c_str(), Value(nowTime).asString());
        overTime = Value(nowTime).asString();
        CCLOG("overTime = %d",nowTime);
    }
    int isOverTime = Value(overTime.c_str()).asInt();
    bool Endlesslock = data::User::getInstance()->getEndlesslock();
    if (isOverTime <= ((int)time(0)) || !Endlesslock) {//时间到了 活动结束
    UserDefault::getInstance()-> setBoolForKey(DISCOUNTENDLESS_ISOVER.c_str(),true);
        discount->setVisible(false);
        endlessText->setVisible(true);
        return;
    }
    
    m_nUpTime = isOverTime - (int)time(0);
    
    this->setTimeWithStr(m_nUpTime);
    this->schedule(schedule_selector(Gateway::updateTime), 1);
    

//    auto Titlelistener = [=](EventCustom* e){
//        this->setTitleDisPlay(0);
//    };
//    _eventDispatcher->addCustomEventListener(data::User::BUY_FIRST_CHARGE, Titlelistener);
}

void Gateway::updateTime(float dt)
{
    std::string overTime = UserDefault::getInstance()->getStringForKey(OVER_TIMES.c_str());
    int isOverTime = Value(overTime.c_str()).asInt();

    m_nUpTime = isOverTime - (int)time(0);
    if (m_nUpTime<=0) {
        UserDefault::getInstance()-> setBoolForKey(DISCOUNTENDLESS_ISOVER.c_str(),true);
        Widget* discount = getWidgetFromPanel(IMAGE_41);
        discount->setVisible(false);
        this->unschedule(schedule_selector(Gateway::updateTime));
        Node* endlessText = Main::seekNodeByName(_panel, "text_endless");
        endlessText->setVisible(true);
    }
    this->setTimeWithStr(m_nUpTime);
}

void Gateway::setTimeWithStr(int number)
{
    Widget* discount = getWidgetFromPanel(IMAGE_41);

    Text* discountText = (Text*)cocos2d::ui::Helper::seekWidgetByName(discount, "Text_7");
    int hour=0;
    int minute=0;
    int second=0;
    hour = number/3600;
    minute = (number-(3600*hour))/60;
    second = (number-(3600*hour)-(60*minute));
    String* ns = String::createWithFormat("剩余时间：%.2d:%.2d:%.2d", hour,minute,second);

//    discountText->setVisible(false);
    discountText->setString(ns->getCString());
}

void Gateway::libaoBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
    
    if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
        Main* main = (Main*)this->getParent();
//        main->clickSetting();
        //增加音效..
        cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
        PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
        bool buy_first_charge = UserDefault::getInstance()->getBoolForKey("buy_first_charge");
        if (!buy_first_charge) {
            popup->addTopPop(SpecialOfferLayer::createWithType(FirstChargePacksType));
        }
        else{
            popup->addTopPop(SpecialOfferLayer::createWithType(SpecialOffersType));
        }
//        SpecialOfferLayer *specialOfferLayer = SpecialOfferLayer::createWithType(SpecialOffersType);
//        this->addChild(specialOfferLayer,100);

    }
}

void Gateway::setTitleDisPlay(float dt)
{
    
    Widget* libaoButton = getWidgetFromPanel(BUTTON_LIBAO);
    libaoButton->setVisible(true);

    Widget* Image_42 = (Widget*)Main::seekNodeByName(libaoButton, "Image_42");
    Text *Text_8 = (Text*)cocos2d::ui::Helper::seekWidgetByName(Image_42, "Text_8");
    bool buy_first_charge = UserDefault::getInstance()->getBoolForKey("buy_first_charge");
    std::string weekStr;

    if (!buy_first_charge) {
        weekStr = "首充礼包";
    }else{

        time_t now = time(0);
        tm *timeData = localtime(&now);
        
        int weekType = timeData->tm_wday;
        weekType = (((int)weekType)?weekType:7);
        
        int openWeek = UserDefault::getInstance()->getIntegerForKey("open_specialoffer");
        if (openWeek == weekType)
        {
            libaoButton->setVisible(false);
            return;
        }
        switch (weekType) {
            case 1:
                weekStr = "周一特惠礼包";
                break;
            case 2:
                weekStr = "周二特惠礼包";
                break;
            case 3:
                weekStr = "周三特惠礼包";
                break;
            case 4:
                weekStr = "周四特惠礼包";
                break;
            case 5:
                weekStr = "周五特惠礼包";
                break;
            case 6:
                weekStr = "周六特惠礼包";
                break;
            case 7:
                weekStr = "周日特惠礼包";
                break;
                
            default:
                break;
        }

    }
    Text_8->setString(weekStr);
    
}

void Gateway::showEndlessLayer()
{
        auto done = CallFuncN::create([=](Ref* ref){
            
            if (data::User::getInstance()->getEndlesslock())
            {
                
                PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
                popup->addTopPop(EndlessUnlock::create());
                //增加音效..
                cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
            }
        });
    this->runAction(Sequence::create(DelayTime::create(1),done, NULL));
}


