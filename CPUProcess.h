#include"Process.h"
#pragma once
class CPUProcess
{
protected:
	int processesCount;
	int processesMinDelta;
	int processesMaxDelta;
	int lastProcessTime;
	int lasProcessId;
public:
	CPUProcess(int count, int minDelta, int maxDelta);
	Process* createProcess();
	bool hasNext();
	int getNowTime();
};

