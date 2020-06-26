#include<iostream>
#include"CPU.h"
#include"CPUProcess.h"
#include"CPUQueue.h"
#include<vector>
#include<time.h>
#include<map>

int main() {
	srand(unsigned(time(NULL)));
	int queueSize = 3;
	int processTime = 5;
	int minDelta = 1;
	int maxDelta = 8;

	int processCount = 20;
	CPU cpu(processTime);
	CPUProcess generator(processCount, minDelta, maxDelta);
	std::vector<CPUQueue*> queues;
	std::map<int, int> queuesForTime;
	queuesForTime.insert({ 0, 0 });

	while (generator.hasNext()) {
		Process* newProcess = generator.createProcess();

		if (queues.size() == 0 || queues[queues.size() - 1]->isFull()) {
			queues.push_back(new CPUQueue(queueSize));
		}

		if (queues[0]->isFull() && !cpu.isBusy(generator.getNowTime())) {
			cpu.addQueue(queues[0], std::max(queues[0]->getCanBeginTime(), cpu.getNextFreeTime()));
			queues.erase(queues.begin());
			std::cout << std::endl;
		}

		std::cout << "create process " << newProcess->getId() << " at the " << newProcess->getAddTime() << std::endl;


		queues[queues.size() - 1]->addProcess(newProcess);

		std::cout << "t = " << generator.getNowTime() << " queues count = " << queues.size() <<
			" process in last queue = " << queues[queues.size() - 1]->getCount() << std::endl;
		std::cout << std::endl;

		queuesForTime.insert({ generator.getNowTime(), queues.size() });


		std::cout << std::endl;
	}

	while (queues.size() > 0) {
		int startTime = std::max(queues[0]->getCanBeginTime(), cpu.getNextFreeTime());
		cpu.addQueue(queues[0], startTime);
		queues.erase(queues.begin());
		std::cout << std::endl;
		queuesForTime.insert({ startTime, queues.size() });
	}

	std::map<int, int> timeForQueueCount;

	for (auto const& [now, queuesCount] : queuesForTime) {
		//int now = par.first;
		//int queuesCount = par.second;

		std::cout << "t = " << now << "  queues =  " << queuesCount << std::endl;
		if (queuesCount != 0) {
			int nextTime = queuesForTime.upper_bound(now)->first;
			int length = nextTime - now;

			if (timeForQueueCount.find(queuesCount) == timeForQueueCount.end()) {
				timeForQueueCount.insert({ queuesCount, length });
			}
			else {
				timeForQueueCount[queuesCount] += length;
			}
		}
	}

	int maxQueues = 0;
	int sumTime = 0;
	double midCount = 0;

	for (auto [queuesCount, summTime] : timeForQueueCount) {
		std::cout << queuesCount << "  queues  total time = " << summTime << std::endl;
		maxQueues = std::max(queuesCount, maxQueues);
		sumTime += summTime;
		midCount += queuesCount * summTime;
	}

	midCount /= sumTime;
	std::cout << "max queues = " << maxQueues << "  mid queues count = " << midCount << std::endl;

	//std::cout << "Hello" << std::endl;
	return 0;
}