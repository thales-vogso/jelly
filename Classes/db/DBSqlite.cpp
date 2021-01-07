/****************************************************************************
*	@       	       
*	@desc	数据库
*	@date	2014-10-10
*	@author	110101
*	@       	       
*	@file	popstar/Classes/db/DBSqlite.cpp
*	@modify	null
******************************************************************************/

#include "DBSqlite.h"

USING_NS_CC;

const std::string DBSqlite::DB_NAME = "save.db";
const std::string DBSqlite::DB_ERR = "databaseError";

DBSqlite::DBSqlite(){
	
}
DBSqlite::DBSqlite(std::string dbName){
	this->setDB(dbName);
}
DBSqlite::~DBSqlite(){

}
bool DBSqlite::setDB(std::string dbName){
	std::string path = FileUtils::getInstance()->getWritablePath() + dbName;
	char* errMsg;
	int res = sqlite3_open(path.c_str(), &_pdb);
	if (res != SQLITE_OK){
		CCLOG("open database failed,  number%d", res);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(DBSqlite::DB_ERR, &res);
		return false;
	}
	return true;
}
bool DBSqlite::setDB(){
	return this->setDB(DBSqlite::DB_NAME);
}
int isExisted(void * para, int n_column, char ** column_value, char ** column_name)
{
	bool *isExisted_ = (bool*)para;
	*isExisted_ = (**column_value) != '0';
	return 0;
}
bool DBSqlite::exist(std::string tableName){
	bool tableIsExisted;
	char* errMsg;
	std::stringstream sql;
	sql << "select count(type) from sqlite_master where type='table' and name ='" << tableName << "'";
	int res = sqlite3_exec(_pdb, sql.str().c_str(), isExisted, &tableIsExisted, &errMsg);
	return tableIsExisted;
}
void DBSqlite::upgrade(std::string tableName, std::string tableSql){
	std::stringstream sql;
	bool res = false;
	sql << "SELECT TRIM(GROUP_CONCAT(sql, ';')) AS `sql` FROM `sqlite_master` WHERE `tbl_name` = '" << tableName << "' ORDER BY type='index', type='table' LIMIT 1";
	UMGDBColumn one = getOne(sql.str());
	std::string oldSql = one.asString();
	std::string newSql = tableSql;
	if (oldSql == ""){
		query(tableSql);
		return;
	}
	if (!compareSql(oldSql, newSql)){
		sql.clear();
		sql.str("");
		sql << "SELECT * FROM `" << tableName << "` LIMIT 100";
		std::vector<UMGDBRow> all = getAll(sql.str());
		sql.clear();
		sql.str("");
		sql << "DROP TABLE `" << tableName << "`";
		res = query(sql.str());
		res = query(newSql);
		for (UMGDBRow row : all){
			sql.clear();
			sql.str("");
			std::stringstream keys;
			std::stringstream values;
			bool first = true;
			for (std::string key : row.key){
				if (first){
					first = false;
				}
				else{
					keys << ",";
					values << ",";
				}
				keys << "`" << key << "`";
				values << "'" << row[key].asString() << "'";
			}
			sql << "INSERT INTO`" << tableName << "` (" << keys.str() << ") VALUES (" << values.str() << ")";
			res = query(sql.str());
		}
		CCLOG("upgrade success");
	}
	sql.clear();
	sql.str("");
}
bool DBSqlite::query(std::string sql){
	char* errMsg;
	int res = sqlite3_exec(_pdb, sql.c_str(), NULL, NULL, &errMsg);
	if (res != SQLITE_OK){
		CCLOG("query failed, number:%d, msg:%s, sql:%s", res, errMsg, sql.c_str());
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(DBSqlite::DB_ERR, &res);
		return false;
	}
	return true;
}
int DBSqlite::insertID(){
	std::string sql = "select last_insert_rowid()";
	int id = this->getOne(sql).asInt();
	return id;
}
std::vector<UMGDBRow> DBSqlite::getAll(std::string sql){
	char **re;
	int r, c, res;
	char* errMsg;
	std::vector<UMGDBRow> all;
	res = sqlite3_get_table(_pdb, sql.c_str(), &re, &r, &c, &errMsg);
	if (res != SQLITE_OK){
		CCLOG("select table all failed, number:%d, msg:%s", res, errMsg);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(DBSqlite::DB_ERR, &res);
		return all;
	}
	int i, j;
	for (i = 1; i <= r; i++){
		UMGDBRow row;
		for (j = 0; j<c; j++){
			std::string k(re[j]);
			UMGDBColumn v;
			v(re[i*c + j]);
			row.add(k, v);
		}
		all.push_back(row);
	}
	sqlite3_free_table(re);
	return all;
}
UMGDBRow DBSqlite::getRow(std::string sql){
	char **re;
	int r, c, res;
	char* errMsg;
	UMGDBRow row;
	res = sqlite3_get_table(_pdb, sql.c_str(), &re, &r, &c, &errMsg);
	if (res != SQLITE_OK){
		CCLOG("select table row failed, number:%d, msg:%s", res, errMsg);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(DBSqlite::DB_ERR, &res);
		return row;
	}
	for (int j = 0; j<c; j++){
		std::string k(re[j]);
		UMGDBColumn v;
		v(re[c + j]);
		row.add(k, v);
	}
	return row;
}
UMGDBColumn DBSqlite::getOne(std::string sql){
	char **re;
	int r, c, res;
	char* errMsg;
	res = sqlite3_get_table(_pdb, sql.c_str(), &re, &r, &c, &errMsg);
	UMGDBColumn colmun;
	if (res != SQLITE_OK){
		CCLOG("select table one failed, number:%d, msg:%s", res, errMsg);
		Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(DBSqlite::DB_ERR, &res);
		return colmun;
	}
	if (r > 0 && c > 0){
		if(re[1])
			colmun(re[1]);
		else
			colmun(""); re;
	}else{
		colmun("");
	}
	sqlite3_free_table(re);
	return colmun;
}
bool DBSqlite::compareSql(std::string oldSql, std::string newSql){
	const std::string blank = " \t\n\r\v\f";
	while (newSql.length()>0 && blank.find(newSql.at(0)) != std::string::npos)
		newSql.erase(0, 1);
	while (newSql.length()>0 && blank.find(newSql.at(newSql.length() - 1)) != std::string::npos)
		newSql.erase(newSql.length() - 1, 1);
	while (oldSql.length()>0 && blank.find(oldSql.at(0)) != std::string::npos)
		oldSql.erase(0, 1);
	while (oldSql.length()>0 && blank.find(oldSql.at(oldSql.length() - 1)) != std::string::npos)
		oldSql.erase(oldSql.length() - 1, 1);
	return oldSql == newSql;
}