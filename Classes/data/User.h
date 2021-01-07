/****************************************************************************
*	@       	       
*	@desc	用户信息
*	@date	2014-10-17
*	@author	110101
*	@       	       
*	@file	data/User.h
*	@modify	2014-10-22 by 120101
******************************************************************************/
#ifndef __USER_H__
#define __USER_H__

#include "cocos2d.h"
#include "db/DBConnector.h"
#include "db/Table.h"

namespace data{
	/**
	 *	用户信息
	 */
	typedef struct userTag{
		int uid;
		std::string name;
		int gold;
	}UserInfo;
	/**
	*	设置信息
	*/
	typedef struct settingTag{
		int uid;
		int bgm;
		int se;
		int guide;
		int first;
		int libao;
		bool firstlevel;
		bool firstthress;
		bool firstfail;
		bool firstletter;
		bool firstfullletter;
		bool firstshing;
		bool firsttimeitem;
		bool firstbomb;
		bool showbomb;
		bool showshock;
		bool showrage;
		bool adblock;
		bool endlesslock;
	}SettingInfo;

	class User {
	public:
		/**
		 *	初始化
		 */
		User();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~User();
		/**
		 *	获取实体
		 */
		static User* getInstance();
		/**
		 *	初始化
		 */
		void init();
		/**
		*	初始化用户信息
		*/
		void initUserData();
		/**
		*	初始化设置信息
		*/
		void initSettingData();
		/**
		*	从表中读取数据
		*/
		UMGDBRow getUserData();
		/**
		 *	设置金币
		 *	@param	coin	金币数量
		 */
		void setGold(int gold);
		/**
		 *	获取金币
		 *	@return	金币数量
		 */
		int getGold();
		/**
		 *	金币增加
		 *	@param	num	 增加的数量，可为负数
		 */
		bool goldPlus(int num);
		/**
		 *	金币减少
		 *	@param	num	减少的数量，不能为负数
		 *	@return	结果
		 */
		bool goldReduce(unsigned num);
		/**
		 *	设置名字
		 *	@param	姓名
		 */
		void setName(std::string name);
		/**
		 *	获取姓名
		 *	@return	姓名
		 */
		std::string getName();
		/**
		 *	获取用户id
		 */
		int getUID();
		/**
		 *	设置日期
		 *	@param	date	日期，可以用时间戳，可以用datetime，没参数为当前日期
		 */
		void setDate(time_t timestamp);
		void setDate(std::string dateStr);
		void setDate();
		/**
		 *	获取日期
		 *	@return	日期
		 */
		std::string getDate();
		/**
		 *	用户默认信息
		 */
		static const UserInfo DEFAULT_USER_DATA;
		/**
		 *	数据表-用户
		 */
		static const std::string TABLE_USER;
		/**
		 *	金币改变事件
		 */
		static const std::string GOLD_CHANGE;
		
