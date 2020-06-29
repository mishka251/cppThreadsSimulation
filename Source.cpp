#include<iostream>
#include"CPU.h"
#include"CPUProcess.h"
#include"CPUQueue.h"
#include<vector>
#include<time.h>
#include<map>

int main() {
	srand(unsigned(time(NULL)));

	int processTime1 = 3;


	int minDelta1 = 1;
	int maxDelta1 = 6;

	int minDelta2 = 3;
	int maxDelta2 = 8;

	int processCount = 15;

	CPU cpu(processTime1, 1);

	CPUProcess generator1(processCount, minDelta1, maxDelta1, 1);
	CPUProcess generator2(processCount, minDelta2, maxDelta2, 2);


	int timeNow = 0;

	int firstLoses = 0;
	int secondLoses = 0;

	while (generator1.hasNext() || generator2.hasNext()) {

		int nextTick = generator1.getNextTime();

		nextTick = std::min(nextTick, generator2.getNextTime());

		if (cpu.isBusy(timeNow)) {
			nextTick = std::min(nextTick, cpu.getNextFreeTime());
		}


		timeNow = nextTick;


		if (nextTick == generator1.getNextTime() || nextTick == generator2.getNextTime()) {
			Process* newProcess =
				(nextTick == generator1.getNextTime())
				? generator1.createProcess() :
				generator2.createProcess();

			if (!cpu.isBusy(timeNow)) {
				cpu.run(timeNow, newProcess);
			}
			else {
				if (cpu.getProcessGenerator() == newProcess->getGenerator()) {
					std::cout << "cpu has process from " << cpu.getProcessGenerator() << " thred,"
						<< cpu.getProcessName() << " lost" << std::endl;
					cpu.run(timeNow, newProcess);
				}
				else {
					std::cout << "process " << newProcess->getName() << " destoyed" << std::endl;

					if (newProcess->getGenerator() == 1) {
						firstLoses++;
					}
					else {
						secondLoses++;
					}

					delete newProcess;
				}

			}
		}


		std::cout << std::endl;
	}




	std::cout << " thread 1 destroyed " << 100.0 * firstLoses / processCount << "%" << std::endl;
	std::cout << " thread 2 destroyed " << 100.0 * secondLoses / processCount << "%" << std::endl;

	return 0;
}