/****************************************************************************
*	@       	       
*	@desc	游戏数据
*	@date	2014-10-29
*	@author	110101
*	@       	       
*	@file	data/Game.cpp
*	@modify	null
******************************************************************************/

#include "Game.h"

USING_NS_CC;

namespace data{
	const std::string Game::SCORE_CHANGE = "userScoreChange";
	const std::string Game::STAGE_CHANGE = "userStageChange";
	const std::string Game::TIME_CHANGE = "userTimeChange";
	const UserGameInfo Game::DEFAULT_USER_GAME_DATA = { 1, 0, 61,false,false };
	Game* Game::_instance = nullptr;
	Game::Game(){
		this->init();
	}
	Game::~Game(){
	}
	void Game::init(){
		bool res;
		_uid = User::getInstance()->getUID();
		_db = DBConnector::getInstance()->open();
		Table* table = Table::getInstance();
		if (!_db->exist(GAME_SAVE_TABLE)) _db->query(table->getTableByName(GAME_SAVE_TABLE));
		if (!_db->exist(GAME_FISH_TABLE)) _db->query(table->getTableByName(GAME_FISH_TABLE));
		_db->upgrade(USER_GAME_TABLE, table->getTableByName(USER_GAME_TABLE));
		_db->upgrade(USER_GAME_LOG_TABLE, table->getTableByName(USER_GAME_LOG_TABLE));
	}
	Game* Game::getInstance(){
		if (!_instance){
			_instance = new Game();
		}
		return _instance;
	}
	UMGDBRow Game::getUserGame(){
		bool res;
		std::stringstream sql;
		sql << "SELECT COUNT(*) AS `num` FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0){
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << USER_GAME_TABLE << "` (`uid`, `stage`, `score`, `time`,`useTimeItem`,`useRage`) VALUES ('" << _uid << "','" << DEFAULT_USER_GAME_DATA.stage << "','" << DEFAULT_USER_GAME_DATA.score << "','" << DEFAULT_USER_GAME_DATA.time << "','"<<DEFAULT_USER_GAME_DATA.useitem<<"','"<<DEFAULT_USER_GAME_DATA.useRage<<"')";
			res = _db->query(sql.str());
			//addUserGameLog();
		}
		sql.str("");
		sql.clear();
		sql << "SELECT * FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		int stage = row["stage"].asInt();
		int score = row["score"].asInt();
		int time = row["time"].asInt();

