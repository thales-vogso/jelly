/****************************************************************************
*	@       	       
*	@desc	UmGame数据
*	@date	2014-11-6
*	@author	120101
*	@       	       
*	@file	data/UmGame.h
*	@modify	null
******************************************************************************/
#ifndef __DATA_UMGAME_H__
#define __DATA_UMGAME_H__

#include "cocos2d.h"
#include "db/DBConnector.h"
#include "db/Table.h"
#include "data/User.h"

namespace data{
	/**
	 *	设置数据信息
	 */
	typedef struct umgameTag{
		int uid;
		int u;
		int m;
		int g;
		int a;
		int e;
	}UmGameInfo;

	class UmGame {
	public:
		/**
		 *	初始化
		 */
		UmGame();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~UmGame();
		/**
		 *	获取实体
		 */
		static UmGame* getInstance();
		/**
		 *	初始化
		 */
		void init();
		/**
		 *	获取UMGAME
		 *	@return UMGAME容器
		 */
		UMGDBRow getUmGame();
		/**
		*	增加Letter
		*	@参数 Letter枚举
		*/
		void addLetter(int letter);
		/**
		*	增加Letter
		*	@参数 字母
		*/
		void addLetter(std::string letter);
		/**
		 *	金币商店默认信息
		 */
		static const UmGameInfo DEFAULT_DATA;
		/**
		 *	数据表-金币商店
		 */
		static const std::string TABLE_UMGAME;
		/**
		*	字母改变事件
		*/
		static const std::string LETTER_CHANGE;
		/**
		*	字母收集完成事件
		*/
		static const std::string LETTER_DONE;

	private:
		/**
		 *	自身
		 */
		static UmGame* _instance;
		/**
		 *	数据库
		 */
		DBSqlite* _db;
		/**
		*	通过枚举获取字符串名称
		*/
		std::string getLetterStr(int letter);
	};
}
#endif // __DATA_IMGAME_H__
