/****************************************************************************
*	@       	       
*	@desc	在鱼之间画线
*	@date	2014-10-27
*	@author	110101
*	@       	       
*	@file	game/Line.h
*	@modify	null
******************************************************************************/
#ifndef __LINE_H__
#define __LINE_H__
#include "cocos2d.h"
#include "cache/Fish.h"
#include "game/Fish.h"
class Line : public cocos2d::Layer
{
public:
	/**
	 *	初始化
	 *	@return	是否正确初始化信息
	 */
	virtual bool init();
	/**
	 *	静态的create工厂方法
	 *	@return	创建好画线层对象
	 */
	CREATE_FUNC(Line);
	/**
	 *	画线中
	 */
	void drawing(cocos2d::Vec2 point);
	/**
	 *	画节点
	 */
	void drawNode(cocos2d::Vec2 point,int type);
	/**
	 *	画实体线
	 */
	void drawFact(int type);
	/**
	 *	画线结束
	 */
	void drawEnd();
	/**
	 *	效果
	 */
	void effect();
	/**
	 *	闭合
	 */
	bool isSynezesis();
	/**
	 *	触网
	 */
	bool isWebify(cocos2d::Vec2 point);
	/**
	 *	被圈中
	 */
	bool isRounded(cocos2d::Vec2 point);
	/**
	 *	点在多边形内
	 */
	bool isPointInPolygon(cocos2d::Vec2 point, std::vector<cocos2d::Vec2> Vertexs);
private:
	/**
	 *	节点集合
	 */
	std::vector<cocos2d::Vec2> _nodes;
	/**
	 *	拖动点
	 */
	cocos2d::Vec2 _dragPoint;
	/**
	 *	纹理
	 */
	cocos2d::Texture2D* _texture;
	/**
	 *	正在画的线
	 */
	cocos2d::Sprite* _drawLine;
	/*
	*	正在画的闪光鱼的线
	*/
	cocos2d::Sprite*_drawShingLine;
	/**
	 *	实际的线
	 */
	cocos2d::Layer* _factLine = nullptr;
	/**
	 *	粒子效果
	 */
	cocos2d::Layer* _particle;
	/**
	 *	线宽度
	 */
	int LINE_WIDTH;
	/**
	 *	注册点x
	 */
	const int LINE_ANCHOR_X = 24;
	/**
	 *	热区
	 */
	const int HOT_SCOPE = 15;
	/*
	*	是否是闪光鱼
	*/
	bool _isShing;

};
#endif