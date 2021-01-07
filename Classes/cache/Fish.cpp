/****************************************************************************
*	@       	       
*	@desc	缓存-鱼
*	@date	2014-10-23
*	@author	110101
*	@       	       
*	@file	popstar/Classes/cache/Fish.cpp
*	@modify	null
******************************************************************************/

#include "Fish.h"

USING_NS_CC;
using namespace cocostudio;
using namespace cocostudio::timeline;

namespace cache{
	Fish* Fish::_instance = nullptr;
	const std::string Fish::prefix = "fish";
	Fish::Fish(){
		//async();
	}
	Fish::~Fish(){
	}
	Fish* Fish::getInstance(){
		if (!_instance){
			_instance = new Fish();
		}
		return _instance;
	}
	void Fish::async(){
		//_loaded = 0;
		//int* id = 0;
		//Loader::getInstance()->start(id);
		//for (int i = 0; i < fishCount; i++){
		//	std::stringstream str;
		//	str << prefix << "/" << this->getFishNameStringByEnum(i) << ".ExportJson";
		//	cocostudio::ArmatureDataManager::getInstance()->addArmatureFileInfoAsync(str.str().c_str(), this, schedule_selector(Fish::jsonAsyncCallback));
		//}
		// 		TextureCache::getInstance()->addImageAsync("pic.png", [=](Texture2D*tex){
		// 
		// 			auto ui_texture = (Texture2D*)tex;
		// 			SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic.plist", ui_texture);
		// 		});
	}
	void Fish::jsonAsyncCallback(float dt){
		ProgressObj obj;
		obj.loaded = _loaded;
		obj.total = cache::Fish::fishCount;
		if (obj.loaded >= obj.total - 1){
			Loader::getInstance()->complete(&obj);
		}
		else{
			_loaded++;
			Loader::getInstance()->progress(&obj);
		}
	}
	Node* Fish::getDiscoNormalFish(){
#ifdef CANDY
		std::string str = "csb/candy/candy_disco_normal.csb";

		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0);
#endif
#ifdef LONGBAO
		std::string str = "csb/longbao/disco.csb";
		Node*rootNode = CSLoader::createNode(str);
		ActionTimeline*action = CSLoader::createTimeline(str);
		rootNode->runAction(action);
		action->gotoFrameAndPlay(0, 0, true);		
#endif
		return rootNode;
	}
	Node* Fish::getDiscoPressFish(){
#ifdef CANDY
		std::string str = "csb/candy/candy_disco_cap.csb";
		  
		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0);
#endif
#ifdef LONGBAO
		std::string str = "csb/longbao/disco.csb";

		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0);
