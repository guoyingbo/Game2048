#pragma once
#include "cocos2d.h"



class ColorRect : public cocos2d::CCLayerColor
{
public:
	virtual void draw();
	static ColorRect* create(const cocos2d::ccColor4B& color, GLfloat width, GLfloat height);
};



class NumberCell : public ColorRect
{
public:
	NumberCell(cocos2d::CCSize size, int number):m_number(number),m_size(size){}

	virtual bool init();
	static cocos2d::ccColor4B m_color[11];

	void SetTitle(int t);
	static NumberCell* create(cocos2d::CCSize size, int number);
private:
	int m_number;

	cocos2d::CCSize m_size;

};