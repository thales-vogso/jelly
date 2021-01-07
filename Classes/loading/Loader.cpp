/****************************************************************************
*	@       	       
*	@desc	载入
*	@date	2014-10-21
*	@author	110101
*	@       	       
*	@file	loading/Loader.h
*	@modify	null
******************************************************************************/

#include "Loader.h"

USING_NS_CC;

const std::string Loader::START = "loadStart";
const std::string Loader::PROGRESS = "loadProgress";
const std::string Loader::COMPLETE = "loadComplete";
const std::string Loader::ERR = "loadError";

Loader* Loader::_instance = nullptr;

Loader::Loader(){
	this->init();
}
Loader::~Loader(){
}
Loader* Loader::getInstance(){
	if (!_instance){
		_instance = new Loader();
	}
	return _instance;
}

bool Loader::init(){
	ValueMap picMap = FileUtils::getInstance()->getValueMapFromFile("pic.xml");
	std::string preStr = "";
#ifdef CANDY
		ValueVector candyVec = picMap.at("candy").asValueVector();
		preStr = "pic/candy/";
		for (Value val:candyVec)
		{
			__uiName.push_back(preStr + val.asString() + ".png");
		}
#endif
#ifdef LONGBAO
		ValueVector longbaoVec = picMap.at("longbao").asValueVector();
		preStr = "pic/longbao/";
		for (Value val : longbaoVec)
		{
			__uiName.push_back(preStr + val.asString() + ".png");
		}
#endif
		ValueVector publicVec = picMap.at("public").asValueVector();
		preStr = "pic/public/";
		for (Value val : publicVec)
		{
			__uiName.push_back(preStr + val.asString() + ".png");
		}
		ValueVector uiVec = picMap.at("ui").asValueVector();
		preStr = "pic/ui/";
		for (Value val : uiVec)
		{
			__uiName.push_back(preStr + val.asString() + ".png");
		}
		ValueVector mapVec = picMap.at("map").asValueVector();
		preStr = "map/";
		for (Value val : mapVec)
		{
			__uiName.push_back(preStr + val.asString());
		}
	return true;
}
void Loader::load(int id){
	_id = id;
	switch (_id)
	{
	case Loader::LoaderResource::GAME:
		gamePreload();
		break;
	case Loader::LoaderResource::UI:
		uiPreload();
		break;
	case Loader::LoaderResource::FISH:
		fishPreload();
		break;
	default:
		break;
	}
}
void Loader::start(void* p){
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::START, &p);
}
void Loader::progress(void* p){
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::PROGRESS, &p);
}
void Loader::complete(void* p){
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::COMPLETE, &p);
}
void Loader::err(void* p){
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::ERR, &p);
}
void Loader::loadingCallback(Texture2D* texture){
	_loadedResource++;
	ProgressObj obj = { _id, _loadedResource, _totalResource };
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::PROGRESS, &obj);
	if (_loadedResource == _totalResource){
		int id = _id;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::COMPLETE, &id);
	}
}
void Loader::gamePreload(){
	_loadedResource = 0;
	_totalResource = 100;
	for (int i = 0; i < 100; i++){
		Director::getInstance()->getTextureCache()->addImageAsync("icon/magic.png", CC_CALLBACK_1(Loader::loadingCallback, this));
	}
	int id = _id;
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Loader::START, &id);
}
void Loader::uiPreload(){
	_loadedResource = 0;
	_totalResource = __uiName.size();
	for (int i = 0; i < __uiName.size(); i++)
	{
		Director::getInstance()->getTextureCache()->addImageAsync(__uiName.at(i), CC_CALLBACK_1(Loader::loadingCallback, this));
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->textureForKey(__uiName.at(i));
		if (texture)
		{
			texture->setAntiAliasTexParameters();
		}
	}
}
void Loader::fishPreload(){
	cache::Fish::getInstance()->async();
}