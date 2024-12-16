#ifndef PLAN_H
#define PLAN_H

#include <queue>
#include "task_container.h"

class Plan {
private:
    struct TaskCompare {
        bool operator()(const std::shared_ptr<Task>& a, const std::shared_ptr<Task>& b) {
            return a->nextExecutionTime() > b->nextExecutionTime();
        }
    };

    std::priority_queue<std::shared_ptr<Task>, std::vector<std::shared_ptr<Task>>, TaskCompare> taskQueue;

public:
    void addTask(const std::shared_ptr<Task>& task);
    void executeNext();
    void printAll() const;
};

class Scheduler {
private:
    TaskContainer& container;

public:
    Scheduler(TaskContainer& container);
    Plan buildPlan() const;
};

#endif // PLAN_H