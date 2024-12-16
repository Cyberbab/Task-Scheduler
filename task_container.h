#ifndef TASK_CONTAINER_H
#define TASK_CONTAINER_H

#include <vector>
#include <memory>
#include <algorithm>
#include <iostream>
#include "tasks.h"

class TaskContainer {
private:
    std::vector<std::shared_ptr<Task>> tasks;

public:
    void addTask(const std::shared_ptr<Task>& task);
    bool removeTask(int taskId);
    std::shared_ptr<Task> getTaskById(int taskId) const;
    const std::vector<std::shared_ptr<Task>>& getAllTasks() const;
    std::vector<std::shared_ptr<Task>> getTasksByAssignee(const std::string& assignee) const;
    void printAll() const;
};

#endif // TASK_CONTAINER_H