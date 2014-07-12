#ifndef _CONFIG_
#define _CONFIG_
#include "cocos2d.h"
class Global
{
public:
    Global();
    ~Global();
    static Global *shareGlobal();


    void save();

    int bestScore;
    int maxTitle;
    bool bSound;

    int curScore;
    int curTitle;

    cocos2d::CCObject* caller;
    cocos2d::SEL_CallFunc func;

};

#endif 
