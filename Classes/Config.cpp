#include "Config.h"

USING_NS_CC;
static Config s_config;

Config::Config()
{
	bestScore = CCUserDefault::sharedUserDefault()->getIntegerForKey("BestScore",0);
	maxTitle = CCUserDefault::sharedUserDefault()->getIntegerForKey("MaxTitle",0);
	bSound = CCUserDefault::sharedUserDefault()->getBoolForKey("Sound",true);
}

Config * Config::shareConfig()
{
	return &s_config;
}

Config::~Config()
{
	CCUserDefault::sharedUserDefault()->setIntegerForKey("BestScore",bestScore);
	CCUserDefault::sharedUserDefault()->setIntegerForKey("MaxTitle",maxTitle);
	CCUserDefault::sharedUserDefault()->setBoolForKey("Sound",bSound);
}



