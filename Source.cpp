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

	int processTime1 = 5;
	int processTime2 = 5;


	int minDelta1 = 1;
	int maxDelta1 = 8;

	int minDelta2 = 1;
	int maxDelta2 = 8;

	int processCount = 20;

	CPU cpu1(processTime1, 1);
	CPU cpu2(processTime2, 2);

	CPUProcess generator1(processCount, minDelta1, maxDelta1, 1);
	CPUProcess generator2(processCount, minDelta2, maxDelta2, 2);

	CPUQueue queue(queueSize);

	int timeNow = 0;

	int firstLoses = 0;
	int secondLoses = 0;

	int maxQueueSze = 0;

	while (generator1.hasNext() && generator2.hasNext()) {

		int nextTick = generator1.getNextTime();

		nextTick = std::min(nextTick, generator2.getNextTime());

		if (cpu1.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu1.getNextFreeTime());
		}

		if (cpu2.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu2.getNextFreeTime());
		}

		timeNow = nextTick;

		if (nextTick == generator2.getNextTime()) {
			Process* newProcess = generator2.createProcess();
			if (!cpu2.isBusy(timeNow)) {
				cpu2.run(timeNow, newProcess);
			}
			else {
				std::cout << "prcoess " << newProcess->getName() << " pushedto queue" << std::endl;
				queue.addProcess(newProcess);
				maxQueueSze = std::max(maxQueueSze, queue.getCount());
			}
		}

		if (nextTick == generator1.getNextTime()) {
			Process* newProcess = generator1.createProcess();
			if (!cpu1.isBusy(timeNow)) {
				cpu1.run(timeNow, newProcess);
			}
			else {
				if (cpu1.getProcessGenerator() == 2) {
					std::cout << "cpu1 has process from 2 thred," << newProcess->getName() << " lost" << std::endl;
				}
				else {
					if (!cpu2.isBusy(timeNow)) {
						cpu2.run(timeNow, newProcess);
					}
					else {
						std::cout << "process " << newProcess->getName() << " destoyed" << std::endl;
						delete newProcess;
						firstLoses++;
					}
				}

			}
		}

		if (nextTick == cpu2.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu2 is free and take process"
					<< process->getName() << "from queue" << std::endl;
				cpu2.run(timeNow, process);
			}
			else {

			}
		}

		if (nextTick == cpu1.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu1 is free and take process" <<
					process->getName() << "from queue" << std::endl;
				cpu1.run(timeNow, process);
			}
		}
		std::cout << std::endl;
	}


	while (generator1.hasNext()) {

		int nextTick = generator1.getNextTime();


		if (cpu1.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu1.getNextFreeTime());
		}

		if (cpu2.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu2.getNextFreeTime());
		}

		timeNow = nextTick;


		if (nextTick == generator1.getNextTime()) {
			Process* newProcess = generator1.createProcess();
			if (!cpu1.isBusy(timeNow)) {
				cpu1.run(timeNow, newProcess);
			}
			else {
				if (cpu1.getProcessGenerator() == 2) {
					std::cout << "cpu1 has process from 2 thred, " << newProcess->getName() << " lost" << std::endl;
				}
				else {
					if (!cpu2.isBusy(timeNow)) {
						cpu2.run(timeNow, newProcess);
					}
					else {
						std::cout << "process " << newProcess->getName() << " destoyed" << std::endl;
						delete newProcess;
						firstLoses++;
					}
				}

			}
		}

		if (nextTick == cpu2.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu2 is free and take process" << process->getId()
					<< " generate from " << process->getGenerator() << " from queue" << std::endl;
				cpu2.run(timeNow, process);
			}
		}

		if (nextTick == cpu1.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu1 is free and take process" << process->getId()
					<< " generate from " << process->getGenerator() << " from queue" << std::endl;
				cpu1.run(timeNow, process);
			}
		}
		std::cout << std::endl;
	}

	while (generator2.hasNext()) {

		int nextTick = generator2.getNextTime();


		if (cpu1.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu1.getNextFreeTime());
		}

		if (cpu2.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu2.getNextFreeTime());
		}

		timeNow = nextTick;

		if (nextTick == generator2.getNextTime()) {
			Process* newProcess = generator2.createProcess();
			if (!cpu2.isBusy(timeNow)) {
				cpu2.run(timeNow, newProcess);
			}
			else {
				queue.addProcess(newProcess);
				maxQueueSze = std::max(maxQueueSze, queue.getCount());
			}
		}

		if (nextTick == cpu2.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu2 is free and take process" << process->getName() << " from queue" << std::endl;
				cpu2.run(timeNow, process);
			}
		}

		if (nextTick == cpu1.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu1 is free and take process" << process->getName() << " from queue" << std::endl;
				cpu1.run(timeNow, process);
			}
		}
		std::cout << std::endl;
	}

	while (queue.getCount() > 0) {

		int nextTick = cpu1.getNextFreeTime();


		if (cpu2.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu2.getNextFreeTime());
		}

		timeNow = nextTick;

		if (nextTick == cpu2.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu2 is free and take process" << process->getName() << " from queue" << std::endl;
				cpu2.run(timeNow, process);
			}
		}

		if (nextTick == cpu1.getNextFreeTime()) {
			if (queue.getCount() > 0) {
				Process* process = queue.pop();
				std::cout << "t=" << timeNow << " cpu1 is free and take process" << process->getName() << " from queue" << std::endl;
				cpu1.run(timeNow, process);
			}
		}
		std::cout << std::endl;
	}

	std::cout << "max queue size " << maxQueueSze << std::endl;
	std::cout << " thread 1 losts " << 100.0 * firstLoses / processCount << "%" << std::endl;
	std::cout << " thread 2 losts " << 100.0 * secondLoses / processCount << "%" << std::endl;

	return 0;
}