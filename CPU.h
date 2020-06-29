#pragma once
#include"CPUQueue.h"
#include"Process.h"

class CPU
{
private:
	int processTime;
	int nextFreeTime;
	Process* process;
	int id;
public:
	CPU(int processTime, int id);
	void addQueue(CPUQueue* queue, int now);
	bool isBusy(int time);
	int getNextFreeTime();
	void run(int time, Process* process);
	int getProcessGenerator();
	//void free();
};

