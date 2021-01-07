/****************************************************************************
*	@       	       
*	@desc	道具数据
*	@date	2014-10-30
*	@author	110101
*	@       	       
*	@file	data/Item.cpp
*	@modify	null
******************************************************************************/

#include "Item.h"
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
#include "MobClickCpp.h"
#else
#include "external/libMobClickCpp/include/MobClickCpp.h"
#endif
USING_NS_CC;

namespace data{
	const std::string Item::ITEM_CHANGE = "userItemChange";;
	Item* Item::_instance = nullptr;
	Item::Item(){
		this->init();
	}
	Item::~Item(){

	}
	void Item::init(){
		bool res;
		_uid = User::getInstance()->getUID();
		_db = DBConnector::getInstance()->open();
		Table* table = Table::getInstance();
		if (!_db->exist(USER_ITEM_TABLE)) _db->query(table->getTableByName(USER_ITEM_TABLE));
		if (!_db->exist(USER_ITEM_LOG_TABLE)) _db->query(table->getTableByName(USER_ITEM_LOG_TABLE));
	}
	Item* Item::getInstance(){
		if (!_instance){
			_instance = new Item();
		}
		return _instance;
	}
	std::vector<ItemInfo> Item::getItems(){
		if (_items.size() == 0){
			_items.push_back({ Item::ITEM_SHOCK_ID, "shock" });
			_items.push_back({ Item::ITEM_BOMB_ID, "bomb" });
			_items.push_back({ Item::ITEM_RAGE_ID, "rage" });
		}
		return _items;
	}
	ItemInfo Item::getItemByID(int id){
		ItemInfo item;
		for (std::vector<ItemInfo>::iterator it = _items.begin(); it != _items.end(); it++){
			item = *it;
			if (item.id == id){
				return item;
			}
		}
		return item;
	}
	std::vector<UMGDBRow> Item::getUserItems(){
		bool res;
		std::stringstream sql;
		sql << "SELECT * FROM `" << USER_ITEM_TABLE << "` ";
		std::vector<UMGDBRow> all = _db->getAll(sql.str());
		sql.clear();
		return all;
	}
	UMGDBRow Item::getUserItemNum(){
		std::vector<UMGDBRow> all = this->getUserItems();
		UMGDBRow res;
		for (std::vector<UMGDBRow>::iterator it = all.begin(); it != all.end(); it++){
			UMGDBRow row = *it;
			res.add(row["item_id"].asString(), row["num"]);
			UserItemInfo param = { row["item_id"].asInt(), row["num"].asInt() };
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Item::ITEM_CHANGE, &param);
		}
		return res;
	}
	UMGDBRow Item::getUserItemByItemID(int id){
		bool res;
		std::stringstream sql;
		sql << "SELECT * FROM `" << USER_ITEM_TABLE << "` WHERE `uid`=" << _uid << " AND `item_id`=" << id << " LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		return row;
	}
	int Item::getUserItemNumByItemID(int id){
		bool res;
		std::stringstream sql;
		sql << "SELECT COUNT(*) FROM `" << USER_ITEM_TABLE << "` WHERE `uid`=" << _uid << " AND `item_id`=" << id << " LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num > 0){
			sql.clear();
			sql.str("");
			sql << "SELECT `num` FROM `" << USER_ITEM_TABLE << "` WHERE `uid`=" << _uid << " AND `item_id`=" << id << " LIMIT 1";
			num = _db->getOne(sql.str()).asInt();
			sql.clear();
		}
		else
		{
			num = ItemNum;
			data::Item::getInstance()->add(id, num, data::Item::MethodType::SYSTEM);
		}
		return num;
	}
	void Item::add(int id, int num, int method){
		UMGDBRow row = this->getUserItemByItemID(id);
		UserItemInfo param = { id, num };
		std::stringstream sql;
		if (row.isEmpty()){
			sql << "INSERT INTO " << USER_ITEM_TABLE << " (`uid`, `item_id`, `num`, `date`)  VALUES ( " << _uid << ", " << id << ", " << num << ", '" << getDate() << "')";
		}
		else{
			param.num = row["num"].asInt() + num;
			sql << "UPDATE " << USER_ITEM_TABLE << " SET `num`  =`num` + " << num << ", `date`='" << getDate() << "' WHERE `uid`=" << _uid << " AND `item_id`=" << id << " ";
		}
		bool res = _db->query(sql.str());
		sql.clear();
		if (res){
			this->record(id, num, method);
		}
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Item::ITEM_CHANGE, &param);
	}
	void Item::use(int id){
// 		UMGDBRow row = this->getUserItemByItemID(id);
// 		if (row.isEmpty()) return;
// 		if (row["num"].asInt() == 0) return;
// 		std::stringstream sql;
// 		sql << "UPDATE " << USER_ITEM_TABLE << " SET `num` = `num` - 1 WHERE `uid` = " << _uid << " AND `item_id` = " << id << " ";
// 		bool res = _db->query(sql.str());
// 		sql.clear();
// 		if (res){
// 			this->record(id, 1, MethodType::USE);
// 		}
// 		UserItemInfo param = { id, row["num"].asInt() - 1 };
		//单价..
		int price;
		//道具数量..
		int amount = 1;
#if(CC_TARGET_PLATFORM==CC_PLATFORM_IOS)
		if (id == 1)
		{
			price = 6;
			umeng::MobClickCpp::use("shock", amount, price);
		}
		else if (id == 2)
		{
			price = 2;
			umeng::MobClickCpp::use("bomb", amount, price);
		}
		else if (id == 3)
		{
			price = 10;
			umeng::MobClickCpp::use("rage", amount, price);
		}

#endif
		if (id == 1)
		{
			User::getInstance()->goldPlus(-6);
		}
		else if (id == 2)
		{
			User::getInstance()->goldPlus(-2);
		}
		else if (id == 3)
		{
			User::getInstance()->goldPlus(-10);
		}
		//Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Item::ITEM_CHANGE, &param);
}
	void Item::record(int id, int num, int method){
		std::stringstream sql;
		sql << "INSERT INTO " << USER_ITEM_LOG_TABLE << " (`uid`, `item_id`, `num`, `method`, `date`)  VALUES ( " << _uid << ", " << id << ", " << num << ", " << method << ", '" << getDate() << "')";
		int res = _db->query(sql.str());
		sql.clear();
	}
	std::string Item::getDate(time_t timestamp){
		bool res;
		char now[64];
		time_t t = time(&timestamp);
		struct tm *ttime;
		ttime = localtime(&t);
		strftime(now, 64, "%Y-%m-%d %H:%M:%S", ttime);
		std::string date(now);
		return date;
	}
}