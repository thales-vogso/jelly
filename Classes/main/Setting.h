/****************************************************************************
*	@       	       
*	@desc	设置界面
*	@date	2014-10-20
*	@author	120101
*	@       	       
*	@file	setting/Setting.h
*	@modify	2014-10-25 by 110101
******************************************************************************/
#ifndef __SETTING_H__
#define __SETTING_H__

#include "cocos2d.h"
#include "main.h"
#include "data/User.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "cache/Music.h"

/**
*	音效按纽元素
*/
namespace SoundEffectBtn{
	enum Element{
		BLOCK = 10,
		ON,
		OFF
	};
};
/**
*	音乐按纽元素
*/
namespace BGMBtn{
	enum Element{
		BLOCK = 20,
		ON,
		OFF
	};
};

class Setting : public cocos2d::Layer{
public:
	/**
	*	存档点击
	*/
	void removeMask(Ref* ref);
	/**
	 *	初始化
	 *	@return	布尔值
	 */
	virtual bool init();
	/**
	 *	设置音乐
	 *	@param	valid	开启或者关闭，如果没有参数为切换
	 */
	void setBGM(bool valid);
	void setBGM();
	/**
	 *	设置音效
	 *	@param	valid	开启或者关闭，如果没有参数为切换
	 */
	void setSoundEffect(bool valid);
	void setSoundEffect();
	/**
	*	移入主屏幕
	*/
	void moveIn();
	/**
	*	移出主屏幕
	*/
	void moveOut();

	CREATE_FUNC(Setting); /** 创造函数 */
private:
	//----------------------------
	/**
	 *	获取cocostuido创造的ui
	 */
	Node* getPanel();
	/**
	 *	从面板获取按纽
	 */
	Node* getButtonFromPanel(std::string name);
	cocos2d::ui::Widget* getButtonFromPanel(int id);
	/**
	 *	从按纽获取元素
	 */
	Node* getElementFromButton(int id);
	/**
	 *	通过枚举获取按纽名称
	 */
	std::string getButtonNameByEnum(int id);
	/**
	 *	通过枚举获取按纽元素名称
	 */
	std::string getButtonElementByEnum(int id);
	/**
	 *	cocostuido创造的ui
	 */
	Node* _panel;
	/**
	 *	cocostuido创造的ui的名字
	 */
	const std::string PANEL_NAME = "csb/main/setting.csb";
	const int BUTTON_SPACE = 150;
	const int BLOCK_OFF_X = 44;
	const int BLOCK_ON_X = 132;
	/**
	 *	按纽名字
	 */
	enum ButtonName{
		EFFECT,
		BGM,
		HELP,
		BACK
	};
	/**
	 *	音乐点击
	 */
	void bgmBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	 *	音效点击
	 */
	void soundEffectBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	 *	帮助点击
	 */
	void helpBtnClick(cocos2d::Ref* ref, cocos2d::ui::Widget::TouchEventType e);
	/**
	*	返回点击
	*/
	void backBtnClick(Ref* ref, cocos2d::ui::Widget::TouchEventType e);
};

#endif // __SETTING_H__
