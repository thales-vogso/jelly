/****************************************************************************
*	@       	       
*	@desc	帮助
*	@date	2014-12-9
*	@author	120101
*	@       	       
*	@file	main/Guide.app
*	@modify	null
******************************************************************************/
#include "Guide.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio;
using namespace cocostudio::timeline;
using namespace popup;
Scene* Guide::createScene(int step)
{
    auto scene = Scene::create();

	auto layer = Guide::create();

	layer->_step = step;

	scene->addChild(layer);

    return scene;
}

void Guide::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
	
	switchStep(_step);
}

void Guide::playFirstFrame()
{
	_skip->setVisible(true);
	switch (_step)
	{
	case 0:
		__action->gotoFrameAndPlay(0, 30, false);
		break;
	case 1:		
		__action->gotoFrameAndPlay(0, 30, false);		
		break;
	case 2:
		__action->gotoFrameAndPlay(0, 30, false);
		break;
	case 3:
		__action->gotoFrameAndPlay(0, 120, false);
		break;
	case 4:
		if (data::User::getInstance()->getFirst())
			data::User::getInstance()->setGuide(Guide::STEP2);
		__action->gotoFrameAndPlay(0, 30, false);
		break;
	case 5:
		if (data::User::getInstance()->getFirst())
			data::User::getInstance()->setGuide(Guide::STEP3);
		_skip->setVisible(false);
		__action->gotoFrameAndPlay(0, 30, false);
		break;
	//case 6:
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 7:
	//	if (data::User::getInstance()->getFirst())
	//		data::User::getInstance()->setGuide(Guide::STEP3);
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 8:
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	__labelAction->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 9:
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 10:
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	__labelAction->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 11:
	//	if (data::User::getInstance()->getFirst())
	//		data::User::getInstance()->setGuide(Guide::STEP4);
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 12:
	//	_skip->setVisible(false);
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	//case 13:
	//	__action->gotoFrameAndPlay(0, 30, false);
	//	break;
	}
}

bool Guide::init()
{	
#ifdef CANDY
	_preStr = "csb/guide/";
#endif
#ifdef LONGBAO
	_preStr = "csb/longbao/guide/";
#endif
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	cache::Music::getInstance()->playBGM(cache::Music::BGMName::GATEWAY);
	//弹窗层..
	PopUp* popUp = PopUp::create();
	addChild(popUp, 100, "popup");

	std::string str = _preStr+"bg.csb";

	__bgNode = CSLoader::createNode(str);
	__bgNode->setPosition(midPoint);
	addChild(__bgNode,1);
#ifdef CANDY
	/**  场景背景图片  */
	ImageView* bg = ImageView::create("map/map5_blur.jpg");
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setPosition(midPoint);
	bg->setScale(scale);
	bg->setTouchEnabled(true);
	bg->setSwallowTouches(true);
	bg->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Guide::next, this)));
	addChild(bg, 0);
#endif

#ifdef LONGBAO
	/**  场景背景图片  */
	ImageView* bg = ImageView::create("map/map7.jpg");
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setPosition(midPoint);
	bg->setScale(scale);
	bg->setTouchEnabled(true);
	bg->setSwallowTouches(true);
	bg->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Guide::next, this)));
	addChild(bg, 0);
