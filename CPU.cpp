#include "CPU.h"
#include<iostream>

CPU::CPU(int processTime) {
	this->processTime = processTime;
	this->nextFreeTime = 0;
}

bool CPU::isBusy(int time) {
	return time <= this->nextFreeTime;
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