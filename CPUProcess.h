#include"Process.h"
#pragma once
class CPUProcess
{
protected:
	int processesCount;
	int processesMinDelta;
	int processesMaxDelta;

	int nextProcessTime;
	int generatedProcessesCount;
	int id;

public:
	CPUProcess(int count, int minDelta, int maxDelta, int id);
	Process* createProcess();
	bool hasNext();
	int getNextTime();
};

