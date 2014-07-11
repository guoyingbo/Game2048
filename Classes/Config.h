#ifndef _CONFIG_
#define _CONFIG_
#include "cocos2d.h"
class Config
{
public:
	Config();
	~Config();
	static Config *shareConfig();


	void save();

	int bestScore;
	int maxTitle;
	bool bSound;


};

#endif 
