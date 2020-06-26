# cppThreadsSimulation
## Требует с++ 17!
## Создано в Visual Studio 2019 Pro
Лабораторная работа.
Имитация обработки нескольких процессов одним процессором.
Класс CPU имитирует обработку процессором потоков.
Класс Process имитирует один процесс.
Класс CPUProcess имитирует генератор процессов.
Класс CPUQueue имитирует очередь процессов

Алгоритм:
CPUProcess генерирует процессы и добавляет в очередь. Когда очередь заполняется она либо идёт на обработку в CPU,
либо становиться в очередь на запуск и создается новая очередь.
Считется сколько очередей ждало обработки процессором в каждый момент времени и считается среднее кол-во очередей.