# cppThreadsSimulation
## Вимагає с++ 17!
## Створено в Visual Studio 2019 Pro
Лабораторна работа.
Імітація імітує декількох процесів одним процесом.
Клас CPU імітує обробку процесорів потоків.
Клас Process імітує один процес.
Клас CPUProcess імітує генератор процесів.
Клас CPUQueue імітує чергу процесів.

Алгоритм:
CPUProcess генерує процеси і добавляє в чергу. Коли черга заповнюється чи йде на обробку в CPU,або стає в чергу на запуск і створюється нова черга.
Рахується скільки черг чекало обробки процесів в кожний момент часу і рахується середня кількість черг.
