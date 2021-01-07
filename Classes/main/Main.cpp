/****************************************************************************
*	@       	       
*	@desc	主场景
*	@date	2014-12-12
*	@author	120101
*	@       	       
*	@file	main/Main.app
*	@modify	null
******************************************************************************/
#include "main/Main.h"
#if (CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "Cocos2dx/Common/CCUMSocialSDK.h"
#include "Cocos2dx/ShareButton/UMShareButton.h"
USING_NS_UM_SOCIAL;
#endif
USING_NS_CC;
using namespace popup;
using namespace ui;
using namespace cocostudio;
Scene* Main::createScene()
{
	auto scene = Scene::create();

	auto layer = Main::create();

	scene->addChild(layer);
	return scene;
}

bool Main::init()
{
    if (!Layer::init())
    {
        return false;
    }

	Size visibleSize = Director::getInstance()->getVisibleSize();
	_bg = Background::create();
	_bg->changeBgState(Background::MAIN);
	addChild(_bg, 0);
   

	/*  设置界面  */
	Setting* setting = Setting::create();
	setting->setPosition(-1 * visibleSize);
	addChild(setting, 2, "setting");

	/*  开始界面  */
	Gateway* gateway = Gateway::create();
	addChild(gateway, 1, "gateway");
//    if (m_bShowEndlessLayer) {
//        gateway->showEndlessLayer();
//    }
	//弹窗层..
	PopUp* popUp = PopUp::create();
	addChild(popUp, 3, "popup");


	//增加禁止点击遮罩..
	_touchLayer = Widget::create();
	_touchLayer->setColor(Color3B(255, 0, 0));
	_touchLayer->setContentSize(Size(visibleSize.width, visibleSize.height));
	_touchLayer->setPosition(Vec2(visibleSize.width*0.5, visibleSize.height*0.5));
	_touchLayer->setTouchEnabled(false);
	addChild(_touchLayer, 4, "touchLayer");

	_moveInListener = EventListenerCustom::create(Quit::MOVEIN, [=](EventCustom* e){
		openQuit = true;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveInListener, 1);

	_moveOutListener = EventListenerCustom::create(Quit::MOVEOUT, [=](EventCustom* e){
		openQuit = false;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveOutListener, 1);

	outKeyInit();

	return true;
}

void Main::showEndlessLayer()
{
    Gateway* gateway = (Gateway*)getChildByName("gateway");
    gateway->showEndlessLayer();
}

void Main::outKeyInit(){
	auto listener = EventListenerKeyboard::create();

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){

		if (keyCode == EventKeyboard::KeyCode::KEY_BACK){
			PopUp* popup = (PopUp*)getChildByName("popup");
			if (!popup->closeTopPop())
			{
				if (!switchingScene)
				{
					if (switchScene)
					{
						switchingScene = true;
						Setting* setting = (Setting*)getChildByName("setting");
						Gateway* gateway = (Gateway*)getChildByName("gateway");
						_touchLayer->setTouchEnabled(true);
						gateway->moveIn();
						setting->moveOut();
					}
					else
					{
						if (!openQuit)
						{
							addChild(Quit::create(), 10, "quit");
						}
						else
						{
							//退出游戏..
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							umeng::MobClickCpp::end();
#endif						
							Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
							exit(0);
#endif
						}
					}
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Main::switchToSetting()
{
	//取消禁止点击遮罩..
	_touchLayer->setTouchEnabled(false);
	switchScene = true;
	switchingScene = false;
}

void Main::switchToMain()
{
	//取消禁止点击遮罩..
	_touchLayer->setTouchEnabled(false);
	switchScene = false;
	switchingScene = false;
}

void Main::clickSetting()
{
	Setting* setting = (Setting*)getChildByName("setting");
	Gateway* gateway = (Gateway*)getChildByName("gateway");
	_touchLayer->setTouchEnabled(true);
	gateway->moveOut();
	setting->moveIn();
	switchingScene = true;
}

void Main::clickMain()
{
	if (!switchingScene)
	{
		Setting* setting = (Setting*)getChildByName("setting");
		Gateway* gateway = (Gateway*)getChildByName("gateway");
		_touchLayer->setTouchEnabled(true);
		setting->moveOut();
		gateway->moveIn();
		switchingScene = true;
	}
}

Main::~Main()
{
	_eventDispatcher->removeEventListener(_moveInListener);
	_eventDispatcher->removeEventListener(_moveOutListener);
}

Node* Main::seekNodeByName(Node* root, const std::string& name)
{
	if (!root)
	{
		return nullptr;
	}
	if (root->getName() == name)
	{
		return root;
	}
	const auto& arrayRootChildren = root->getChildren();
	for (auto& subWidget : arrayRootChildren)
	{
		Node* child = dynamic_cast<Node*>(subWidget);
		if (child)
		{
			Node* res = seekNodeByName(child, name);
			if (res != nullptr)
			{
				return res;
			}
		}
	}
	return nullptr;
}
