#include "Process.h"
Process::Process(int id, int add_time, int generatorId) {
	this->id = id;
	this->add_time = add_time;
	this->generatorId = generatorId;
}

int Process::getAddTime() {
	return this->add_time;
}

int Process::getId() {
	return this->id;
}

int Process::getGenerator() {
	return this->generatorId;
}

std::string Process::getName() {
	std::string res = "";
	res += std::to_string(this->generatorId);
	res += "-";
	res += std::to_string(this->id);
	return res;
}