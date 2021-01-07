/****************************************************************************
*	@       	       
*	@desc	设置界面
*	@date	2014-10-20
*	@author	120101
*	@       	       
*	@file	setting/Setting.cpp
*	@modify	2014-10-25 by 110101
******************************************************************************/

#include "AppDelegate.h"
#include "Setting.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;

Node* Setting::getPanel(){
	_panel = CSLoader::createNode(PANEL_NAME.c_str());
	return _panel;
}
Node* Setting::getButtonFromPanel(std::string name){
	Node* ui = Main::seekNodeByName(_panel, name);
	return ui;
}
Widget* Setting::getButtonFromPanel(int id){
	std::string name = getButtonNameByEnum(id);
	Widget* ui = (Widget*)getButtonFromPanel(name);
	return ui;
}
std::string Setting::getButtonNameByEnum(int id){
	std::string str;
	switch (id)
	{
	case ButtonName::BGM:
		str = "bgmBtn";
		break;
	case ButtonName::EFFECT:
		str = "effectBtn";
		break;
	case ButtonName::HELP:
		str = "helpBtn";
		break;
	case ButtonName::BACK:
		str = "backBtn";
		break;
	default:
		break;
	}
	return str;
}
Node* Setting::getElementFromButton(int id){
	Node* ui;
	switch (id)
	{
	case SoundEffectBtn::BLOCK:
		ui = getButtonFromPanel(EFFECT)->getChildByName("track")->getChildByName("block");
		break;
	case SoundEffectBtn::ON:
		ui = getButtonFromPanel(EFFECT)->getChildByName("track")->getChildByName("block")->getChildByName("on");
		break;
	case SoundEffectBtn::OFF:
		ui = getButtonFromPanel(EFFECT)->getChildByName("track")->getChildByName("block")->getChildByName("off");
		break;

	case BGMBtn::BLOCK:
		ui = getButtonFromPanel(BGM)->getChildByName("track")->getChildByName("block");
		break;
	case BGMBtn::ON:
		ui = getButtonFromPanel(BGM)->getChildByName("track")->getChildByName("block")->getChildByName("on");
		break;
	case BGMBtn::OFF:
		ui = getButtonFromPanel(BGM)->getChildByName("track")->getChildByName("block")->getChildByName("off");
		break;
	default:
		break;
	}
	return ui;
}

void Setting::setBGM(bool valid){
	data::User::getInstance()->setBGM(valid);
	Node* block = getElementFromButton(BGMBtn::BLOCK);
	Node* on = getElementFromButton(BGMBtn::ON);
	Node* off = getElementFromButton(BGMBtn::OFF);
	if (valid){
		block->setPositionX((float)BLOCK_ON_X);
		on->setVisible(true);
		off->setVisible(false);
		cache::Music::getInstance()->playBGM(cache::Music::BGMName::GATEWAY);
	}else{
		block->setPositionX((float)BLOCK_OFF_X);
		on->setVisible(false);
		off->setVisible(true);
		cache::Music::getInstance()->pauseBGM();
	}
}
void Setting::setBGM(){
	bool valid = data::User::getInstance()->getBGM();
	setBGM(!valid);
}
void Setting::setSoundEffect(bool valid){
	data::User::getInstance()->setSoundEffect(valid);
	Node* block = getElementFromButton(SoundEffectBtn::BLOCK);
	Node* on = getElementFromButton(SoundEffectBtn::ON);
	Node* off = getElementFromButton(SoundEffectBtn::OFF);
	if (valid){
		block->setPositionX((float)BLOCK_ON_X);
		on->setVisible(true);
		off->setVisible(false);
	}
	else{
		block->setPositionX((float)BLOCK_OFF_X);
		on->setVisible(false);
		off->setVisible(true);
	}
}
void Setting::setSoundEffect(){
	bool valid = data::User::getInstance()->getSoundEffect();
	setSoundEffect(!valid);
}