#endif
		return rootNode;
	}
	Node* Fish::getRageFish(){
#ifdef LONGBAO
		std::string str = "csb/longbao/rage.csb";
		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		//根据糖果类型选表情图片
		std::string lookStr;
		int looknum = rand() % 5;
		switch (looknum)
		{
		case Look::Look1:
			lookStr = _lookPreStr + "candy_bq02.png";
			break;
		case Look::Look2:
			lookStr = _lookPreStr + "candy_bq03.png";
			break;
		case Look::Look3:
			lookStr = _lookPreStr + "candy_bq04.png";
			break;
		case Look::Look4:
			lookStr = _lookPreStr + "candy_bq05.png";
			break;
		case Look::Look5:
			lookStr = _lookPreStr + "candy_bq06.png";
			break;
		}
		bq->setTexture(lookStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0, 0, false);
		return rootNode;
#endif

#ifdef CANDY
		std::string str = "csb/candy/rage.csb";
		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		//根据糖果类型选表情图片
		std::string lookStr;
		int looknum = rand() % 5;
		switch (looknum)
		{
		case Look::Look1:
			lookStr = _lookPreStr + "candy_bq02.png";
			break;
		case Look::Look2:
			lookStr = _lookPreStr + "candy_bq03.png";
			break;
		case Look::Look3:
			lookStr = _lookPreStr + "candy_bq04.png";
			break;
		case Look::Look4:
			lookStr = _lookPreStr + "candy_bq05.png";
			break;
		case Look::Look5:
			lookStr = _lookPreStr + "candy_bq06.png";
			break;
		}
		bq->setTexture(lookStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0, 0, false);
		return rootNode;
#endif
	}
	Node* Fish::getNormalFish(int type){

#ifdef LONGBAO
		std::string str = "csb/longbao/smile.csb";
		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* body = (Sprite*)rootNode->getChildByName("candy");
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");

		switch (type)
		{
		case FishName::BLUE:
			body->setTexture(_longbaoPreStr + "blue.png");
			bq->setColor(Color3B(136, 219, 243));
			break;
		case FishName::GREEN:
			body->setTexture(_longbaoPreStr + "green.png");
			bq->setColor(Color3B(131, 214, 149));
			break;
		case FishName::EYE:
			body->setTexture(_longbaoPreStr + "brown.png");
			bq->setColor(Color3B(226, 172, 114));
			break;
		case FishName::RED:
			body->setTexture(_longbaoPreStr + "pink.png");
			bq->setColor(Color3B(226, 114, 172));
			break;
		}
		std::string lookStr = _lookPreStr + "candy_bq08.png";
		int looknum = rand() % 5;
		switch (looknum)
		{
		case 0:
			lookStr = _lookPreStr + "candy_bq01.png";
			break;
		case 1:
			lookStr = _lookPreStr + "candy_bq02.png";
			break;
		case 2:
			lookStr = _lookPreStr + "candy_bq03.png";
			break;
		case 3:
			lookStr = _lookPreStr + "candy_bq07.png";
			break;
		case 4:
			lookStr = _lookPreStr + "candy_bq08.png";
			break;
		}
		bq->setTexture(lookStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(35, 35, false);
		return rootNode;
#endif

#ifdef CANDY
		std::string str = "csb/candy/candy_blue_normal.csb";

		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* body = (Sprite*)rootNode->getChildByName("candy_blue");
		switch (type)
		{
		case FishName::BLUE:
			body->setTexture(_candyPreStr + "candy_blue.png");
			break;
		case FishName::RED:
			body->setTexture(_candyPreStr + "candy_red.png");
			break;
		case FishName::GREEN:
			body->setTexture(_candyPreStr + "candy_green.png");
			break;
		case FishName::EYE:
			body->setTexture(_candyPreStr + "candy_eye.png");
			break;
		case FishName::PINK:
			body->setTexture(_candyPreStr + "candy_pink.png");
			break;
		case FishName::YELLOW:
			body->setTexture(_candyPreStr + "candy_yellow.png");
			break;
		case FishName::PURPLE:
			body->setTexture(_candyPreStr + "candy_purple.png");
			break;
		case FishName::BROWN:
			body->setTexture(_candyPreStr + "candy_brown.png");
			break;
		}
		//加载动画：
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		return rootNode;
#endif
	}
	Node* Fish::getChangeFish(int type){
		std::string str = "csb/candy/candy_blue_normal.csb";

		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* body = (Sprite*)rootNode->getChildByName("candy_blue");
		Sprite* mohu = (Sprite*)rootNode->getChildByName("candy_blue_mh");
		switch (type)
		{
		case FishName::BLUE:
			body->setTexture(_candyPreStr + "candy_blue.png");
			mohu->setTexture(_candyPreStr + "candy_blue_mh.png");
			break;
		case FishName::RED:
			body->setTexture(_candyPreStr + "candy_red.png");
			mohu->setTexture(_candyPreStr + "candy_red_mh.png");
			break;
		case FishName::GREEN:
			body->setTexture(_candyPreStr + "candy_green.png");
			mohu->setTexture(_candyPreStr + "candy_green_mh.png");
			break;
		case FishName::EYE:
			body->setTexture(_candyPreStr + "candy_eye.png");
			mohu->setTexture(_candyPreStr + "candy_eye_mh.png");
			break;
		case FishName::PINK:
			body->setTexture(_candyPreStr + "candy_pink.png");
			mohu->setTexture(_candyPreStr + "candy_pink_mh.png");
			break;
		case FishName::YELLOW:
			body->setTexture(_candyPreStr + "candy_yellow.png");
			mohu->setTexture(_candyPreStr + "candy_yellow_mh.png");
			break;
		case FishName::PURPLE:
			body->setTexture(_candyPreStr + "candy_purple.png");
			mohu->setTexture(_candyPreStr + "candy_purple_mh.png");
			break;
		case FishName::BROWN:
			body->setTexture(_candyPreStr + "candy_brown.png");
			mohu->setTexture(_candyPreStr + "candy_brown_mh.png");
			break;
		}
		std::string lookStr;
		int looknum = rand() % 4;
		switch (looknum)
		{
		case 0:
			lookStr = _lookPreStr + "candy_bq01.png";
			break;
		case 1:
			lookStr = _lookPreStr + "candy_bq02.png";
			break;
		case 2:
			lookStr = _lookPreStr + "candy_bq03.png";
			break;
		case 3:
			lookStr = _lookPreStr + "candy_bq07.png";
			break;
		}
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		bq->setTexture(lookStr);

		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(0, 35, false);
		return rootNode;
	}
	Node* Fish::getSmileFish(int type){
		std::string str = "csb/candy/candy_blue_normal.csb";

		Node* rootNode = CSLoader::createNode(str);//传入Studio2.x的资源路径
		Sprite* body = (Sprite*)rootNode->getChildByName("candy_blue");
		Sprite* mohu = (Sprite*)rootNode->getChildByName("candy_blue_mh");
		switch (type)
		{
		case FishName::BLUE:
			body->setTexture(_candyPreStr + "candy_blue.png");
			mohu->setTexture(_candyPreStr + "candy_blue_mh.png");
			break;
		case FishName::RED:
			body->setTexture(_candyPreStr + "candy_red.png");
			mohu->setTexture(_candyPreStr + "candy_red_mh.png");
			break;
		case FishName::GREEN:
			body->setTexture(_candyPreStr + "candy_green.png");
			mohu->setTexture(_candyPreStr + "candy_green_mh.png");
			break;
		case FishName::EYE:
			body->setTexture(_candyPreStr + "candy_eye.png");
			mohu->setTexture(_candyPreStr + "candy_eye_mh.png");
			break;
		case FishName::PINK:
			body->setTexture(_candyPreStr + "candy_pink.png");
			mohu->setTexture(_candyPreStr + "candy_pink_mh.png");
			break;
		case FishName::YELLOW:
			body->setTexture(_candyPreStr + "candy_yellow.png");
			mohu->setTexture(_candyPreStr + "candy_yellow_mh.png");
			break;
		case FishName::PURPLE:
			body->setTexture(_candyPreStr + "candy_purple.png");
			mohu->setTexture(_candyPreStr + "candy_purple_mh.png");
			break;
		case FishName::BROWN:
			body->setTexture(_candyPreStr + "candy_brown.png");
			mohu->setTexture(_candyPreStr + "candy_brown_mh.png");
			break;
		}
		std::string lookStr;
		int looknum = rand() % 4;
		switch (looknum)
		{
		case 0:
			lookStr = _lookPreStr + "candy_bq01.png";
			break;
		case 1:
			lookStr = _lookPreStr + "candy_bq02.png";
			break;
		case 2:
			lookStr = _lookPreStr + "candy_bq03.png";
			break;
		case 3:
			lookStr = _lookPreStr + "candy_bq07.png";
			break;
		}
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		bq->setTexture(lookStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(str);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		//播放动画： 
		action->gotoFrameAndPlay(35, 35, false);
		return rootNode;
	}
	Node* Fish::getShockFish(int type){
#ifdef LONGBAO
		//根据糖果类型选表情图片
		std::string lookStr = _lookPreStr + "candy_bq06.png";
		//根据糖果类型选动效
		std::string actionStr = "csb/longbao/cap1.csb";

		Node* rootNode = CSLoader::createNode(actionStr);//传入Studio2.x的资源路径
		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		Sprite* mohu = (Sprite*)rootNode->getChildByName("candy");		
		bq->setTexture(lookStr);
		//根据糖果类型选糖果图片
		std::string typeStr;
		switch (type)
		{
		case FishName::BLUE:
			mohu->setTexture(_longbaoPreStr + "blue.png");
			bq->setColor(Color3B(136, 219, 243));
			break;
		case FishName::GREEN:
			mohu->setTexture(_longbaoPreStr + "green.png");
			bq->setColor(Color3B(131, 214, 149));
			break;
		case FishName::EYE:
			mohu->setTexture(_longbaoPreStr + "brown.png");
			bq->setColor(Color3B(226, 172, 114));
			break;
		case FishName::RED:
			mohu->setTexture(_longbaoPreStr + "pink.png");
			bq->setColor(Color3B(226, 114, 172));
			break;
		}

		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(actionStr);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 
		
		//播放动画： 
		action->gotoFrameAndPlay(0);
		return rootNode;
#endif
#ifdef CANDY
		//根据糖果类型选糖果图片
		std::string typeStr;
		switch (type)
		{
		case FishName::BLUE:
			typeStr = _candyPreStr +  "candy_blue_mh.png";
			break;
		case FishName::RED:
			typeStr = _candyPreStr + "candy_red_mh.png";
			break;
		case FishName::GREEN:
			typeStr = _candyPreStr + "candy_green_mh.png";
			break;
		case FishName::EYE:
			typeStr = _candyPreStr + "candy_eye_mh.png";
			break;
		case FishName::PINK:
			typeStr = _candyPreStr + "candy_pink_mh.png";
			break;
		case FishName::YELLOW:
			typeStr = _candyPreStr + "candy_yellow_mh.png";
			break;
		case FishName::PURPLE:
			typeStr = _candyPreStr + "candy_purple_mh.png";
			break;
		case FishName::BROWN:
			typeStr = _candyPreStr + "candy_brown_mh.png";
			break;
		}
		//根据糖果类型选表情图片
		std::string lookStr = _lookPreStr + "candy_bq06.png";
		//根据糖果类型选动效
		std::string actionStr = "csb/candy/candy_eye_cap.csb";

		Node* rootNode = CSLoader::createNode(actionStr);//传入Studio2.x的资源路径

		Sprite* bq = (Sprite*)rootNode->getChildByName("bq");
		Sprite* mohu = (Sprite*)rootNode->getChildByName("candy");

		bq->setTexture(lookStr);
		mohu->setTexture(typeStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(actionStr);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 

		//播放动画： 
		action->gotoFrameAndPlay(0);
		return rootNode;
#endif
	}

	Node* Fish::getPressFish(int type){
#ifdef LONGBAO
		//根据糖果类型选动效
		std::string actionStr;
		int actionnum = rand() % 3;
		switch (actionnum)
		{
		case BodyAction::Body1:
			actionStr = "csb/longbao/cap1.csb";
			break;
		case BodyAction::Body2:
			actionStr = "csb/longbao/cap2.csb";
			break;
		case BodyAction::Body3:
			actionStr = "csb/longbao/cap3.csb";
			break;
		}
		Node* rootNode = CSLoader::createNode(actionStr);//传入Studio2.x的资源路径

		Sprite* bq = NULL;
		Sprite* mohu = NULL;

		if (actionnum == BodyAction::Body2)
		{
			bq = (Sprite*)rootNode->getChildByName("cap2_in")->getChildByName("bq");
			mohu = (Sprite*)rootNode->getChildByName("cap2_in")->getChildByName("candy");
		}
		else
		{
			bq = (Sprite*)rootNode->getChildByName("bq");
			mohu = (Sprite*)rootNode->getChildByName("candy");
		}


		//根据糖果类型选糖果图片
		switch (type)
		{
		case FishName::BLUE:
			mohu->setTexture(_longbaoPreStr + "blue.png");
			bq->setColor(Color3B(136, 219, 243));
			break;
		case FishName::GREEN:
			mohu->setTexture(_longbaoPreStr + "green.png");
			bq->setColor(Color3B(131, 214, 149));
			break;
		case FishName::EYE:
			mohu->setTexture(_longbaoPreStr + "brown.png");
			bq->setColor(Color3B(226, 172, 114));
			break;
		case FishName::RED:
			mohu->setTexture(_longbaoPreStr + "pink.png");
			bq->setColor(Color3B(226, 114, 172));
			break;
		}
		//根据糖果类型选表情图片
		std::string lookStr;
		int looknum = rand() % 2;
		switch (looknum)
		{
		case 0:
			lookStr = _lookPreStr + "candy_bq04.png";
			break;
		case 1:
			lookStr = _lookPreStr + "candy_bq05.png";
			break;
		}
		bq->setTexture(lookStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(actionStr);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 

		//播放动画： 
		action->gotoFrameAndPlay(0);
		return rootNode;
#endif

#ifdef CANDY
		//根据糖果类型选糖果图片
		std::string typeStr;
		switch (type)
		{
		case FishName::BLUE:
			typeStr = _candyPreStr + "candy_blue_mh.png";
			break;
		case FishName::RED:
			typeStr = _candyPreStr + "candy_red_mh.png";
			break;
		case FishName::GREEN:
			typeStr = _candyPreStr + "candy_green_mh.png";
			break;
		case FishName::EYE:
			typeStr = _candyPreStr + "candy_eye_mh.png";
			break;
		case FishName::PINK:
			typeStr = _candyPreStr + "candy_pink_mh.png";
			break;
		case FishName::YELLOW:
			typeStr = _candyPreStr + "candy_yellow_mh.png";
			break;
		case FishName::PURPLE:
			typeStr = _candyPreStr + "candy_purple_mh.png";
			break;
		case FishName::BROWN:
			typeStr = _candyPreStr + "candy_brown_mh.png";
			break;
		}
		//根据糖果类型选表情图片
		std::string lookStr;
		int looknum = rand() % 2;
		switch (looknum)
		{
		case 0:
			lookStr = _lookPreStr + "candy_bq04.png";
			break;
		case 1:
			lookStr = _lookPreStr + "candy_bq05.png";
			break;
		}
		//根据糖果类型选动效
		std::string actionStr;
		int actionnum = rand() % 3;
		switch (actionnum)
		{
		case BodyAction::Body1:
			actionStr = "csb/candy/candy_eye_cap.csb";
			break;
		case BodyAction::Body2:
			actionStr = "csb/candy/candy_red_cap.csb";
			break;
		case BodyAction::Body3:
			actionStr = "csb/candy/candy_green_cap.csb";
			break;
		}
		Node* rootNode = CSLoader::createNode(actionStr);//传入Studio2.x的资源路径

		Sprite* bq = NULL;
		Sprite* mohu = NULL;
		if (actionnum == BodyAction::Body3)
		{
			bq = (Sprite*)rootNode->getChildByName("candy_green_cap_in")->getChildByName("bq");
			mohu = (Sprite*)rootNode->getChildByName("candy_green_cap_in")->getChildByName("candy");
		}
		else
		{
			bq = (Sprite*)rootNode->getChildByName("bq");
			mohu = (Sprite*)rootNode->getChildByName("candy");
		}
		bq->setTexture(lookStr);
		mohu->setTexture(typeStr);
		//加载动画： 
		ActionTimeline *action = CSLoader::createTimeline(actionStr);
		rootNode->runAction(action);//注!!!：同一个文件创建的节点只能使用同一个文件创建的动画。 

		//播放动画： 
		action->gotoFrameAndPlay(0);
		return rootNode;
#endif
	}
	Node* Fish::getLine(int lineNameEnum)
	{
#ifdef LONGBAO
		Sprite*line;
		std::stringstream str;
		cocostudio::Armature* armature;
		switch (lineNameEnum)
		{
		case FishName::DISCO:
			line = Sprite::create(_longbaoPreStr + "candy_tiao.png");
			line->setColor(Color3B(0, 0, 0));
			break;
		case FishName::BLUE:
			line = Sprite::create(_longbaoPreStr + "candy_tiao.png");
			line->setColor(Color3B(136,219,243));
			break;
		case FishName::GREEN:
			line = Sprite::create(_longbaoPreStr + "candy_tiao.png");
			line->setColor(Color3B(131, 214, 149));
			break;
		case FishName::EYE:
			line = Sprite::create(_longbaoPreStr + "candy_tiao.png");
			line->setColor(Color3B(226, 172, 114));
			break;
		case FishName::RED:
			line = Sprite::create(_longbaoPreStr + "candy_tiao.png");
			line->setColor(Color3B(226, 114, 172));
			break;
		}
		return line;
#endif
#ifdef CANDY
		Sprite*line;
		std::stringstream str;
		cocostudio::Armature* armature;
		switch (lineNameEnum)
		{
		case FishName::DISCO:
			line = Sprite::create(_candyPreStr + "candy_disco_cap111.png");
			break;
		case FishName::BLUE:
			line = Sprite::create(_candyPreStr + "candy_blue1.png");
			break;
		case FishName::EYE:
			line = Sprite::create(_candyPreStr + "candy_eye1.png");
			break;
		case FishName::GREEN:
			line = Sprite::create(_candyPreStr + "candy_green1.png");
			break;
		case FishName::RED:
			line = Sprite::create(_candyPreStr + "candy_red1.png");
			break;
		case FishName::PINK:
			line = Sprite::create(_candyPreStr + "candy_pink1.png");
			break;
		case FishName::YELLOW:
			line = Sprite::create(_candyPreStr + "candy_yellow1.png");
			break;
		case FishName::PURPLE:
			line = Sprite::create(_candyPreStr + "candy_purple1.png");
			break;
		case FishName::BROWN:
			line = Sprite::create(_candyPreStr + "candy_brown1.png");
			break;
		}
		return line;
#endif
	}
}
