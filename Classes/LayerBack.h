#pragma once

#include "cocos2d.h"

class LayerBack : public cocos2d::CCLayerColor
{
public:
    LayerBack();
    ~LayerBack();

    virtual bool init();

    virtual void draw();

    // a selector callback
    void menuCloseCallback(cocos2d::CCObject* pSender);
    void menuRestartCallback(cocos2d::CCObject* pSender);
    void menuOptionsCallback(cocos2d::CCObject* pSender);
    void callbackRestart();
    void callbackExit();
    void callbackGameover();
    void callbackWin();
    virtual void ccTouchMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

    virtual void registerWithTouchDispatcher(void);
    virtual void ccTouchesEnded(cocos2d::CCSet* pTouches, cocos2d::CCEvent* pEvent);
    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
    // implement the "static node()" method manually
    static LayerBack* create();

    virtual void keyBackClicked(void);

    void updateBoard();
    void initBoard();
private:

    int max[16];
    cocos2d::CCPoint position[4][4];
    float cellWidth;

    cocos2d::CCPoint posBegin;

    int &m_score;
    int &m_title;
    int &m_best;
    int &m_maxTitle;
};

