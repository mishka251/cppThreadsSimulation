#include "CPUQueue.h"
CPUQueue::CPUQueue(int size) {
	this->size = size;
	this->canBeginTime = 0;
}

void CPUQueue::addProcess(Process* process) {
	this->processes.push(process);
	this->canBeginTime = std::max(this->canBeginTime, process->getAddTime());
}

bool CPUQueue::isFull() {
	return this->processes.size() == this->size;
}

Process* CPUQueue::pop() {
	Process* top = this->processes.front();
	this->processes.pop();
	return top;
}

int CPUQueue::getCount() {
	return this->processes.size();
}

int CPUQueue::getCanBeginTime() {
	return this->canBeginTime;
}