/****************************************************************************
*	@       	       
*	@desc	缓存-音乐
*	@date	2014-11-4
*	@author	120101
*	@       	       
*	@file	cache/Music.h
*	@modify	null
******************************************************************************/
#ifndef __CACHE_MUSIC_H__
#define __CACHE_MUSIC_H__

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "data/User.h"
#include "loading/Loader.h"

namespace cache {
	class Music :public cocos2d::Layer{
	public:
		/**
		 *	初始化
		 */
		Music();
		/**
		 *	析构函数，要清除有指针的内容
		 */
		virtual ~Music();
		/**
		 *	初始化
		 */
		void async();
		/**
		*	回调
		*/
		void jsonAsyncCallback();
		/**
		 *	获取实体
		 */
		static Music* getInstance();
		/**
		*	暂停背景音乐
		*/
		void pauseBGM();
		/**
		*	恢复背景音乐
		*/
		void resumeBGM();
		/**
		*	播放背景音乐
		*/
		void playBGM(int bgmEnum);
		/**
		 *	播放音效
		 *	@参数	音效枚举
		 */
		void playEffect(int effectNameEnum);
		/**
		 *	回调
		 */
		//void jsonAsyncCallback(float dt);
		/**
		 *	音乐的总数量
		 */
		static const int effectCount = 6;
		/**
		 *	前缀
		 */
		static const std::string prefix;
		/**
		 *	音效名字
		 */
		enum EffectName{
			BUYGOLD,
			CLICKBUTTON,
			GAMEOVER,
			FISHBOMB,
			PRESSFISH,
			GAMEWIN,
			PULL
		};

		enum BGMName{
			GATEWAY,
			GAME
		};

	private:
		/**
		 *	自身
		 */
		static Music* _instance;
		/**
		 *	已经载入的数据
		 */
		int _loaded = 0;
		/**
		 *	通过枚举获取音效名字的字符串
		 */
		std::string getSoundEffectStringByEnum(int id);
		/**
		*	通过枚举获取背景音乐名字的字符串
		*/
		std::string getBGMStringByEnum(int id);
	};
}
#endif // __CACHE_MUSIC_H__
