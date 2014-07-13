
#ifndef LAYERGAMEOVER_H_
#define LAYERGAMEOVER_H_

#include "cocos2d.h"
USING_NS_CC;

class LayerGameOver :public CCLayerColor{
public:
    LayerGameOver();
    virtual ~LayerGameOver();

    virtual bool init();
    CREATE_FUNC(LayerGameOver);

    static CCScene* scene();

    void menuAgain(CCObject *pSender);
    void menuBack(CCObject *pSender);
};

#endif /* LAYERGAMEOVER_H_ */
