#include "CPU.h"
#include<iostream>

CPU::CPU(int processTime, int id) {
	this->processTime = processTime;
	this->nextFreeTime = 0;
	this->id = id;
}

bool CPU::isBusy(int time) {
	return time < this->nextFreeTime;
}

void CPU::addQueue(CPUQueue* queue, int now) {
	int total_time = 0;
	while (queue->getCount() > 0)
	{
		Process* process = queue->pop();
		std::cout << "process " << process->getId() << " wait from " << process->getAddTime() <<
			" start at " << now + total_time << " end at " << now + total_time + this->processTime << std::endl;

		delete process;
		total_time += this->processTime;
	}
	this->nextFreeTime = now + total_time;
	delete queue;
}

int CPU::getNextFreeTime() {
	return this->nextFreeTime;
}

void CPU::run(int time, Process* process) {
	std::cout << "t=" << time << " CPU" << this->id << " run process " << process->getName()<<
		" start at " << time << " will end at " << time + this->processTime << std::endl;
	this->nextFreeTime = time + this->processTime;
	this->process = process;
}

int CPU::getProcessGenerator() {
	return process->getGenerator();
}