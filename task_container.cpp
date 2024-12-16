#include "task_container.h"

// ==== TaskContainer ====
void TaskContainer::addTask(const std::shared_ptr<Task>& task) {
    tasks.push_back(task);
}

bool TaskContainer::removeTask(int taskId) {
    auto it = std::remove_if(tasks.begin(), tasks.end(),
                             [taskId](const std::shared_ptr<Task>& task) {
                                 return task->getId() == taskId;
                             });
    if (it != tasks.end()) {
        tasks.erase(it, tasks.end());
        return true;
    }
    return false;
}

std::shared_ptr<Task> TaskContainer::getTaskById(int taskId) const {
    for (const auto& task : tasks) {
        if (task->getId() == taskId) {
            return task;
        }
    }
    return nullptr;
}

const std::vector<std::shared_ptr<Task>>& TaskContainer::getAllTasks() const {
    return tasks;
}

std::vector<std::shared_ptr<Task>> TaskContainer::getTasksByAssignee(const std::string& assignee) const {
    std::vector<std::shared_ptr<Task>> result;
    for (const auto& task : tasks) {
        if (task->getAssignee() == assignee) {
            result.push_back(task);
        }
    }
    return result;
}

void TaskContainer::printAll() const {
    for (const auto& task : tasks) {
        task->print();
    }
}