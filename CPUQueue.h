#include<queue>
#include"Process.h"

#pragma once
class CPUQueue
{
protected:
	int size;
	std::queue<Process*> processes;
	int canBeginTime;
public:
	CPUQueue(int size);
	bool isFull();
	void addProcess(Process* process);
	Process* pop();
	int getCount();
	int getCanBeginTime();
};

