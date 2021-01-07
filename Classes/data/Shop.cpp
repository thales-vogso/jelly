/****************************************************************************
*	@       	       
*	@desc	商店数据
*	@date	2014-10-21
*	@author	120101
*	@       	       
*	@file	data/Shop.cpp
*	@modify	null
******************************************************************************/

#include "Shop.h"

USING_NS_CC;

namespace data{
	const ShopInfo Shop::DEFAULT_DATA[] = { { GoodID::GOLD, "30", 30, 2, GoodsType::ANDROIDMONEY, PriceType::RMB }, { GoodID::GOLD, "70", 70, 4, GoodsType::ANDROIDMONEY, PriceType::RMB },
	{ GoodID::GOLD, "150", 150, 8, GoodsType::ANDROIDMONEY, PriceType::RMB }, { GoodID::GOLD, "300", 300, 15, GoodsType::ANDROIDMONEY, PriceType::RMB },
	{ GoodID::SHOCK, "5个shock", 5, 30, GoodsType::ITEM, PriceType::COIN }, { GoodID::BOMB, "5个bomb", 5, 10, GoodsType::ITEM, PriceType::COIN }, { GoodID::CRAZY, "5个crazy", 5, 50, GoodsType::ITEM, PriceType::COIN } ,
	{ GoodID::GOLD, "100", 100, 6, GoodsType::IOSMONEY, PriceType::RMB }, { GoodID::GOLD, "220", 220, 12, GoodsType::IOSMONEY, PriceType::RMB },
	{ GoodID::GOLD, "600", 600, 30, GoodsType::IOSMONEY, PriceType::RMB }, { GoodID::GOLD, "2000", 2000, 88, GoodsType::IOSMONEY, PriceType::RMB }, { GoodID::GOLD, "16200", 16200, 648, GoodsType::IOSMONEY, PriceType::RMB }};
	const std::string Shop::TABLE_SHOP = "goods";
	Shop* Shop::_instance = nullptr;

	Shop::Shop(){
		this->init();
	}
	Shop::~Shop(){

	}
	Shop* Shop::getInstance(){
		if (!_instance){
			_instance = new Shop();
		}
		return _instance;
	}
	void Shop::init(){
		bool res;
		_db = DBConnector::getInstance()->open();
		std::stringstream sql;
		res = _db->exist(Shop::TABLE_SHOP);
		if (!res){
			res = _db->query(Table::getInstance()->getTableByName(Shop::TABLE_SHOP));
		}
		sql << "SELECT COUNT(*) AS `num` FROM `" << Shop::TABLE_SHOP << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0)
		{
			for (int i = 0; i < 12; i++)
			{
				sql.clear();
				sql.str("");
				sql << "REPLACE INTO `" << Shop::TABLE_SHOP << "` (`goodid`,`name`,`num`, `price`,`goodtype`,`pricetype`) VALUES ('" << Shop::DEFAULT_DATA[i].goodid << "','" << Shop::DEFAULT_DATA[i].name.c_str() << "','" << Shop::DEFAULT_DATA[i].num << "','" << Shop::DEFAULT_DATA[i].price << "','" << Shop::DEFAULT_DATA[i].goodtype << "','" << Shop::DEFAULT_DATA[i].pricetype << "')";
				res = _db->query(sql.str());
			}
		}
	}

	std::vector<UMGDBRow> Shop::getGoodsByType(int i)
	{
		std::stringstream sql;
		sql.clear();
		sql.str("");
		sql << "SELECT * FROM `" << Shop::TABLE_SHOP << "` WHERE `goodtype` = " << i << "";
		return _db->getAll(sql.str());
	}

	UMGDBRow Shop::getGoodById(int i)
	{
		std::stringstream sql;
		sql.clear();
		sql.str("");
		sql << "SELECT * FROM `" << Shop::TABLE_SHOP << "` WHERE `gid` = " << i << "";
		return _db->getRow(sql.str());
	}
}