		/**
		*	设置背景音乐开关
		*	@param	bgm	背景音乐开关
		*/
		void setBGM(bool bgm);
		/**
		*	获取背景音乐开关
		*	@return	背景音乐开关
		*/
		bool getBGM();
		/**
		*	设置音效开关
		*	@param	effect	音效开关
		*/
		void setSE(bool se);
		void setSoundEffect(bool valid);
		/**
		*	获取音效开关
		*	@return	音效开关
		*/
		bool getSE();
		bool getSoundEffect();
		/**
		*	设置新手向导开关
		*	@param	guide	新手引导开关
		*/
		void setGuide(int guide);
		/**
		*	获取新手向导开关
		*	@return		新手引导开关
		*/
		int getGuide();
		/**
		*	设置是否第一次进入游戏
		*	@param	first	是否第一次进入游戏
		*/
		void setFirst(bool first);
		/**
		*	获取是否第一次进入游戏
		*	@return		是否第一次进入游戏
		*/
		bool getFirst();
		/**
		*	设置是否还有购买机会
		*	@param	libao  true为还有机会
		*/
		void setLibao(bool libao);
		/**
		*	设置是否是第一次进入第一关
		*/
		void setFirstLevel(bool first);
		/**
		*	获取是否是第一次进入第一关
		*/
		bool getFirstLevel();
		/*
		*	设置是否是第一次失败
		*/
		void setFirstFail(bool first);
		/*
		*	设置是否是第一次使用时间道具
		*/
		void setFirstTimeItem(bool first);
		/*
		*	设置是否是第一次出现字母鱼
		*/
		void setFirstLetter(bool first);
		/*
		*	设置是否是第一次集齐字母
		*/
		void setFirstFullLetter(bool first);
		/*
		*	设置是否是第一次是进入闪光时间
		*/
		void setFirstShing(bool first);
		/*
		*	设置是否是第一次三秒
		*/
		void setFirstThress(bool first);
		/*
		*	是否是第一次使用炸弹
		*/
		void setFirstBomb(bool first);
		/*
		*	是否再次显示炸弹道具界面
		*/
		void setShowBomb(bool b);
		/*
		*	是否再次显示雷电道具界面
		*/
		void setShowShock(bool b);
		/*
		*	是否再次显示狂暴道具界面
		*/
		void setShowRage(bool b);
		/*
		*	是否去掉了广告
		*/
		void setAdblock(bool b);
		/*
		*	无尽模式是否解锁
		*/
		void setEndlesslock(bool b);
		/*
		*	获取无尽模式是否解锁
		*/
		bool getEndlesslock();
		/*
		*	获取是否去掉了广告
		*/
		bool getAdblock();
		/*
		*	获取是否显示雷电
		*/
		bool getShowShock();
		/*
		*	获取是否显示炸弹
		*/
		bool getShowBomb();
		/*
		*	获取是否显示狂暴
		*/
		bool getShowRage();
		/*
		*	获取是否是第一次使用炸弹
		*/
		bool getFirstBomb();
		/*
		*	获取是否是第一次失败
		*/
		bool getFirstFail();
		/*
		*	获取是否是第一次使用时间道具
		*/
		bool getFirstTimeItem();
		/*
		*	获取是否是第一次出现字母鱼
		*/
		bool getFirstLetter();
		/*
		*	获取是否是第一次集齐字母
		*/
		bool getFirstFullLetter();
		/*
		*	获取是否是第一次出现disco鱼
		*/
		bool getFirstShing();
		/*
		*	获取是否是第一次三秒
		*/
		bool getFirstThress();
		/**
		*	设置是否还有购买机会
		*	@param	libao  true为还有机会
		*/
		bool getLibao();
		/**
		*	记录日志-炸弹鱼的记录
		*/
		void addUserBombFishLog();

		void getUserInit();
		/**
		*	获取时间字符串
		*/
		std::string getTimeDate(time_t timestamp=NULL);
		/**
		*	设置场景默认信息
		*/
		static const SettingInfo DEFAULT_SETTING_DATA;
		/**
		*	数据表-设置场景
		*/
		static const std::string TABLE_SETTING;
		/**
		*	数据表-炸弹鱼的日志表
		*/
		static const std::string  USER_BOMBFISH_LOG_TABLE;
		/**
		*	清空炸弹鱼的数据表
		*/
		void clearBombFishLog();
        /**
         *	首冲购买后监听
         */
        static const std::string BUY_FIRST_CHARGE;
	private:
		/**
		 *	自身
		 */
		static User* _instance;
		/**
		 *	数据库
		 */
		DBSqlite* _db;
		/**
		 *	金币数量
		 */
		int _gold;
		/**
		 *	用户uid
		 */
		int _uid;
		/**
		 *	姓名
		 */
		std::string _name;
		/**
		 *	音乐
	   	 */
		bool _bgm;
		/**
		 *	音效
		 */
		bool _se;
		/**
		 *	新手引导
		 */
		int _guide;
		/**
		*	是否是第一次进入游戏
		*/
		bool _first;
		/**
		*	是否还有购买礼包机会
		*/
		bool _libao;
		/**
		*	是否是第一次进入第一关
		*/
		bool _firstlevel;
	

	};
}
#endif // __USER_H__
