/****************************************************************************
*	@       	       
*	@desc	道具数据
*	@date	2014-10-30
*	@author	110101
*	@       	       
*	@file	data/Item.h
*	@modify	null
******************************************************************************/
#ifndef __DATA_ITEM_H__
#define __DATA_ITEM_H__

#include "cocos2d.h"
#include "db/DBSqlite.h"
#include "db/Table.h"
#include "User.h"

namespace data{
	/**
	*	道具信息
	*/
	typedef struct UserItemInfoTag{
		int id;	//
		int num;	//数量
	}UserItemInfo;
	typedef struct ItemInfoTag{
		int id;	//
		std::string name;//名称
	}ItemInfo;

	class Item {
	public:
		/**
		 *	初始化
		 */
		Item();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~Item();
		/**
		 *	初始化
		 */
		void init();
		/**
		 *	获取实体
		 */
		static Item* getInstance();
		/**
		 *	获取道具列表
		 */
		std::vector<ItemInfo> getItems();
		/**
		 *	根据id获取道具
		 */
		ItemInfo getItemByID(int id);
		/**
		 *	获取道具列表
		 */
		std::vector<UMGDBRow> getUserItems();
		/**
		 *	获取道具数量
		 */
		UMGDBRow getUserItemNum();
		/**
		 *	通过道具id获取道具
		 *	@param	id	道具id
		 */
		UMGDBRow getUserItemByItemID(int id);
		/**
		 *	通过道具id获取道具数量
		 *	@param	id	道具id
		 */
		int getUserItemNumByItemID(int id);
		/**
		 *	添加道具
		 *	@param	id	道具id
		 *	@param	num	数量
		 *	@param	method	方式，系统，购买，使用
		 */
		void add(int id, int num, int method);
		/**
		 *	使用道具
		 */
		void use(int id);
		/**
		 *	获取日期字符串
		 */
		std::string getDate(time_t timestamp = NULL);
		/**
		 *	道具方式
		 */
		enum MethodType{
			SYSTEM,//系统
			BUY,//购买
			USE//使用
		};
		/**
		 *	电击道具id
		 */
		static const int ITEM_SHOCK_ID = 1;
		/**
		 *	炸弹道具id
		 */
		static const int ITEM_BOMB_ID = 2;
		/**
		 *	狂暴道具id
		 */
		static const int ITEM_RAGE_ID = 3;
		/**
		 *	道具改变事件
		 */
		static const std::string ITEM_CHANGE;
	private:
		/**
		 *	自身
		 */
		static Item* _instance;
		/**
		 *	数据库
		 */
		DBSqlite* _db;
		/**
		 *	用户uid
		 */
		int _uid;
		/**
		 *	道具
		 */
		std::vector<ItemInfo> _items;
		/**
		 *	记录日志
		 */
		void record(int id, int num, int method);
		
		/**
		 *	用户道具
		 */
		const std::string USER_ITEM_TABLE = "user_item";
		/**
		 *	用户道具日志
		 */
		const std::string USER_ITEM_LOG_TABLE = "user_item_log";
		/*
		*	玩家道具初始数据
		*/
		const int ItemNum=5;
	};
}
#endif // __DATA_ITEM_H__
