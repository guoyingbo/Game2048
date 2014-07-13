#pragma once
#include "cocos2d.h"

class LayerWin :public cocos2d::CCLayerColor{
public:
    LayerWin();
    virtual ~LayerWin();

    virtual bool init();
    CREATE_FUNC(LayerWin);

    static cocos2d::CCScene* scene();

    void menuAgain(cocos2d::CCObject *pSender);
    void menuBack(cocos2d::CCObject *pSender);
};
