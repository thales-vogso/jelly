/****************************************************************************
*	@       	       
*	@desc	数据表
*	@date	2014-10-14
*	@author	110101
*	@       	       
*	@file	db/Table.h
*	@modify	null
******************************************************************************/

#ifndef __DB_TABLE_H__
#define __DB_TABLE_H__

#include "cocos2d.h"

class Table {
public:
	/**
	 *	初始化
	 */
	Table();
	/**
	 *	析构函数，要清除有指针的内容
	 */
	virtual ~Table();
	/**
	 *	设置xml文件
	 */
	void setXml(std::string xmlName);
	/**
	 *	获取实体
	 */
	static Table* getInstance();
	/**
	 *	通过表名获取表
	 *	@param	name	表名
	 *	@return	建表的sql语句
	 */
	std::string getTableByName(std::string name);

	static const std::string XML_NAME;
	
private:
	/**
	 *	自身
	 */
	static Table* _instance;
	/**
	 *	sqlmap
	 */
	cocos2d::ValueMap _sqlMap;
};

#endif // __DB_TABLE_H__
