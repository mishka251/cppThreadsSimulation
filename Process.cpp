#include "Process.h"
Process::Process(int id, int add_time) {
	this->id = id;
	this->add_time = add_time;
}

int Process::getAddTime() {
	return this->add_time;
}

int Process::getId() {
	return this->id;
}