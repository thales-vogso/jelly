/****************************************************************************
*	@       	       
*	@desc	数据库
*	@date	2014-10-10
*	@author	110101
*	@       	       
*	@file	popstar/Classes/db/DBSqlite.h
*	@modify	null
******************************************************************************/
#ifndef __DB_SQLITE_H__
#define __DB_SQLITE_H__

#include "cocos2d.h"
#include "sqlite3.h"

/**
 *	数据列
 *	@param	value	值
 *	@param	()	重构，赋值
 */
typedef struct umgameDBColTag{
	std::string value;
	bool isEmpty(){
		return value.empty();
	};
	void operator()(std::string v){
		value = v;
	};
	std::string asString(){
		return value;
	};
	int asInt(){
		return std::atoi(value.c_str());
	};
	float asFloat(){
		return std::atof(value.c_str());
	};
	bool asBool(){
		return (bool)asInt();
	};
}UMGDBColumn;
/**
 *	数据行
 *	@param	key	键
 *	@param	value	值
 *	@param	[]	重构，根据索引或者key返回value
 */
typedef struct umgameDBRowTag{
	std::vector<std::string> key;
	std::vector<UMGDBColumn> value;
	bool isEmpty(){
		return value.empty();
	};
	UMGDBColumn operator[](int k){
		return value.at(k);
	};
	UMGDBColumn operator[](std::string k){
		int i, size = (int)key.size();
		for (i = 0; i < size; i++){
			if (key.at(i) == k){
				return value.at(i);
			}
		}
		return value.at(0);
	};
	void add(std::string k, UMGDBColumn v){
		int i, size = (int)key.size();
		for (i = 0; i < size; i++){
			if (key.at(i) == k){
				value.at(i) = v;
				return;
			}
		}
		key.push_back(k);
		value.push_back(v);
	}
}UMGDBRow;

class DBSqlite {
public:
	/**
	 *	构造
	 */
	DBSqlite();
	DBSqlite(std::string dbName);
	/**
	 *	析构函数，要清除有指针的内容
	 */
	virtual ~DBSqlite();
	/**
	 *	初始化
	 */
	void init();
	/**
	 *	设置数据库
	 *	@param	dbName	数据库名字
	 */
	bool setDB(std::string dbName);
	bool setDB();
	/**
	 *	判断表存在
	 *	@param	tableName	表名
	 */
	bool exist(std::string tableName);
	/**
	 *	升级表
	 */
	void upgrade(std::string tableName, std::string tableSql);
	/**
	 *	执行sql
	 *	@param	sql
	 *	@return	执行结果
	 */
	bool query(std::string sql);
	/**
	 *	获取刚刚插入的id
	 */
	int insertID();
	/**
	 *	获取单独数据
	 *	@param	sql	
	 *	@return	返回数据
	 */
	UMGDBColumn getOne(std::string sql);
	/**
	 *	获取一行数据
	 *	@param	sql
	 *	@return	返回数据
	 */
	UMGDBRow getRow(std::string sql);
	/**
	 *	获取数组数据
	 *	@param	sql
	 *	@return	返回数据
	 */
	std::vector<UMGDBRow> getAll(std::string sql);
	/**
	 *	数据库名字
	 */
	static const std::string DB_NAME;

	/**
	 *	数据库错误
	 */
	static const std::string DB_ERR;
	/**
	 *	数据库执行错误
	 */
	static const std::string DB_QUERY_ERR;
	/**
	 *	数据库查询错误
	 */
	static const std::string DB_SELECT_ERR;
private:
	/**
	 *	数据库
	 */
	sqlite3* _pdb = NULL;
	/**
	 *	数据库名
	 */
	std::string dbName;
	/**
	 *	对比两个sql
	 */
	bool compareSql(std::string oldSql, std::string newSql);
};

#endif // __DB_SQLITE_H__
