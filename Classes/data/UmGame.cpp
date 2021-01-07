/****************************************************************************
*	@       	       
*	@desc	UmGame数据
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	data/UmGame.cpp
*	@modify	null
******************************************************************************/

#include "UmGame.h"

USING_NS_CC;

namespace data{
	const std::string UmGame::LETTER_CHANGE = "userLetterChange";
	const std::string UmGame::LETTER_DONE = "userLetterDone";
	const UmGameInfo UmGame::DEFAULT_DATA = {1,0,0,0,0,0};
	const std::string UmGame::TABLE_UMGAME = "umgame";
	UmGame* UmGame::_instance = nullptr;

	UmGame::UmGame(){
		this->init();
	}
	UmGame::~UmGame(){

	}
	UmGame* UmGame::getInstance(){
		if (!_instance){
			_instance = new UmGame();
		}
		return _instance;
	}
	void UmGame::init(){
		bool res;
		_db = DBConnector::getInstance()->open();
		std::stringstream sql;
		res = _db->exist(UmGame::TABLE_UMGAME);
		if (!res){
			res = _db->query(Table::getInstance()->getTableByName(UmGame::TABLE_UMGAME));
		}
		sql << "SELECT COUNT(*) AS `num` FROM `" << UmGame::TABLE_UMGAME << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0)
		{
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << UmGame::TABLE_UMGAME << "` (`uid`,`u`,`m`,`g`, `a`,`e`) VALUES ('" << User::DEFAULT_USER_DATA.uid << "','" << UmGame::DEFAULT_DATA.u << "','" << UmGame::DEFAULT_DATA.m << "','" << UmGame::DEFAULT_DATA.g << "','" << UmGame::DEFAULT_DATA.a << "','" << UmGame::DEFAULT_DATA.e << "')";
			res = _db->query(sql.str());
		}
	}

	UMGDBRow UmGame::getUmGame()
	{
		std::stringstream sql;
		sql.clear();
		sql.str("");
		sql << "SELECT * FROM `" << UmGame::TABLE_UMGAME << "` WHERE `uid`=" << User::DEFAULT_USER_DATA.uid << " LIMIT 1";
		return _db->getRow(sql.str());
	}

	void UmGame::addLetter(std::string str)
	{
		if (str == "M")
		{
			std::stringstream sql;
			sql.clear();
			sql.str("");
			sql << "SELECT `m` FROM `" << UmGame::TABLE_UMGAME.c_str() << "` WHERE `uid`=" << User::DEFAULT_USER_DATA.uid << " LIMIT 1";
			int num = _db->getOne(sql.str()).asInt();
			if (num == 1)
			{
				bool res;
				std::stringstream sql;
				sql << "UPDATE `" << UmGame::TABLE_UMGAME.c_str() << "` SET `" << str.c_str() << "`='" << 2 << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
				res = _db->query(sql.str());
			}
			else if (num == 0)
			{
				bool res;
				std::stringstream sql;
				sql << "UPDATE `" << UmGame::TABLE_UMGAME.c_str() << "` SET `" << str.c_str() << "`='" << 1 << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
				res = _db->query(sql.str());
			}
		}
		else
		{
			bool res;
			std::stringstream sql;
			sql << "UPDATE `" << UmGame::TABLE_UMGAME.c_str() << "` SET `" << str.c_str() << "`='" << 1 << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
			res = _db->query(sql.str());
		}		
		//判断是否集满并清空
		UMGDBRow umgame = data::UmGame::getInstance()->getUmGame();
		if (umgame["u"].asInt() == 1 && umgame["m"].asInt() == 2 && umgame["g"].asInt() == 1 && umgame["a"].asInt() == 1 && umgame["e"].asInt() == 1)
		{

			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(UmGame::LETTER_DONE, this);
			bool res;
			std::stringstream sql;
			sql << "UPDATE `" << UmGame::TABLE_UMGAME << "` SET u = 0 ,m = 0 ,g = 0 , a = 0 , e = 0 " << " WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
			res = _db->query(sql.str());
		}
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(UmGame::LETTER_CHANGE, this);
	}
}