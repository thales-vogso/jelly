/****************************************************************************
*	@       	       
*	@desc	缓存-音乐
*	@date	2014-11-4
*	@author	120101
*	@       	       
*	@file	cache/Music.h
*	@modify	null
******************************************************************************/

#include "Music.h"

USING_NS_CC;
using namespace cocostudio;

namespace cache{
	Music* Music::_instance = nullptr;
	const std::string Music::prefix = "music";
	Music::Music(){
	}
	Music::~Music(){
	
	}
	void Music::async(){
		_loaded = 0;
		int* id = 0;
		Loader::getInstance()->start(id);
		std::stringstream str;
		//str << prefix << "/" << bgmName;
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(str.str().c_str());
		for (int i = 0; i < effectCount; i++){
			std::stringstream str;
			str << prefix << "/" << this->getSoundEffectStringByEnum(i);
			CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(str.str().c_str());
		}
	}
	Music* Music::getInstance(){
		if (!_instance){
			_instance = new Music();
		}
		return _instance;
	}
	void Music::playEffect(int effectNameEnum){
		if (!data::User::getInstance()->getSoundEffect())
			return;
		std::string effectName = this->getSoundEffectStringByEnum(effectNameEnum);
		std::stringstream str;
		str << prefix << "/" << effectName;
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(str.str().c_str());
//        CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(<#float volume#>)
	}
	void Music::playBGM(int bgmEnum){
		if (!data::User::getInstance()->getBGM())
			return;		
		std::string bgmName = this->getBGMStringByEnum(bgmEnum);
		std::stringstream str;
		str << prefix << "/" << bgmName;
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(str.str().c_str(),true);
	}
	void Music::pauseBGM(){
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}
	void Music::resumeBGM(){
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}
	std::string Music::getSoundEffectStringByEnum(int id){
		std::string str;
		switch (id)
		{
		case EffectName::BUYGOLD:
			str = "buygold.wav";
			break;
		case EffectName::CLICKBUTTON:
			str = "clickbutton.wav";
			break;
		case EffectName::GAMEOVER:
			str = "gameover.wav";
			break;
		case EffectName::FISHBOMB:
			str = "fishbomb.wav";
			break;
		case EffectName::PRESSFISH:
			str = "pressfish.wav";
			break;
		case EffectName::GAMEWIN:
			str = "gamewin.wav";
			break;
		case EffectName::PULL:
			str = "bgm.mp3";
			break;
		default:
			break;
		}
		return str;
	}
	std::string Music::getBGMStringByEnum(int id){
		std::string str;
		switch (id)
		{
		case BGMName::GATEWAY:
			str = "gateway.mp3";
			break;
		case BGMName::GAME:
			str = "bgm.mp3";
			break;
		default:
			break;
		}
		return str;
	}
	//void Music::jsonAsyncCallback(){
	//	ProgressObj obj;
	//	obj.loaded = _loaded;
	//	obj.total = cache::Music::effectCount + 1;
	//	if (obj.loaded >= obj.total - 1){
	//		Loader::getInstance()->complete(&obj);
	//	}else{
	//		_loaded++;
	//		Loader::getInstance()->progress(&obj);
	//	}
	//}
}
