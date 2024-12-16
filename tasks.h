#ifndef TASKS_H
#define TASKS_H

#include <string>
#include <iostream>

// Базовый класс Task
class Task {
protected:
    int id;
    std::string description;
    std::string assignee;
    int priority;
    int duration;

public:
    Task(int id, const std::string& description, const std::string& assignee, int priority, int duration);
    virtual ~Task() = default;

    virtual int nextExecutionTime() const = 0;
    int getPriority() const;
    const std::string& getAssignee() const;
    int getId() const;

    virtual void print() const;
    virtual void execute() = 0;
};

// Задача с крайним сроком
class DeadlineTask : public Task {
private:
    int deadline;

public:
    DeadlineTask(int id, const std::string& description, const std::string& assignee, 
                 int priority, int duration, int deadline);

    int nextExecutionTime() const override;
    void extendDeadline(int seconds);
    void changePriority(int newPriority);
    void execute() override;
    void print() const override;
};

// Периодическая задача
class PeriodicTask : public Task {
private:
    int nextExecution;
    int period;

public:
    PeriodicTask(int id, const std::string& description, const std::string& assignee, 
                 int priority, int duration, int nextExecution, int period);

    int nextExecutionTime() const override;
    void skipNextExecution();
    void execute() override;
    void print() const override;
};

// Просроченная задача
class OverdueTask : public Task {
public:
    OverdueTask(int id, const std::string& description, const std::string& assignee, 
                int priority, int duration);

    int nextExecutionTime() const override;
    void execute() override;
    void print() const override;
};

#endif // TASKS_H