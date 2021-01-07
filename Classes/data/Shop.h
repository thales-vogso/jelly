/****************************************************************************
*	@       	       
*	@desc	商店数据
*	@date	2014-10-21
*	@author	120101
*	@       	       
*	@file	data/Shop.h
*	@modify	null
******************************************************************************/
#ifndef __DATA_SHOP_H__
#define __DATA_SHOP_H__

#include "cocos2d.h"
#include "db/DBConnector.h"
#include "db/Table.h"

namespace data{
	/**
	 *	设置数据信息
	 */
	typedef struct shopTag{
		int goodid;
		std::string name;
		int num;
		int price;
		int goodtype;
		int pricetype;
	}ShopInfo;

	class Shop {
	public:

		enum GoodID{
			GOLD,
			SHOCK,
			BOMB,
			CRAZY
		};		
		enum PriceType{
			COIN,
			RMB
		};
		enum GoodsType{
			ANDROIDMONEY,
			IOSMONEY,
			ITEM
		};
		/**
		 *	初始化
		 */
		Shop();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~Shop();
		/**
		 *	获取实体
		 */
		static Shop* getInstance();
		/**
		 *	初始化
		 */
		void init();
		/**
		 *	通过type类型获取DBObject容器
		 *	@return DBObject容器
		 */
		std::vector<UMGDBRow> getGoodsByType(int i);
		/**
		*	通过gid类型获取DBObject容器
		*	@return DBObject对象
		*/
		UMGDBRow getGoodById(int i);
		/**
		 *	金币商店默认信息
		 */
		static const ShopInfo DEFAULT_DATA[];
		/**
		 *	数据表-金币商店
		 */
		static const std::string TABLE_SHOP;

	private:
		/**
		 *	自身
		 */
		static Shop* _instance;
		/**
		 *	数据库
		 */
		DBSqlite* _db;
	};
}
#endif // __DATA_SHOP_H__
