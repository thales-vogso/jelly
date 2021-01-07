/****************************************************************************
*	@       	       
*	@desc	缓存-鱼
*	@date	2014-10-23
*	@author	110101
*	@       	       
*	@file	popstar/Classes/cache/Fish.h
*	@modify	null
******************************************************************************/
#ifndef __CACHE_FISH_H__
#define __CACHE_FISH_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "loading/Loader.h"
#include "plat.h"
namespace cache {
	class Fish :public cocos2d::Layer{
	public:
		/**
		*	鱼名字
		*/
		enum FishName{
			DISCO = -1,
			BLUE,
			GREEN,
			EYE,
			RED,
			PINK,
			YELLOW,
			PURPLE,
			BROWN
		};
		/**
		*	鱼身动作
		*/
		enum BodyAction{
			Body1,
			Body2,
			Body3
		};
		/**
		*	表情动作
		*/
		enum Look{
			Look1,
			Look2,
			Look3,
			Look4,
			Look5,
			Look6
		};
		/**
		 *	初始化
		 */
		Fish();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~Fish();
		/**
		 *	初始化
		 */
		void async();
		/**
		 *	获取实体
		 */
		static Fish* getInstance();
		/**
		*	获得狂暴鱼
		*	@return	鱼结构
		*/
		Node* getRageFish();
		/**
		*	获得电击鱼
		*	@return	鱼结构
		*/
		Node* getShockFish(int type);
		/**
		*	获得挤压鱼
		*	@return	鱼结构
		*/
		Node* getPressFish(int type);
		/**
		*	获得笑鱼
		*	@return	鱼结构
		*/
		Node* getSmileFish(int type);
		/**
		*	获得变化鱼
		*	@return	鱼结构
		*/
		Node* getChangeFish(int type);
		/**
		 *	获得普通鱼
		 *	@return	鱼结构
		 */
		Node* getNormalFish(int type);
		/**
		*	获得迪斯科普通鱼
		*	@return	鱼结构
		*/
		Node* getDiscoNormalFish();
		/**
		*	获得迪斯科逮捕鱼
		*	@return	鱼结构
		*/
		Node* getDiscoPressFish();
		/*
		*	获取鱼的线
		*/
		Node* getLine(int lineNameEnum);
		/**
		 *	回调
		 */
		void jsonAsyncCallback(float dt);
		/**
		 *	鱼的总数量
		 */
		static const int fishCount = 5;
		/**
		 *	前缀
		 */
		static const std::string prefix;
	private:
		/**
		*	表情图片前缀
		*/
		std::string _lookPreStr = "pic/public/";
		/**
		*	糖果图片前缀
		*/
		std::string _candyPreStr = "pic/candy/";
		/**
		*	笼包图片前缀
		*/
		std::string _longbaoPreStr = "pic/longbao/";
		/**
		 *	自身
		 */
		static Fish* _instance;
		/**
		 *	已经载入的数据
		 */
		int _loaded = 0;
	};
}
#endif // __CACHE_FISH_H__
