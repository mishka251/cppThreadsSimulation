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

	CPU cpu1(processTime, 1);

	CPUProcess generator(processCount, minDelta, maxDelta, 1);

	CPUQueue queue1(queueSize);
	CPUQueue queue2(queueSize);

	int timeNow = 0;

	int processInQueue1 = 0;
	int processInQueue2 = 0;

	while (generator.hasNext()) {

		int nextTick = generator.getNextTime();

		if (cpu1.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu1.getNextFreeTime());
		}

		timeNow = nextTick;

		if (nextTick == generator.getNextTime()) {
			Process* newProcess = generator.createProcess();
			if (!cpu1.isBusy(timeNow)) {
				cpu1.run(timeNow, newProcess);
			}
			else {
				std::cout << "t=" << timeNow << " cpu is busy. " << queue1.getCount() << " processes in queue1, " <<
					queue2.getCount() << " processes in queue2" << std::endl;
				if (queue1.getCount() > queue2.getCount()) {
					std::cout << newProcess->getName() << " push to queue2" << std::endl;
					queue2.addProcess(newProcess);
					processInQueue2++;
				}
				else {
					std::cout << newProcess->getName() << " push to queue1" << std::endl;
					queue1.addProcess(newProcess);
					processInQueue1++;
				}

			}
		}


		if (nextTick == cpu1.getNextFreeTime()) {
			if (queue1.getCount() + queue2.getCount() == 0) {
				std::cout << "t=" << timeNow << " cpu is free. Queues is free" << std::endl;
			}
			else {
				std::cout <<"cpu if free "<< queue1.getCount() << " processes in queue1, " <<
					queue2.getCount() << " processes in queue2" << std::endl;

				if (queue1.getCount() > queue2.getCount()) {
					Process* process = queue1.pop();
					std::cout << "take " << process->getName() << " from to queue1" << std::endl;
					cpu1.run(timeNow, process);
				}
				else {
					Process* process = queue2.pop();
					std::cout << "take from to queue2" << std::endl;
					std::cout << "take " << process->getName() << " from to queue2" << std::endl;
					cpu1.run(timeNow, process);
				}

			}
		}
		std::cout << std::endl;
	}


	while (queue1.getCount() > 0 || queue2.getCount() > 0) {

		int nextTick = cpu1.getNextFreeTime();


		timeNow = nextTick;

		std::cout << queue1.getCount() << " processes in 1 queue" <<
			queue2.getCount() << " processes in 2 queue" << std::endl;

		if (queue1.getCount() > queue2.getCount()) {
			Process* process = queue1.pop();
			std::cout << "take " << process->getName() << " from to queue1" << std::endl;
			cpu1.run(timeNow, process);
		}
		else {
			Process* process = queue2.pop();
			std::cout << "take from to queue2" << std::endl;
			std::cout << "take " << process->getName() << " from to queue2" << std::endl;
			cpu1.run(timeNow, process);
		}
		std::cout << std::endl;
	}

	std::cout << "process in  1 queue " << processInQueue1 <<  std::endl;
	std::cout << "process in  2 queue " << processInQueue2 << std::endl;

	return 0;
}