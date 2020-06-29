#pragma once
#include<string>
class Process
{
protected:
	int id;
	int add_time;
	int generatorId;
public:
	Process(int id, int add_time, int generator);
	int getId();
	int getAddTime();
	int getGenerator();
	std::string getName();
};

