#pragma once
#include"CPUQueue.h"
#include"Process.h"

class CPU
{
private:
	int processTime;
	int nextFreeTime;
	//CPUQueue* queue;
public:
	CPU(int processTime);
	void addQueue(CPUQueue* queue, int now);
	bool isBusy(int time);
	int getNextFreeTime();
	//void run(int time);
};

