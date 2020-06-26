#pragma once
class Process
{
protected:
	int id;
	int add_time;
public:
	Process(int id, int add_time);
	int getId();
	int getAddTime();
};

