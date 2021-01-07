/****************************************************************************
*	@       	       
*	@desc	用户信息
*	@date	2014-09-26
*	@author	110101
*	@       	       
*	@file	data/User.cpp
*	@modify	2014-10-21 by 120101
******************************************************************************/

#include "User.h"

USING_NS_CC;

namespace data{
	const std::string User::GOLD_CHANGE = "userGoldChange";
    const std::string User::BUY_FIRST_CHARGE = "buy_first_charge_listen";
	const UserInfo User::DEFAULT_USER_DATA = { 1, "user", 50 };
	const std::string User::TABLE_USER = "user";
	const SettingInfo User::DEFAULT_SETTING_DATA = { 1, 1, 1, 1, 1, 1,true,true,true,true,true,true,true,true,true,true,true,false,true};
	const std::string User::TABLE_SETTING = "user_setting";
	const std::string User::USER_BOMBFISH_LOG_TABLE = "user_bombfish_log";
	User* User::_instance = nullptr;

	User::User(){
		this->init();
	}
	User::~User(){

	}
	User* User::getInstance(){
		if (!_instance){
			_instance = new User();
		}
		return _instance;
	}
	void User::init(){
		initUserData();
		initSettingData();
		UMGDBRow row = getUserData();
		_uid = row["uid"].asInt();
		setGold(row["gold"].asInt());
		setName(row["name"].asString());
		setDate();
		setBGM(row["bgm"].asBool());
		setSE(row["se"].asBool());
		setGuide(row["guide"].asInt());
		setFirst(row["first"].asBool());
		setLibao(row["libao"].asBool());


	}
	void User::initUserData(){
		bool res;
		_db = DBConnector::getInstance()->open();
		std::stringstream sql;
		res = _db->exist(User::TABLE_USER);
		if (!res){
			res = _db->query(Table::getInstance()->getTableByName(User::TABLE_USER.c_str()));
		}
		sql << "SELECT COUNT(*) AS `num` FROM `" << User::TABLE_USER.c_str() << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0){
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << User::TABLE_USER.c_str() << "` (`uid`, `name`, `gold`) VALUES ('" << User::DEFAULT_USER_DATA.uid << "','" << User::DEFAULT_USER_DATA.name.c_str() << "','" << User::DEFAULT_USER_DATA.gold << "')";
			res = _db->query(sql.str());
		}
	}

	void User::initSettingData(){
		bool res;
		_db = DBConnector::getInstance()->open();
		std::stringstream sql;
		res = _db->exist(User::TABLE_SETTING);
		if (!res){
			res = _db->query(Table::getInstance()->getTableByName(User::TABLE_SETTING.c_str()));
		}       
		sql << "SELECT COUNT(*) AS `num` FROM `" << User::TABLE_SETTING.c_str() << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0){
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << User::TABLE_SETTING.c_str() << "` (`uid`, `bgm`, `se`, `guide`, `first`, `libao`,`firstlevel`,`firstthress`,`firstfail`,`firstletter`,`firstfullletter`,`firstshing`,`firsttimeitem`,`firstbomb`,`SHOWBOMB`,`SHOWSHOCK`,`SHOWRAGE`,`adblock`,`endlesslock`) VALUES ('" << User::DEFAULT_SETTING_DATA.uid << "','" << User::DEFAULT_SETTING_DATA.bgm << "','" << User::DEFAULT_SETTING_DATA.se << "','" << User::DEFAULT_SETTING_DATA.guide << "','" << User::DEFAULT_SETTING_DATA.first << "','" << User::DEFAULT_SETTING_DATA.libao << "','" << User::DEFAULT_SETTING_DATA.firstlevel << "','" << User::DEFAULT_SETTING_DATA.firstthress << "','" << User::DEFAULT_SETTING_DATA.firstfail << "','" << User::DEFAULT_SETTING_DATA.firstletter << "','" << User::DEFAULT_SETTING_DATA.firstfullletter << "','" << User::DEFAULT_SETTING_DATA.firstshing << "','" << User::DEFAULT_SETTING_DATA.firsttimeitem << "','" << User::DEFAULT_SETTING_DATA.firstbomb << "','" << User::DEFAULT_SETTING_DATA.showbomb << "','" << User::DEFAULT_SETTING_DATA.showshock << "','" << User::DEFAULT_SETTING_DATA.showrage << "','" << User::DEFAULT_SETTING_DATA.adblock << "','" << User::DEFAULT_SETTING_DATA.endlesslock << "')";
			res = _db->query(sql.str());
		}
	}

	UMGDBRow User::getUserData(){
		std::stringstream sql;
		sql << "SELECT * FROM `" << User::TABLE_USER.c_str() << "` `u` , `" << User::TABLE_SETTING.c_str() << "` `s` WHERE `u`.uid = `s`.uid";
		return _db->getRow(sql.str());
	}

	void User::setGold(int gold){
		_gold = gold;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_USER.c_str() << "` SET `gold`='" << gold << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
		res = _db->query(sql.str());
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(User::GOLD_CHANGE, &gold);
	}
	void User::getUserInit()
	{
		int row = getGold();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(User::GOLD_CHANGE, &row);
	}
	int User::getGold(){
		return _gold;
	}
	bool User::goldPlus(int num){
		int gold = _gold + num;
		if (gold < 0) return false;
		this->setGold(gold);
		return true;
	}
	bool User::goldReduce(unsigned num){
		int gold = _gold - num;
		if (gold < 0) return false;
		this->setGold(gold);
		return true;
	}
	void User::setName(std::string name){
		_name = name;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_USER.c_str() << "` SET `name`='" << name << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
		res = _db->query(sql.str());
	}
	std::string User::getName(){
		return _name;
	}
	int User::getUID(){
		return _uid;
	}
	void User::setDate(time_t timestamp){
		bool res;
		char now[64];
		time_t t = time(&timestamp);
		struct tm *ttime;
		ttime = localtime(&t);
		strftime(now, 64, "%Y-%m-%d %H:%M:%S", ttime);
		std::string date;
		date = { now };
		this->setDate(date);
	}
	void User::setDate(std::string date){
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_USER.c_str() << "` SET `date`='" << date.c_str() << "' WHERE `uid`=" << User::DEFAULT_USER_DATA.uid;
		bool res = _db->query(sql.str());
	}
	void User::setDate(){
		this->setDate(NULL);
	}
	std::string User::getDate(){
		std::stringstream sql;
		sql << "SELECT `date` FROM " << User::TABLE_USER.c_str() << "` WHERE `uid`=" << User::DEFAULT_USER_DATA.uid << " LIMIT 1";
		std::string date = _db->getOne(sql.str()).asString();
		return date;
	}

	void User::setBGM(bool bgm){
		_bgm = bgm;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `bgm`='" << (int)bgm << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getBGM(){
		return _bgm;
	}

	void User::setSE(bool se){
		_se = se;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `se`='" << (int)se << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getSE(){
		return _se;
	}

	void User::setSoundEffect(bool valid){
		_se = valid;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `se`='" << (int)_se << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}
	bool User::getSoundEffect(){
		return _se;
	}

	void User::setGuide(int guide){
		_guide = guide;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `guide`='" << (int)guide << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}
	int User::getGuide(){
		return _guide;
	}

	void User::setFirst(bool first){
		_first = first;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `first`='" << (int)first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}
	bool User::getFirst(){
		return _first;
	}

	void User::setLibao(bool libao){
		_libao = libao;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `libao`='" << (int)libao << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}
	bool User::getLibao(){
		return _libao;
	}

	void User::addUserBombFishLog()
	{
		bool res;
		_db = DBConnector::getInstance()->open();
		std::stringstream sql;
		res = _db->exist(User::USER_BOMBFISH_LOG_TABLE);
		if (!res){
			res = _db->query(Table::getInstance()->getTableByName(User::USER_BOMBFISH_LOG_TABLE));
		}

		sql << "REPLACE INTO `" << User::USER_BOMBFISH_LOG_TABLE << "` (`game_id`,`num`,`time`) VALUES ('" << _uid << "','" << 1 << "','" << getTimeDate() << "')";
		res = _db->query(sql.str());
	}
	std::string User::getTimeDate(time_t timestamp){
		bool res;
		char now[64];
		time_t t = time(&timestamp);
		struct tm *ttime;
		ttime = localtime(&t);
		strftime(now, 64, "%Y-%m-%d %H:%M:%S", ttime);
		std::string date(now);
		return date;
	}
	void User::clearBombFishLog()
	{
		std::stringstream sql;
		sql << "DELETE FROM `" << USER_BOMBFISH_LOG_TABLE << "`";
		bool res = _db->query(sql.str());
		sql.clear();
	}

	bool User::getFirstLevel()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstlevel"].asBool();
		return first;
	}
	void User::setFirstLevel(bool first)
	{
		_firstlevel = first;
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstlevel`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstFail(bool first)
	{

		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstfail`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstTimeItem(bool first)
	{

		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firsttimeitem`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstLetter(bool first)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstletter`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstFullLetter(bool first)
	{
	
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstfullletter`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstShing(bool first)
	{
	
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstshing`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setFirstThress(bool first)
	{
		
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstthress`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getFirstFail()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstfail"].asBool();
		return first;
	}

	bool User::getFirstTimeItem()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firsttimeitem"].asBool();
		return first;
	}

	bool User::getFirstLetter()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstletter"].asBool();
		return first;
	}

	bool User::getFirstFullLetter()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstfullletter"].asBool();
		return first;
	}

	bool User::getFirstShing()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstshing"].asBool();
		return first;
	}

	bool User::getFirstThress()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstthress"].asBool();
		return first;
	}

	void User::setFirstBomb(bool first)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `firstbomb`='" << first << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getFirstBomb()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["firstbomb"].asBool();
		return first;
	}

	void User::setShowBomb(bool b)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `SHOWBOMB`='" << b << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setShowShock(bool b)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `SHOWSHOCK`='" << b << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	void User::setShowRage(bool b)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `SHOWRAGE`='" << b << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getShowShock()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["SHOWSHOCK"].asBool();
		return first;
	}

	bool User::getShowBomb()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["SHOWBOMB"].asBool();
		return first;
	}
	bool User::getShowRage()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["SHOWRAGE"].asBool();
		return first;
	}

	void User::setAdblock(bool b)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `adblock`='" << b << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
	}

	bool User::getAdblock()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["adblock"].asBool();
		return first;
	}

	void User::setEndlesslock(bool b)
	{
		bool res;
		std::stringstream sql;
		sql << "UPDATE `" << User::TABLE_SETTING.c_str() << "` SET `endlesslock`='" << b << "' WHERE `uid`=" << User::DEFAULT_SETTING_DATA.uid;
		res = _db->query(sql.str());
        
	}

	bool User::getEndlesslock()
	{
		std::stringstream sql;
		sql.clear();
		sql << "SELECT * FROM `" << TABLE_SETTING.c_str() << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool first = row["endlesslock"].asBool();
		return first;
	}

}