bool Setting::init(){

	if (!Layer::init()){
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	
	/** cocostuido原件 */
	Node* panel = getPanel();
	addChild(panel,2);

	Widget* bgm = getButtonFromPanel(BGM);
	Widget* effect = getButtonFromPanel(EFFECT);
	Widget* help = getButtonFromPanel(HELP);
	Widget* back = getButtonFromPanel(BACK);
	Widget* backTouch = cocos2d::ui::Helper::seekWidgetByName(back, "touch");
	/** 设置初始位置 */
	back->setPosition(Vec2(0 + 26 + 45, -26 -45 + 180 + visibleSize.height)+visibleSize);
	bgm->setPosition(Vec2(visibleSize.width * 1.5f, visibleSize.height * 0.5) + visibleSize);
	effect->setPosition(Vec2(bgm->getPositionX() - BUTTON_SPACE - effect->getContentSize().width, visibleSize.height * 0.5) + visibleSize);
	help->setPosition(Vec2(bgm->getPositionX() + BUTTON_SPACE + help->getContentSize().width, visibleSize.height * 0.5) + visibleSize);
	/** 点击事件 */
	backTouch->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Setting::backBtnClick, this)));
	bgm->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Setting::bgmBtnClick, this)));
	effect->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Setting::soundEffectBtnClick, this)));
	help->addTouchEventListener(ui::Widget::ccWidgetTouchCallback(CC_CALLBACK_2(Setting::helpBtnClick, this)));
	/** 两个声音按纽初始化 */
	bool soundEffectValid = data::User::getInstance()->getSoundEffect();
	bool bgmValid = data::User::getInstance()->getBGM();
	setSoundEffect(soundEffectValid);
	setBGM(bgmValid);
	return true;
}
void Setting::bgmBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		setBGM();
		//增加音效
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}
void Setting::soundEffectBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		setSoundEffect();
		//增加音效
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}
void Setting::helpBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		//增加音效
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);

		Scene* scene = Guide::createScene(1);
		Director::getInstance()->replaceScene(TransitionCrossFade::create(0.7, (Scene*)scene));
	}
}
void Setting::backBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e){
	if (e == cocos2d::ui::Widget::TouchEventType::ENDED){
		Main* main = (Main*)this->getParent();
		main->clickMain();
		//增加音效
		cache::Music::getInstance()->playEffect(cache::Music::EffectName::CLICKBUTTON);
	}
}

void Setting::moveIn(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Widget* bgm = getButtonFromPanel(BGM);
	Widget* effect = getButtonFromPanel(EFFECT);
	Widget* help = getButtonFromPanel(HELP);
	Widget* back = getButtonFromPanel(BACK);
	Widget* backTouch = cocos2d::ui::Helper::seekWidgetByName(back, "touch");
	backTouch->setTouchEnabled(true);

	/** 缓动事件 */
	Sequence* backSeq = Sequence::create(DelayTime::create(0.6f), EaseBounceOut::create(MoveBy::create(0.5f, Vec2(0, - 180))), NULL);
	Sequence* bgmSeq = Sequence::create(DelayTime::create(0.8f), EaseOut::create(MoveTo::create(0.5f, Vec2(visibleSize.width * 0.5, visibleSize.height * 0.5) + visibleSize), 2.5f), NULL);
	Sequence* soundEffectSeq = Sequence::create(DelayTime::create(0.6f), EaseOut::create(MoveTo::create(0.5f, Vec2(visibleSize.width * 0.5 - BUTTON_SPACE - effect->getContentSize().width, visibleSize.height * 0.5) + visibleSize), 2.5f), NULL);
	auto done = CallFuncN::create([=](Ref* ref)
	{Main* main = (Main*)this->getParent();
	main->switchToSetting(); });
	Sequence* helpSeq = Sequence::create(DelayTime::create(1), EaseOut::create(MoveTo::create(0.5f, Vec2(visibleSize.width * 0.5 + BUTTON_SPACE + help->getContentSize().width, visibleSize.height * 0.5) + visibleSize), 2.5f),done, NULL);
	back->runAction(backSeq);
	bgm->runAction(bgmSeq);
	effect->runAction(soundEffectSeq);
	help->runAction(helpSeq);
}

void Setting::moveOut(){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Widget* bgm = getButtonFromPanel(BGM);
	Widget* effect = getButtonFromPanel(EFFECT);
	Widget* help = getButtonFromPanel(HELP);
	Widget* back = getButtonFromPanel(BACK);

	/** 缓动事件 */
	Sequence* backSeq = Sequence::create(EaseIn::create(MoveBy::create(0.5f, Vec2(0, 180)),2.5f), NULL);

	Sequence* bgmSeq = Sequence::create(DelayTime::create(0.4f), EaseIn::create(MoveTo::create(0.3f, Vec2(bgm->getPositionX() + visibleSize.width, visibleSize.height * 0.5) + visibleSize), 2.5f), NULL);
	Sequence* soundEffectSeq = Sequence::create(DelayTime::create(0.6f), EaseIn::create(MoveTo::create(0.3f, Vec2(effect->getPositionX() + visibleSize.width, visibleSize.height * 0.5) + visibleSize), 2.5f), NULL);
	Sequence* helpSeq = Sequence::create(DelayTime::create(0.2f), EaseIn::create(MoveTo::create(0.3f, Vec2(help->getPositionX() + visibleSize.width, visibleSize.height * 0.5) + visibleSize), 2.5f), NULL);

	back->runAction(backSeq);
	bgm->runAction(bgmSeq);
	effect->runAction(soundEffectSeq);
	help->runAction(helpSeq);
}