#pragma once
#include "cocos2d.h"
USING_NS_CC;

class LayerOptions :public CCLayerColor
{
public:
	LayerOptions(void);
	~LayerOptions(void);

	virtual bool init();
	static CCScene* scene(); 
	CREATE_FUNC(LayerOptions);

	void menuContinue(CCObject *pSender);
	void menuExit(CCObject *pSender);
	void menuSound(CCObject *pSender);

protected:
	virtual void keyBackClicked(void);




};

