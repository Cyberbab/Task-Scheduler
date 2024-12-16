#include "plan.h"

// ==== Plan ====
void Plan::addTask(const std::shared_ptr<Task>& task) {
    taskQueue.push(task);
}

void Plan::executeNext() {
    if (taskQueue.empty()) {
        std::cout << "No tasks to execute.\n";
        return;
    }

    auto task = taskQueue.top();
    taskQueue.pop();
    task->execute();
    if (auto periodicTask = std::dynamic_pointer_cast<PeriodicTask>(task)) {
        periodicTask->skipNextExecution();
        taskQueue.push(periodicTask);
    }
}

void Plan::printAll() const {
    auto copy = taskQueue;
    while (!copy.empty()) {
        copy.top()->print();
        copy.pop();
    }
}

// ==== Scheduler ====
Scheduler::Scheduler(TaskContainer& container) : container(container) {}

Plan Scheduler::buildPlan() const {
    Plan plan;
    for (const auto& task : container.getAllTasks()) {
        plan.addTask(task);
    }
    return plan;
}