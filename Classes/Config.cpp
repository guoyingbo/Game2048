#include "Config.h"

USING_NS_CC;
static Global s_config;

Global::Global()
{
    bestScore = 0;
    maxTitle = 0;
    bSound = true;

    curScore = 0;
    curTitle = 0;
}

Global * Global::shareGlobal()
{
    return &s_config;
}

Global::~Global()
{

}


void Global::load()
{
    bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("BestScore",0);
    maxTitle = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxTitle",0);
    bSound = CCUserDefault::sharedUserDefault()->getBoolForKey("Sound",true);
}

void Global::save()
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("BestScore",bestScore);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxTitle",maxTitle);
    CCUserDefault::sharedUserDefault()->setBoolForKey("Sound",bSound);
}
