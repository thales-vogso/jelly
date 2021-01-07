/****************************************************************************
*	@       	       
*	@desc	数据表
*	@date	2014-10-14
*	@author	110101
*	@       	       
*	@file	db/Table.cpp
*	@modify	null
******************************************************************************/

#include "Table.h"

USING_NS_CC;

const std::string Table::XML_NAME = "sql.xml";
Table* Table::_instance = nullptr;

Table::Table(){
}
Table::~Table(){

}
Table* Table::getInstance(){
	if (!_instance){
		_instance = new Table();
	}
	return _instance;
}
void Table::setXml(std::string xmlName){
	ValueVector sqlVec = FileUtils::getInstance()->getValueVectorFromFile(xmlName);
	_sqlMap = sqlVec.at(0).asValueMap();
}
std::string Table::getTableByName(std::string name){
	if (_sqlMap.size() == 0){
		this->setXml(Table::XML_NAME);
	}
	std::string a = _sqlMap.at(name.c_str()).asString();
	return _sqlMap.at(name.c_str()).asString();
}