#include "CPUProcess.h"
#include<random>
#include<iostream>

CPUProcess::CPUProcess(int count, int minDelta, int maxDelta, int id) {
	this->processesCount = count;
	this->processesMinDelta = minDelta;
	this->processesMaxDelta = maxDelta;
	this->id = id;


	this->nextProcessTime = this->processesMinDelta + rand() % (this->processesMaxDelta - this->processesMinDelta);
	this->generatedProcessesCount = 0;
}

Process* CPUProcess::createProcess() {
	this->generatedProcessesCount++;

	Process* process = new Process(this->generatedProcessesCount, this->nextProcessTime, this->id);
	std::cout << "t=" << this->nextProcessTime << " generator" << this->id << " generate process " << this->generatedProcessesCount << std::endl;
	int timeDelta = this->processesMinDelta + rand() % (this->processesMaxDelta - this->processesMinDelta);
	this->nextProcessTime += timeDelta;
	return process;
}

bool CPUProcess::hasNext() {
	return this->generatedProcessesCount < this->processesCount;
}

int CPUProcess::getNextTime() {
	return this->nextProcessTime;
}