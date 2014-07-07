#include "NumberCell.h"

USING_NS_CC;
cocos2d::ccColor4B NumberCell::m_color[11] =
{
	cocos2d::ccc4(238, 228, 218, 255), //2
	cocos2d::ccc4(237, 224, 200, 255), //4
	cocos2d::ccc4(242, 177, 121, 255), //8
	cocos2d::ccc4(236, 141, 84, 255), //16
	cocos2d::ccc4(246, 124, 95, 255), //32
	cocos2d::ccc4(234, 89, 55, 255), //64
	cocos2d::ccc4(243, 216, 107, 255), //128
	cocos2d::ccc4(241, 208, 75, 255), //256
	cocos2d::ccc4(228, 192, 42, 255), //512
	cocos2d::ccc4(226, 186, 19, 255), //1024
	cocos2d::ccc4(236, 196, 0, 255)  //2048
};

bool NumberCell::init()
{
	CCString snum;
	int text = pow((float)2, m_number);
	snum.initWithFormat("%d", text);

	ccColor4B color = m_color[m_number-1];

	CCLayerColor::initWithColor(color,m_size.width,m_size.height);
	CCLabelTTF *pLable = CCLabelTTF::create(snum.getCString(),"Arial Bold",m_size.height/2);

	pLable->setPosition(ccp(m_size.width/2, m_size.height/2));
	if (m_number < 3)
		pLable->setColor(ccc3(119,110,101));

	this->addChild(pLable,1,1);

	return true;
}

void NumberCell::SetTitle( int t )
{
	m_number = t;
	CCString snum;
	int text = pow((float)2, m_number);
	snum.initWithFormat("%d", text);
	CCLabelTTF *pLable = (CCLabelTTF *)getChildByTag(1);
	pLable->setString(snum.getCString());
	if (m_number > 2)
		pLable->setColor(ccc3(255,255,255));
	ccColor4B color = m_color[m_number-1];
	this->setColor(ccc3(color.r,color.g,color.b));
}

NumberCell* NumberCell::create( CCSize size, int number )
{
	NumberCell* pRet = new NumberCell(size,number);
	if (pRet && pRet->init())
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}



void ColorRect::draw()
{
	CCLayerColor::draw();
	ccColor3B color = this->getColor();
	CCSize size = this->getContentSize();

	float dr = 255 - color.r;
	float dg = 255 - color.g;
	float db = 255 - color.b;

	int min = dr;
	if (min > dg) min = dg;
	if (min > db) min = db;

	int fac = min /2;

	ccColor3B cdepth = ccc3(color.r + fac*(dr/min),color.g + fac*(dg/min),color.b + fac*(db/min));
	ccDrawColor4B(cdepth.r,cdepth.g,cdepth.b,255);
	ccDrawLine(ccp(0,0),ccp(0,size.height));
	ccDrawLine(ccp(0,size.height),ccp(size.width,size.height));

	dr = color.r;
	dg = color.g;
	db = color.b;

	int max = dr;
	if (max < dg) max = dg;
	if (max < db) max = db;

	fac = max/5;
	cdepth = ccc3(color.r - fac*(dr/max),color.g - fac*(dg/max),color.b - fac*(db/max));
	ccDrawColor4B(cdepth.r,cdepth.g,cdepth.b,255);

	ccDrawLine(ccp(0,0),ccp(size.width,0));
	ccDrawLine(ccp(size.width,0),ccp(size.width,size.height));
}

ColorRect* ColorRect::create( const cocos2d::ccColor4B& color, GLfloat width, GLfloat height )
{
	ColorRect* pRet = new ColorRect();
	if (pRet && pRet->initWithColor(color,width,height))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		delete pRet;
		pRet = NULL;
		return NULL;
	}
}
