#include "cocos2d.h"

USING_NS_CC;

class ModelDialog : public CCLayerColor
{
public:
    ModelDialog(CCObject* caller,SEL_CallFunc func);

    static ModelDialog* create(const char* title ,CCObject* caller,SEL_CallFunc func,int type);

    virtual bool init(const char* title,int type);

    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void registerWithTouchDispatcher();

    void menuYes(CCObject* pSender);
    void menuNo(CCObject* pSender);


protected:

    CCObject* m_caller;
    SEL_CallFunc m_func;
private:
};