#endif
	/**  按钮  */
	_skip = (Widget*)Main::seekNodeByName(__bgNode, "skip");
	_skip->setPosition(Vec2(visibleSize.width * 0.5 - 26 - 45, visibleSize.height * 0.5 - 26 - 45));
	_skip->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Guide::skip, this)));
	Node* next = Main::seekNodeByName(__bgNode, "next");
	next->setPosition(Vec2(0, _skip->getPosition().y));
	float flash = 0.5f;
	Sequence* seq = Sequence::create(FadeOut::create(flash), FadeIn::create(flash), NULL);
	next->runAction(RepeatForever::create(seq));

	outKeyInit();
	return true;
}
void Guide::outKeyInit(){
	_moveInListener = EventListenerCustom::create(Quit::MOVEIN, [=](EventCustom* e){
		openQuit = true;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveInListener, 1);

	_moveOutListener = EventListenerCustom::create(Quit::MOVEOUT, [=](EventCustom* e){
		openQuit = false;
	});
	_eventDispatcher->addEventListenerWithFixedPriority(_moveOutListener, 1);

	auto listener = EventListenerKeyboard::create();

	listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){

		if (keyCode == EventKeyboard::KeyCode::KEY_BACK){
			PopUp* popup = (PopUp*)getChildByName("popup");
			if (!popup->closeTopPop())
			{
				if (!openQuit)
				{
					addChild(Quit::create(), 10, "quit");
				}
				else
				{
					//退出游戏..
					Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
					exit(0);
#endif
				}
			}
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Guide::next(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		_frame++;
		switch (_step)
		{
		case 0:
			switch (_frame)
			{
			case 2:
				__action->gotoFrameAndPlay(30, 60, false);
				break;
			}
			break;
		case 1:
			switch (_frame)
			{
			case 2:
				__action->gotoFrameAndPlay(30, 60, false);
				break;
			}
			break;
		case 2:
			switch (_frame)
			{
			case 2:				
				auto done = CallFuncN::create([=](Ref* ref){
					Scene* scene = NewbieTeach::createScene(NewbieTeach::LINE);
					Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				});				
				__rootNode->runAction(Sequence::create(FadeOut::create(0.4f), done, NULL));
				__rootNode->getChildByName("line")->runAction(FadeTo::create(0.1, 50));
				break;
			}
			break;
		case 3:
			switch (_frame)
			{
			case 2:
				__action->gotoFrameAndPlay(120, 150, false);	
				break;
			}
			break;
		case 4:
			switch (_frame)
			{
			case 2:
				auto done = CallFuncN::create([=](Ref* ref){
					Scene* scene = NewbieTeach::createScene(NewbieTeach::ROUND);
					Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				});
				__rootNode->runAction(Sequence::create(FadeOut::create(0.4f), done, NULL));
				__rootNode->getChildByName("line")->runAction(FadeTo::create(0.1, 50));
				break;
			}
			break;
		case 5:
			switch (_frame)
			{
			case 2:
				__action->gotoFrameAndPlay(30, 120, false);
				break;
			case 3:
				__action->gotoFrameAndPlay(120, 210, false);
				break;
			case 4:
				__action->gotoFrameAndPlay(210, 300, false);
				break;
			case 5:
				__action->gotoFrameAndPlay(300, 360, false);
				break;
			case 6:
				__action->gotoFrameAndPlay(360, 390, false);
				break;
			}
			break;
		//case 6:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 90, false);
		//		break;
		//	case 3:
		//		__action->gotoFrameAndPlay(90, 300, false);
		//		break;
		//	case 4:
		//		__action->gotoFrameAndPlay(300, 330, false);
		//		break;
		//	}
		//	break;
		//case 7:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 60, false);
		//		break;
		//	//case 3:
		//	//	__action->gotoFrameAndPlay(90, 150, false);
		//	//	break;
		//	//case 4:
		//	//	__action->gotoFrameAndPlay(150, 180, false);
		//	//	break;
		//	}
		//	break;
		//case 8:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__labelAction->gotoFrameAndPlay(30, 90, false);
		//		break;
		//	case 3:
		//		auto done = CallFuncN::create([=](Ref* ref){
		//			Scene* scene = NewbieTeach::createScene(NewbieTeach::SHING);
		//			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
		//		});
		//		__labelNode->runAction(Sequence::create(FadeOut::create(0.4f), done, NULL));
		//		__rootNode->runAction(FadeOut::create(0.4f));
		//		__rootNode->getChildByName("line")->runAction(FadeTo::create(0.1, 50));
		//		//__action->gotoFrameAndPlay(175, 205, false);
		//		//__labelAction->gotoFrameAndPlay(90, 120, false);
		//		break;
		//	}
		//	break;
		//case 9:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 60, false);
		//		break;
		//	}
		//	break;
		//case 10:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__labelAction->gotoFrameAndPlay(30, 90, false);
		//		break;
		//	case 3:
		//		auto done = CallFuncN::create([=](Ref* ref){
		//			Scene* scene = NewbieTeach::createScene(NewbieTeach::LETTER);
		//			Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
		//		});
		//		__labelNode->runAction(Sequence::create(FadeOut::create(0.4f), done, NULL));
		//		__rootNode->runAction(FadeOut::create(0.4f));
		//		__rootNode->getChildByName("line")->runAction(FadeTo::create(0.1, 50));
		//		//__action->gotoFrameAndPlay(175, 205, false);
		//		//__labelAction->gotoFrameAndPlay(90, 120, false);
		//		break;
		//	}
		//	break;
		//case 11:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 150, false);
		//		break;
		//	case 3:
		//		__action->gotoFrameAndPlay(150, 210, false);
		//		break;
		//	case 4:
		//		__action->gotoFrameAndPlay(210, 270, false);
		//		break;
		//	case 5:
		//		__action->gotoFrameAndPlay(270, 330, false);
		//		break;
		//	case 6:
		//		__action->gotoFrameAndPlay(330, 390, false);
		//		break;
		//	}
		//	break;
		//case 12:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 120, false);
		//		break;
		//	case 3:
		//		__action->gotoFrameAndPlay(120, 210, false);
		//		break;
		//	case 4:
		//		__action->gotoFrameAndPlay(210, 300, false);
		//		break;
		//	case 5:
		//		__action->gotoFrameAndPlay(300, 330, false);
		//		break;
		//	}
		//	break;
		//case 13:
		//	switch (_frame)
		//	{
		//	case 2:
		//		__action->gotoFrameAndPlay(30, 90, false);
		//		break;
		//	case 3:
		//		__action->gotoFrameAndPlay(90, 270, false);
		//		break;
		//	case 4:
		//		__action->gotoFrameAndPlay(270, 300, false);
		//		break;
		//	case 5:
		//		__action->gotoFrameAndPlay(300, 330, false);
		//		break;
		//	}
		//	break;
		}
	}
}

void Guide::skip(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED)
	{
		//增加音效..
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
		PopUp* popup = (PopUp*)getChildByName("popup");
        //添加暂停界面..
        Skip *skip = Skip::create();
        skip->m_bNotPushToColse = true;
        popup->addTopPop(skip);
	}
}

void Guide::nextStep()
{
	_step++;
	_frame = 1;
	switchStep(_step);
}

void Guide::switchStep(int step){

	if (__rootNode)
		__rootNode->removeFromParentAndCleanup(true);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	std::string str;

	switch (step)
	{
	//case 0:
	//	str = _preStr + "golevel.csb";
	//	break;
	case 1:
		str = _preStr + "step1.csb";
		break;
	case 2:
		str = _preStr + "step2loop.csb";
		break;
	case 3:
		str = _preStr + "step3.csb";
		break;
	case 4:
		str = _preStr + "step4loop.csb";
		break;
	case 5:
		str = _preStr + "step5.csb";
		break;
	//case 7:
	//	str = _preStr + "step6-1pre.csb";
	//	break;
	//case 8:
	//	str = _preStr + "step6-2loop.csb";
	//	break;
	//case 9:
	//	str = _preStr + "step7-1pre.csb";
	//	break;
	//case 10:
	//	str = _preStr + "step7-2loop.csb";
	//	break;
	//case 11:
	//	str = _preStr + "step8.csb";
	//	break;
	//case 12:
	//	str = _preStr + "step10.csb";
	//	break;
	//case 13:
	//	str = _preStr + "step9.csb";
	//	break;
	}

	__rootNode = CSLoader::createNode(str);
	__rootNode->setPosition(midPoint);
	addChild(__rootNode,1);

	//加载动画： ..
	__action = CSLoader::createTimeline(str);	
	__rootNode->runAction(__action);
	__action->setTimeSpeed(0.8);

	__action->setFrameEventCallFunc([=](Frame* frame){
		EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
		if (!evnt)
			return;

		std::string str = evnt->getEvent();
		
		if (str != "")
		{
			if (str == "end")
			{
				if (_step == 3)
				{
					Scene* scene = TeachGame::createScene(TeachEntity::LEVEL1);
					Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				}
				else if (_step == 4)
				{
					Scene* scene = TeachGame::createScene(TeachEntity::LEVEL2);
					Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				}
				else if (_step == 5)
				{
#ifdef GIFT_POPUE_VETSION
                    bool isOver = UserDefault::getInstance()->getBoolForKey("Discount_WithEndless_IsOver");
                    
                    data::User::getInstance()->setGuide(Guide::FINISH);
                    data::User::getInstance()->setFirst(false);
                    
                    if (isOver) {
                        Scene* scene = Game::createScene();
                        Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
                    }
                    else{
                        //设置监听
                        _listener = EventListenerCustom::create("closeEndless", [=](EventCustom* e){
                            Scene* scene = Game::createScene();
                            Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
                        });
                        _eventDispatcher->addEventListenerWithFixedPriority(_listener, 1);
                        
                        EndlessUnlock *endless = EndlessUnlock::create();
                        endless->m_bNotPushToColse = true;
                        this->addChild(endless, 10);
                        
                    }
#else
                    data::User::getInstance()->setGuide(Guide::FINISH);
                    data::User::getInstance()->setFirst(false);
                    Scene* scene = Game::createScene();
                    Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
#endif

                    
//                    PopUp* popup = (PopUp*)getParent()->getChildByName("popup");
//                    popup->addTopPop(EndlessUnlock::create());
                    
				}
				else
					nextStep();
				//else if (_step == 13)
				//{						
				//	if (data::User::getInstance()->getFirst())
				//	{
				//		data::User::getInstance()->setGuide(Guide::FINISH);
				//		data::User::getInstance()->setFirst(false);
				//		Scene* scene = Game::createScene();
				//		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				//	}
				//	else
				//	{
				//		Scene* scene = Main::createScene();
				//		Director::getInstance()->replaceScene(scene);
				//	}
				//}
				//else if (_step == 0)
				//{
				//	Scene* scene = TeachGame::createScene(TeachEntity::LEVEL3);
				//	Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
				//}
			}
			else if (str == "break")
			{
				if (_step == 2)
					__action->gotoFrameAndPlay(30, 190, true);
				else if (_step == 4)
					__action->gotoFrameAndPlay(30, 175, true);
				//else if (_step == 8)
				//	__action->gotoFrameAndPlay(30, 175, true);
				//else if (_step == 10)
				//	__action->gotoFrameAndPlay(30, 175, true);
			}
		}
	});
	loadLabelNode(step);
	playFirstFrame();
}

void Guide::loadLabelNode(int step){

	//if (__labelNode)
	//	__labelNode->removeFromParentAndCleanup(true);

	//Size visibleSize = Director::getInstance()->getVisibleSize();
	//Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	//std::string str = "";
	//switch (step)
	//{
	//case 2:
	//	str = _preStr + "step2label.csb";
	//	break;
	//case 5:
	//	str = _preStr + "step4label.csb";
	//	break;
	//case 8:
	//	str = _preStr + "step6label.csb";
	//	break;
	//case 10:
	//	str = _preStr + "step7label.csb";
	//	break;
	//}

	//if (str == "")
	//	return;

	//__labelNode = CSLoader::createNode(str);
	//__labelNode->setPosition(midPoint);
	//addChild(__labelNode, 2);

	////加载动画： ..
	//__labelAction = CSLoader::createTimeline(str);
	//__labelNode->runAction(__labelAction);
	//__labelAction->setTimeSpeed(0.8);
	//__labelAction->setFrameEventCallFunc([=](Frame* frame){
	//	EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
	//	if (!evnt)
	//		return;

	//	std::string str = evnt->getEvent();

	//	if (str != "")
	//	{
	//		if (str == "end")
	//		{
	//			if (_step == 2)
	//			{
	//				Scene* scene = NewbieTeach::createScene(NewbieTeach::LINE);
	//				Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	//			}

	//			else if (_step == 5)
	//			{
	//				Scene* scene = NewbieTeach::createScene(NewbieTeach::ROUND);
	//				Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	//			}
	//			else if (_step == 8)
	//			{
	//				Scene* scene = NewbieTeach::createScene(NewbieTeach::SHING);
	//				Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	//			}
	//			else if (_step == 10)
	//			{
	//				Scene* scene = NewbieTeach::createScene(NewbieTeach::LETTER);
	//				Director::getInstance()->replaceScene(TransitionCrossFade::create(0.4, (Scene*)scene));
	//			}
	//		}
	//	}
	//});
}