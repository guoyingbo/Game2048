#include "Config.h"

USING_NS_CC;
static Global s_config;

Global::Global()
{
    bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("BestScore",0);
    maxTitle = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxTitle",0);
    bSound = CCUserDefault::sharedUserDefault()->getBoolForKey("Sound",true);

    curScore = 0;
    curTitle = 0;
}

Global * Global::shareGlobal()
{
    return &s_config;
}

Global::~Global()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("BestScore",bestScore);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxTitle",maxTitle);
    CCUserDefault::sharedUserDefault()->setBoolForKey("Sound",bSound);
}



