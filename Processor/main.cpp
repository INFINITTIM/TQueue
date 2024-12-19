#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include "../Queue/TQueue.h"

class Task {
    int id;
    int stepsCount;
    int processorsCount;
public:
    int get_id()
    {
        return id;
    }
    int get_stepsCount()
    {
        return stepsCount;
    }
    int get_processorsCount()
    {
        return processorsCount;
    }

    Task() : id(-1), stepsCount(0), processorsCount(0) {}

    Task(int id, int stepsCount, int processorsCount)
        : id(id), stepsCount(stepsCount), processorsCount(processorsCount) {}
};

class CPU {
    bool isBusy;
    int taskID; 
    int currentStepIndex; 
    int allstepsCount;
    int freeTime; 
    int solvedTasksCount;
public:

    CPU() : isBusy(false), taskID(-1), currentStepIndex(0), freeTime(0), solvedTasksCount(0), allstepsCount(0) {}

    CPU(bool _isBusy, int _taskID, int _currentStepIndex, int _freeTime, int _solvedTasksCount, int _allstepsCount)
        : isBusy(_isBusy), taskID(_taskID), currentStepIndex(_currentStepIndex), 
        freeTime(_freeTime), solvedTasksCount(_solvedTasksCount), allstepsCount(_allstepsCount) {}

    bool getisBusy()
    {
        return isBusy;
    }

    int gettaskID()
    {
        return taskID;
    }

    int getcurrentStepIndex()
    {
        return currentStepIndex;
    }

    int getfreeTime()
    {
        return freeTime;
    }

    int getsolvedTasksCount()
    {
        return solvedTasksCount;
    }

    int getallspetcount()
    {
        return allstepsCount;
    }

    void takingTask(int id, int _allstepsCount)
    {
        isBusy = true;
        taskID = id;
        allstepsCount = _allstepsCount;
    }

    void completeStep(int stepsCount)
    {
        if(currentStepIndex < stepsCount)
            currentStepIndex++;
        if (currentStepIndex == stepsCount)
            completeTask();
    }

    void completeTask()
    {
        isBusy = false;
        taskID = -1;
        currentStepIndex = 0;
        freeTime = 1;
        allstepsCount = 0;
        solvedTasksCount++;
    }

    void freetimecpu()
    {
            ++freeTime;
    }

    void printCPU()
    {
        if (!getisBusy())
        {
            std::cout << "Свободен уже ";

            std::cout << getfreeTime();

            int remainder_100 = getfreeTime();

            while (remainder_100 > 99)
                remainder_100 %= 100;
            if (((remainder_100 > 20 || remainder_100 < 10) && (remainder_100 % 10) == 1))
                std::cout << " такт";
            else if ((remainder_100 > 20 || remainder_100 < 10) &&
                ((remainder_100 % 10) == 2 || (remainder_100 % 10) == 3 || (remainder_100 % 10) == 4))
                std::cout << " такта";
            else
                std::cout << " тактов";
        }

        else
        {
            std::cout << "Занят Задачей : ";
            std::cout << gettaskID();

            std::cout << " | Выполнено: " << getcurrentStepIndex() << "/" << getallspetcount();
        }

        std::cout << " | Решено задач : " << getsolvedTasksCount();
    }
};

class Program
{
public:
    std::vector<CPU> processors;
    TQueue<Task> tasks;

    Program(int processorCount) : tasks(100)
    {
        processors.resize(processorCount);
    }

    void addTask(const Task& new_task)
    {
        tasks.push(new_task);
    }

    void processTask(double P, int maxstepcount, int maxprocessorcount)
    {
        if ((rand() % 100) < (P * 100)) {
            int id = rand() % 1000;
            int stepsCount = 1 + rand() % maxstepcount;
            int processorsCount = 1 + rand() % maxprocessorcount;

            addTask(Task(id, stepsCount, processorsCount));
        }

        for (int i = 0; i < processors.size(); i++)
        {
            if (processors[i].getisBusy())
                processors[i].completeStep(processors[i].getallspetcount());
            else
            {
                processors[i].freetimecpu();
            }
        }

        if (!tasks.isEmpty())
        {
            Task t = tasks.pop();
            int not_busy_cpu_count = 0;

            for (int i = 0; i < processors.size(); i++)
            {
                if (!processors[i].getisBusy()) {
                    not_busy_cpu_count++;
                }
            }

            int tmp_t_processorsCount = t.get_processorsCount();

            if (not_busy_cpu_count >= tmp_t_processorsCount)
            {
                for (int i = 0; i < processors.size(); i++)
                {
                    if ((!processors[i].getisBusy()) && (tmp_t_processorsCount > 0))
                    {
                        processors[i].takingTask(t.get_id(), t.get_stepsCount());
                        tmp_t_processorsCount--;
                    }
                }
                std::cout << "Задача " << t.get_id() << " назначена на выполнение\n" << std::endl;
            }
            else {
                tasks.push(t);
                std::cout << "Недостаточно процессоров. Задача " << t.get_id() << " помещена в конец очереди\n" << std::endl;
            }
            
        }
        printProgram();
        printQueue();
    }

    void printProgram()
    {
        std::cout << "Статус процессоров:\n";
        for (int i = 0; i < processors.size(); ++i) {
            std::cout << "Процессор " << i + 1 << " | ";
            processors[i].printCPU();
            std::cout << std::endl;
        }
        std::cout << std::endl << "Количество задач в очереди: " << tasks.size() << "\n";
        std::cout << std::endl;
    }

    void printQueue() const {
        if (tasks.isEmpty()) {
            std::cout << "Очередь задач пуста.\n";
        }
        else
        {
            std::cout << "Задачи в очереди:\n";

            TQueue<Task> temp_queue_tasks = tasks;
            while (!temp_queue_tasks.isEmpty()) {
                Task task = temp_queue_tasks.front();
                std::cout
                    << "ID: " << task.get_id()
                    << ", Шаги: " << task.get_stepsCount()
                    << ", Процессоры: " << task.get_processorsCount()
                    << std::endl;
                temp_queue_tasks.pop();
            }
        }
    }
};

int main()
{
    setlocale(LC_ALL, "Russian");
    srand((time(nullptr)));

    int processorCount;
    int taсts;
    double P;

    int maxstepcount;
    int maxprocessorcount;

    std::cout << "Выберите кол-во процессоров : ";
    std::cin >> processorCount;
    std::cout << "Выберите шанс появления задачи : ";
    std::cin >> P;
    std::cout << "Выберите кол-во тактов работы программы : ";
    std::cin >> taсts;

    std::cout << " --------------------------------------------- " << std::endl;

    std::cout << "Задача может выпасть с кол-вом процессоров от 1 до ";
    std::cin >> maxprocessorcount;
    std::cout << "Задача может выпасть с кол-вом шагов от 1 до ";
    std::cin >> maxstepcount;

    Program prog(processorCount);

    for (int i = 0; i < taсts; i++)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        system("cls");
        prog.processTask(P, maxstepcount, maxprocessorcount);
    }
}
