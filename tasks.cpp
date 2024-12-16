#include "tasks.h"

// ==== Task ====
Task::Task(int id, const std::string& description, const std::string& assignee, int priority, int duration)
    : id(id), description(description), assignee(assignee), priority(priority), duration(duration) {}

int Task::getPriority() const {
    return priority;
}

const std::string& Task::getAssignee() const {
    return assignee;
}

int Task::getId() const {
    return id;
}

void Task::print() const {
    std::cout << "Task ID: " << id << ", Description: " << description
              << ", Assignee: " << assignee << ", Priority: " << priority
              << ", Duration: " << duration << "s\n";
}

// ==== DeadlineTask ====
DeadlineTask::DeadlineTask(int id, const std::string& description, const std::string& assignee, 
                           int priority, int duration, int deadline)
    : Task(id, description, assignee, priority, duration), deadline(deadline) {}

int DeadlineTask::nextExecutionTime() const {
    return deadline;
}

void DeadlineTask::extendDeadline(int seconds) {
    deadline += seconds;
}

void DeadlineTask::changePriority(int newPriority) {
    priority = newPriority;
}

void DeadlineTask::execute() {
    std::cout << "Executing DeadlineTask ID: " << id << " [" << description << "]\n";
}

void DeadlineTask::print() const {
    Task::print();
    std::cout << "Deadline: " << deadline << "s\n";
}

// ==== PeriodicTask ====
PeriodicTask::PeriodicTask(int id, const std::string& description, const std::string& assignee, 
                           int priority, int duration, int nextExecution, int period)
    : Task(id, description, assignee, priority, duration), nextExecution(nextExecution), period(period) {}

int PeriodicTask::nextExecutionTime() const {
    return nextExecution;
}

void PeriodicTask::skipNextExecution() {
    nextExecution += period;
}

void PeriodicTask::execute() {
    std::cout << "Executing PeriodicTask ID: " << id << " [" << description << "]\n";
    nextExecution += period;
}

void PeriodicTask::print() const {
    Task::print();
    std::cout << "Next Execution: " << nextExecution << "s, Period: " << period << "s\n";
}

// ==== OverdueTask ====
OverdueTask::OverdueTask(int id, const std::string& description, const std::string& assignee, 
                         int priority, int duration)
    : Task(id, description, assignee, priority, duration) {}

int OverdueTask::nextExecutionTime() const {
    return 0; // Immediate execution
}

void OverdueTask::execute() {
    std::cout << "Executing OverdueTask ID: " << id << " [" << description << "] IMMEDIATELY\n";
}

void OverdueTask::print() const {
    Task::print();
    std::cout << "Status: OVERDUE\n";
}