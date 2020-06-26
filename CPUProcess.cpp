#include "CPUProcess.h"
#include<random>
#include<iostream>

CPUProcess::CPUProcess(int count, int minDelta, int maxDelta) {
	this->processesCount = count;
	this->processesMinDelta = minDelta;
	this->processesMaxDelta = maxDelta;
	this->lastProcessTime = 0;
	this->lasProcessId = 0;
}

Process* CPUProcess::createProcess() {
	this->lasProcessId++;
	int timeDelta = this->processesMinDelta + rand() % (this->processesMaxDelta - this->processesMinDelta);
	this->lastProcessTime += timeDelta;
	Process* process = new Process(this->lasProcessId, this->lastProcessTime);


	return process;
}

bool CPUProcess::hasNext() {
	return this->lasProcessId < this->processesCount;
}

int CPUProcess::getNowTime() {
	return this->lastProcessTime;
}