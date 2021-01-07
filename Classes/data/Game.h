/****************************************************************************
*	@       	       
*	@desc	游戏数据
*	@date	2014-10-29
*	@author	110101
*	@       	       
*	@file	data/Game.h
*	@modify	null
******************************************************************************/
#ifndef __DATA_GAME_H__
#define __DATA_GAME_H__

#include "cocos2d.h"
#include "db/DBSqlite.h"
#include "db/Table.h"
#include "User.h"

namespace data{
	/**
	*	用户信息
	*/
	typedef struct UserGameInfoTag{
		int stage;	//关卡
		int score;	//分数
		int time;	//剩余时间
		bool useitem;
		bool useRage;
	}UserGameInfo;
	class Game {
	public:

		/**
		 *	初始化
		 */
		Game();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~Game();
		/*
		*	获取每关的目标分数
		*/
		static int getTotleScore();

		/**
		 *	初始化
		 */
		void init();
		/**
		 *	获取实体
		 */
		static Game* getInstance();
		/**
		 *	获取用户游戏数据
		 *	@param	id	存档id，-1为重玩本关
		 */
		UMGDBRow getUserGame();
		UMGDBRow getUserGame(int id);
		/**
		 *	清空用户游戏数据，gamerover时候清空数据
		 */
		void clearUserGame();
		/*
		*	清空游戏日志表，在放弃游戏的时候清空游戏数据
		*/
		void cleatUserGameLog();
		/**
		 *	设置分数
		 */
		void setScore(int score);
		/*进行加分操作*/
		void scorePlus(int score);
		/**
		 *	设置关卡
		 */
		void setStage(int stage);
		/**
		 *	过关，过关时候处理下关数据
		 */
		void stageClear();
		/**
		*	设置时间
		*/
		void setTime(int time);
		/**
		*	记录是否使用了时间道具
		*/
		void setUseTimeItem(bool);
		/**
		*	返回是否使用了时间道具
		*/
		bool isUseTimeItem();
		/**
		*	记录是否使用了魔药道具
		*/
		void setUseRage(bool);
		/**
		*	返回是否使用了魔药道具
		*/
		bool isUseRage();
		/**
		 *	获取场景上的鱼
		 */
		std::vector<UMGDBRow> getFishes();
		/**
		 *	添加鱼，没有参数为完全随机
		 *	@param	type	类型
		 *	@param	x	坐标x
		 *	@param	y	坐标y
		 *	@param	award	奖励
		 */
		int addFish(int type, int x, int y, std::string award = "");
		int addFish();
		/**
		 *	删除鱼
		 *	@param	鱼id
		 */
		void delFish(int id);
		/**
		 *	清空鱼
		 */
		void clearFish();
		/**
		 *	获取存档列表
		 */
		std::vector<UMGDBRow> getGameSaves();
		/**
		 *	添加存档
		 *	@param	stage	关卡
		 *	@param	score	分数
		 */
		void addGameSave(int stage, int score);
		void addGameSave();
		/**
		 *	修改存档
		 *	@param	id	修改的存档的id
		 *	@param	stage	关卡
		 *	@param	score	分数
		 */
		void modifyGameSave(int id, int stage, int score);
		void modifyGameSave(int id);
		/**
		 *	获取日期字符串
		 */
		std::string getDate(time_t timestamp);
		void userGameInit();
		/**
		 *	积分改变事件
		 */
		static const std::string SCORE_CHANGE;
		/**
		 *	关卡改变事件
		 */
		static const std::string STAGE_CHANGE;
		/**
		*	时间改变事件
		*/
		static const std::string TIME_CHANGE;
	private:
		/**
		 *	自身
		 */
		static Game* _instance;
		/**
		 *	数据库
		 */
		DBSqlite* _db;
		/**
		 *	用户uid
		 */
		int _uid;
		/**
		 *	记录日志
		 */
		void addUserGameLog();
		/**
		 *	用户数据表
		 */
		const std::string USER_TABLE = "user";
		/**
		 *	用户游戏数据表
		 */
		const std::string USER_GAME_TABLE = "user_game";
		/**
		 *	用户游戏数据日志表
		 */
		const std::string USER_GAME_LOG_TABLE = "user_game_log";
		/**
		 *	初始数据
		 */
		static const UserGameInfo DEFAULT_USER_GAME_DATA;
		/**
		 *	游戏存档数据表
		 */
		const std::string GAME_SAVE_TABLE = "game_save";
		/**
		 *	鱼数据表
		 */
		const std::string GAME_FISH_TABLE = "game_fish";
	};
}
#endif // __DATA_GAME_H__
