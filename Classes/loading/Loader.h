/****************************************************************************
*	@       	       
*	@desc	载入
*	@date	2014-10-21
*	@author	110101
*	@       	       
*	@file	loading/Loader.h
*	@modify	null
******************************************************************************/
#ifndef __LOADER_H__
#define __LOADER_H__

#include "cocos2d.h"
#include "cache/Fish.h"
#include "cache/Music.h"

typedef struct progressTag{
	int id;
	int loaded;
	int total;
}ProgressObj;

class Loader{
public:
	/**
	 *	构造函数
	 */
	Loader();
	/**
	 *	析构函数
	 */
	virtual ~Loader();
	/**
	 *	初始化
	 *	@return	布尔值
	 */
	virtual bool init();
	/**
	 *	获取实体
	 */
	static Loader* getInstance();
	/**
	 *	加载
	 *	@param	id	加载的需要处理的内容
	 */
	void load (int id);
	/**
	 *	载入开始
	 *	@param	p	传入的参数
	 */
	void start(void* p);
	/**
	 *	载入中
	 *	@param	p	传入的参数
	 */
	void progress(void* p);
	/**
	 *	载入结束
	 *	@param	p	传入的参数
	 */
	void complete(void* p);
	/**
	 *	载入错误
	 *	@param	p	传入的参数
	 */
	void err(void* p);
	/**
	 *	读取的资源
	 */
	 enum LoaderResource{
		GAME,
		MAP,
		UI,
		FISH
	};
	/**
	 *	载入开始
	 */
	static const std::string START;
	/**
	*	载入进行
	*/
	static const std::string PROGRESS;
	/**
	*	载入完成
	*/
	static const std::string COMPLETE;
	/**
	*	载入错误
	*/
	static const std::string ERR;
private:
	/**
	*	UI资源名称容器
	*/
	std::vector<std::string> __uiName;
	/**
	 *	自身
	 */
	static Loader* _instance;
	/**
	 *	正在加载的内容
	 */
	int _id;
	/**
	 *	已读取资源数
	 */
	int _loadedResource;
	/**
	 *	总资源数
	 */
	int _totalResource;
	/**
	 *	载入回调
	 */
	void loadingCallback(cocos2d::Texture2D* texture);
	/**
	 *	游戏预加载
	 */
	void gamePreload();
	/**
	 *	商城预加载
	 */
	void uiPreload();
	/**
	 *	鱼预加载
	 */
	void fishPreload();
};

#endif // __LOADER_H__