		return row;
	}
	bool Game::isUseTimeItem()
	{
		bool res;
		std::stringstream sql;
		sql << "SELECT COUNT(*) AS `num` FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0){
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << USER_GAME_TABLE << "` (`uid`, `stage`, `score`, `time`) VALUES ('" << _uid << "','" << DEFAULT_USER_GAME_DATA.stage << "','" << DEFAULT_USER_GAME_DATA.score << "','" << DEFAULT_USER_GAME_DATA.time << "')";
			res = _db->query(sql.str());
			//addUserGameLog();
		}
		sql.str("");
		sql.clear();
		sql << "SELECT * FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool item = row["useTimeItem"].asBool();
		return item;
	}
	UMGDBRow Game::getUserGame(int id){
		std::stringstream sql;
		UMGDBRow row;
		if (id <= 0){
			sql << "SELECT `stage` FROM `" << USER_GAME_LOG_TABLE << "` ORDER BY `id` DESC LIMIT 1";
			int stageFromLog = _db->getOne(sql.str()).asInt();
			sql.clear();
			sql.str("");
			sql << "SELECT `stage` FROM `" << USER_GAME_TABLE << "` LIMIT 1";
			int stageFromNow = _db->getOne(sql.str()).asInt();
			sql.clear();
			sql.str("");
			int page =  stageFromLog == stageFromNow ? 0 : 1;

			sql << "SELECT * FROM `" << USER_GAME_LOG_TABLE << "` ORDER BY `id` DESC LIMIT " << page << ", 1";
		}
		else{
			sql << "SELECT * FROM `" << GAME_SAVE_TABLE << "` WHERE `id`=" << id << " LIMIT 1";
		}
		row = _db->getRow(sql.str());
		if (!row.isEmpty()){
			setScore(row["score"].asInt());
			setStage(row["stage"].asInt());
			setTime(DEFAULT_USER_GAME_DATA.time);
			sql.clear();
			clearFish();
		}
		return this->getUserGame();
	}


	void Game::addUserGameLog(){
		std::stringstream sql;
		UMGDBRow row = getUserGame();
		sql << "REPLACE INTO `" << USER_GAME_LOG_TABLE << "` (`user_game_id`, `stage`, `score`, `time`) VALUES ('" << row["id"].asInt() << "', '" << row["stage"].asInt() << "', '" << row["score"].asInt() << "', '" << time(NULL) << "' )";
		bool res = _db->query(sql.str());
	}
	void Game::clearUserGame(){
		std::stringstream sql;
		sql << "DELETE FROM `" << USER_GAME_TABLE << "`";
		bool res = _db->query(sql.str());
		sql.clear();
		clearFish();
	}
	


	void Game::userGameInit(){
		UMGDBRow row = getUserGame();
		int stage = row["stage"].asInt();
		int score = row["score"].asInt();
		int time =  row["time"].asInt();
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::STAGE_CHANGE, &stage);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::SCORE_CHANGE, &score);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::TIME_CHANGE, &time);
	}
	void Game::setStage(int stage){
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `stage`=" << stage << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		sql.clear();
		int param = stage;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::STAGE_CHANGE, &param);
	}
	void Game::stageClear(){
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `stage`=`stage` + 1, `time`=" << DEFAULT_USER_GAME_DATA.time << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		addUserGameLog();
		sql.clear();
		clearFish();
	}
	void Game::setTime(int time)
	{
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `time`=" << time << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		sql.clear();
		int param = time;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::TIME_CHANGE, &param);
	}
	void Game::setUseTimeItem(bool item)
	{
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `useTimeItem`=" << item << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		sql.clear();
	}
	void Game::setScore(int score){
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `score`=" << score << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		sql.clear();
		int param = score;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::SCORE_CHANGE, &param);
	}
	std::vector<UMGDBRow> Game::getFishes(){
		std::stringstream sql;
		sql << "SELECT * FROM `" << GAME_FISH_TABLE << "` LIMIT 20";
		return _db->getAll(sql.str());
	}
	int Game::addFish(int type, int x, int y, std::string award){
		std::stringstream sql;
		sql << "INSERT INTO " << GAME_FISH_TABLE << " (`type`, `x`, `y`,`award`, `time`)  VALUES ( " << type << ", " << x << ", " << y << ", '" << award << "', " << time(NULL) << ")";
		int res = _db->query(sql.str());
		sql.clear();
		return _db->insertID();
	}
	int Game::addFish(){
		int type = 1;
		int x = 0;
		int y = 0;
		return this->addFish(type, x, y);
	}
	void Game::delFish(int id){
		std::stringstream sql;
		sql << "DELETE FROM `" << GAME_FISH_TABLE << "` WHERE `id`=" << id << " ";
		int res = _db->query(sql.str());
	}
	void Game::clearFish(){
		std::stringstream sql;
		sql << "DROP TABLE `" << GAME_FISH_TABLE << "`";
		int res = _db->query(sql.str());
		sql.clear();
		Table* table = new Table();
		res = _db->query(table->getTableByName(GAME_FISH_TABLE));
	}
	std::vector<UMGDBRow> Game::getGameSaves(){
		std::stringstream sql;
		sql << "SELECT * FROM `" << GAME_SAVE_TABLE << "` ORDER BY `id` ASC LIMIT 10";
		return _db->getAll(sql.str());
	}
	void Game::addGameSave(int stage, int score){
		std::stringstream sql;
		sql << "INSERT INTO " << GAME_SAVE_TABLE << " (`uid`, `stage`, `score`, `date`)  VALUES ( " << _uid << ", " << stage << ", " << score << ", '" << getDate(NULL) << "')";
		int res = _db->query(sql.str());
		sql.clear();
	}
	void Game::addGameSave(){
		UMGDBRow row = getUserGame();
		this->addGameSave(row["stage"].asInt(), row["score"].asInt());
	}
	void Game::modifyGameSave(int id, int stage, int score){
		std::stringstream sql;
		sql << "UPDATE " << GAME_SAVE_TABLE << " SET `stage`=" << stage << ", `score`=" << score << " WHERE `id`=" << id << " ";
		int res = _db->query(sql.str());
		sql.clear();
	}
	void Game::modifyGameSave(int id){
		UMGDBRow row = getUserGame();
		this->modifyGameSave(id, row["stage"].asInt(), row["score"].asInt());
	}
	std::string Game::getDate(time_t timestamp){
		bool res;
		char now[64];
		time_t t = time(&timestamp);
		struct tm *ttime;
		ttime = localtime(&t);
		strftime(now, 64, "%Y-%m-%d %H:%M:%S", ttime);
		std::string date(now);
		return date;
	}

	int Game::getTotleScore()
	{
		int totlescore = 0;
		UMGDBRow row = _instance->getUserGame();
		int stage = row["stage"].asInt();
		if (stage == 1)
		{
			totlescore = 100;
		}
		else
		{
            //           即对 40*(N*N-2*N+4) 进行向上取整到百位
            
//            totlescore = 100 * (stage*stage - 2 * stage + 4);
            int argument = 40 * (stage*stage - 2 * stage + 4);
            totlescore = 100 * (argument/100 + (((argument%100)>0)?1:0));
		}
		return totlescore;
	}
	void Game::scorePlus(int score)
	{
		std::stringstream sql;
		UMGDBRow row = getInstance()->getUserGame();
		int lasescore = row["score"].asInt();
		score = lasescore + score;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `score`=" << score << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());

		int param = score;
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(Game::SCORE_CHANGE, &param);
		sql.clear();
	}

	void Game::setUseRage(bool rage)
	{
		std::stringstream sql;
		sql << "UPDATE " << USER_GAME_TABLE << " SET `useRage`=" << rage << " WHERE `uid`=" << _uid << " ";
		int res = _db->query(sql.str());
		sql.clear();
	}

	bool Game::isUseRage()
	{
		bool res;
		std::stringstream sql;
		sql << "SELECT COUNT(*) AS `num` FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		int num = _db->getOne(sql.str()).asInt();
		if (num == 0){
			sql.clear();
			sql.str("");
			sql << "REPLACE INTO `" << USER_GAME_TABLE << "` (`uid`, `stage`, `score`, `time`) VALUES ('" << _uid << "','" << DEFAULT_USER_GAME_DATA.stage << "','" << DEFAULT_USER_GAME_DATA.score << "','" << DEFAULT_USER_GAME_DATA.time << "')";
			res = _db->query(sql.str());
			//addUserGameLog();
		}
		sql.str("");
		sql.clear();
		sql << "SELECT * FROM `" << USER_GAME_TABLE << "` LIMIT 1";
		UMGDBRow row = _db->getRow(sql.str());
		sql.clear();
		bool item = row["useRage"].asBool();
		return item;
	}
	void Game::cleatUserGameLog()
	{
		std::stringstream sql;
		sql << "DELETE FROM `" << USER_GAME_LOG_TABLE << "`";
		bool res = _db->query(sql.str());
		sql.clear();
	}
}