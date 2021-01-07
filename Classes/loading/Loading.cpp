/****************************************************************************
*	@       	       
*	@desc	读取界面
*	@date	2014-11-17
*	@author	120101
*	@       	       
*	@file	loading/Loading.h
*	@modify	null
******************************************************************************/

#include "Loading.h"

USING_NS_CC;
using namespace ui;
using namespace cocostudio::timeline;

Scene* Loading::createScene()
{
	auto scene = Scene::create();

	auto layer = Loading::create();

	scene->addChild(layer);

	return scene;
}

bool Loading::init()
{
	if (!Layer::init())
	{
		return false;
	}
    CCLOG("candy-Loading::init");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 midPoint = Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5);

	/*  场景背景图片  */
	Background* _bg = Background::create();
	_bg->changeBgState(Background::LOADING);
	addChild(_bg, 0);

#ifdef LONGBAO
	std::string str = "csb/longbao/ui/loading.csb";
#endif
#ifdef CANDY
	std::string str = "csb/main/loading.csb";
#endif	
	Node* loading = CSLoader::createNode(str);//传入Studio2.x的资源路径..
	loading->setPosition(midPoint);
	this->addChild(loading);
    loading->setVisible(true);
//    auto dones = CallFuncN::create([=](Ref* ref){
//        Scene* scene = Main::createScene();
//        scene->retain();
//        Director::getInstance()->replaceScene(scene);
//    });
//    this->runAction(Sequence::create(DelayTime::create(1.0),dones, NULL));
#ifdef LONGBAO
	//Node* bg1 = Main::seekNodeByName(loading, "map1");
	//Node* bg2 = Main::seekNodeByName(loading, "map2");
	//float scale = visibleSize.width / 2208;
	//bg1->setScaleY(scale);
	//bg2->setScaleY(scale);
	ImageView* bg = ImageView::create("map/map7.jpg.jpg");
	float scaleX = visibleSize.width / bg->getContentSize().width;
	float scaleY = visibleSize.height / bg->getContentSize().height;
	float scale = scaleX > scaleY ? scaleX : scaleY;
	bg->setPosition(midPoint);
	bg->setScale(scale);
	bg->setTouchEnabled(true);
	bg->setSwallowTouches(true);
	addChild(bg, 0);
	Node* zhua = Main::seekNodeByName(loading, "biaoti");
	zhua->setScale(1.5);
	zhua->setPosition(zhua->getPosition() + Vec2(0, 650));
	Sequence* zhuaSeq = Sequence::create(EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	zhua->runAction(zhuaSeq);
#endif
#ifdef CANDY
	Node* zhua = Main::seekNodeByName(loading, "zhua");
	zhua->setPosition(zhua->getPosition() + Vec2(0, 650));
	Sequence* zhuaSeq = Sequence::create(EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	zhua->runAction(zhuaSeq);

	Node* tang = Main::seekNodeByName(loading, "tang");
	tang->setPosition(tang->getPosition() + Vec2(0, 650));
	Sequence* yuSeq = Sequence::create(DelayTime::create(DELAYTIME), EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	tang->runAction(yuSeq);

	Node* guo = Main::seekNodeByName(loading, "guo");
	guo->setPosition(guo->getPosition() + Vec2(0, 650));
	Sequence* wanSeq = Sequence::create(DelayTime::create(DELAYTIME * 2), EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	guo->runAction(wanSeq);

	//Node* meng1 = Main::seekNodeByName(loading, "meng1");
	//meng1->setPosition(meng1->getPosition() + Vec2(0, 650));
	//Sequence* meng1Seq = Sequence::create(EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	//meng1->runAction(meng1Seq);

	//Node* meng2 = Main::seekNodeByName(loading, "meng2");
	//meng2->setPosition(meng2->getPosition() + Vec2(0, 650));
	//Sequence* meng2Seq = Sequence::create(DelayTime::create(DELAYTIME),EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	//meng2->runAction(meng2Seq);

	//Node* tang = Main::seekNodeByName(loading, "tang");
	//tang->setPosition(tang->getPosition() + Vec2(0, 650));
	//Sequence* yuSeq = Sequence::create(DelayTime::create(DELAYTIME * 2), EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	//tang->runAction(yuSeq);

	//Node* guo = Main::seekNodeByName(loading, "guo");
 //   guo->setPosition(guo->getPosition() + Vec2(0, 650));
	//Sequence* wanSeq = Sequence::create(DelayTime::create(DELAYTIME * 3), EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
 //   guo->runAction(wanSeq);

	//Node* wu = Main::seekNodeByName(loading, "wu");
	//wu->setPosition(wu->getPosition() + Vec2(0, 650));
	//Sequence* wuSeq = Sequence::create(DelayTime::create(DELAYTIME * 4), EaseElasticOut::create(MoveBy::create(1, Vec2(0, -650))), NULL);
	//wu->runAction(wuSeq);
#ifdef LANGUAGE_EN
    guo->setVisible(false);
#endif
#endif
	Node* black = Main::seekNodeByName(loading, "black");
	black->setOpacity(0);
	Sequence* blackUnderSeq = Sequence::create(DelayTime::create(DELAYTIME), FadeTo::create(0.4f,128), NULL);
	black->runAction(blackUnderSeq);

	Node* tanhao = Main::seekNodeByName(loading, "tanhao");
	tanhao->setOpacity(0);
	Sequence* exclamationSeq = Sequence::create(DelayTime::create(DELAYTIME * 3), FadeTo::create(0.4f, 128), NULL);
	tanhao->runAction(exclamationSeq);

	Node* dot2 = Main::seekNodeByName(loading, "dot2");
	dot2->setOpacity(0);
	Sequence* inOutSeq = Sequence::create(FadeIn::create(0.5f), FadeOut::create(0.5f), NULL);	
	dot2->runAction(RepeatForever::create(inOutSeq));

	auto done = CallFuncN::create([=](Ref* ref)
	{
		Loader::getInstance()->load(Loader::UI);
	});
	this->runAction(Sequence::create(DelayTime::create(DELAYTIME * 5), done, NULL));

	LoadingBar* whiteWave = (LoadingBar*)Main::seekNodeByName(loading, "whitebar");
	Node* dot = Main::seekNodeByName(loading, "dot");
	
	_eventDispatcher->addCustomEventListener(Loader::PROGRESS, [=](EventCustom* e){
		Text* text = (Text*)Main::seekNodeByName(loading, "num");
		ProgressObj obj = *(ProgressObj*)e->getUserData();
		int per = (float)obj.loaded / (float)obj.total *100;
		std::stringstream str;
		str << per << "%";
		text->setString(str.str().c_str());
		whiteWave->setPercent(per);
		float pointper = per;
		if (per<4)
			pointper = 4;
		else if (per>96)
			pointper = 96;
		float x = (pointper - 4)*9.12;
		float y = 28 * sinf(M_PI / 168 * x);
		dot->setPosition(Vec2(-420, 0) + Vec2(x, y) + whiteWave->getPosition());
	});
	_eventDispatcher->addCustomEventListener(Loader::COMPLETE, [=](EventCustom* e){
		//zhua->runAction(FadeOut::create(0.5));
		_eventDispatcher->removeCustomEventListeners(Loader::PROGRESS);
		_eventDispatcher->removeCustomEventListeners(Loader::COMPLETE);			
		//加载动画： ..
		ActionTimeline *action = CSLoader::createTimeline(str);
		loading->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 ..
		//播放动画： ..
		action->gotoFrameAndPlay(0, false);
//		scene->retain();
		action->setFrameEventCallFunc([=](Frame* frame){
			EventFrame* evnt = dynamic_cast<EventFrame*>(frame);
			if (!evnt)
				return;

			std::string str = evnt->getEvent();
			if (str == "end")
			{
                CCLOG("candy-Loading::end");
                Scene* scene = Main::createScene();

				Director::getInstance()->replaceScene(scene);
			}
		});		
	});
	return true;
}