#pragma once

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

