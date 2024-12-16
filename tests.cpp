#include <cassert>
#include <iostream>
#include "tasks.h"
#include "task_container.h"
#include "plan.h"

// === Тесты для Task и его наследников ===
void testDeadlineTask() {
    DeadlineTask task(1, "Submit report", "Alice", 3, 120, 300);

    assert(task.getId() == 1);
    assert(task.getAssignee() == "Alice");
    assert(task.getPriority() == 3);
    assert(task.nextExecutionTime() == 300);

    task.extendDeadline(50);
    assert(task.nextExecutionTime() == 350);

    task.changePriority(5);
    assert(task.getPriority() == 5);

    std::cout << "DeadlineTask tests passed!\n";
}

void testPeriodicTask() {
    PeriodicTask task(2, "Backup system", "Bob", 2, 60, 400, 3600);

    assert(task.getId() == 2);
    assert(task.getAssignee() == "Bob");
    assert(task.getPriority() == 2);
    assert(task.nextExecutionTime() == 400);

    task.skipNextExecution();
    assert(task.nextExecutionTime() == 400 + 3600);

    std::cout << "PeriodicTask tests passed!\n";
}

void testOverdueTask() {
    OverdueTask task(3, "Fix server issue", "Charlie", 5, 180);

    assert(task.getId() == 3);
    assert(task.getAssignee() == "Charlie");
    assert(task.getPriority() == 5);
    assert(task.nextExecutionTime() == 0);

    std::cout << "OverdueTask tests passed!\n";
}

// === Тесты для TaskContainer ===
void testTaskContainer() {
    TaskContainer container;

    auto task1 = std::make_shared<DeadlineTask>(1, "Submit report", "Alice", 3, 120, 300);
    auto task2 = std::make_shared<PeriodicTask>(2, "Backup system", "Bob", 2, 60, 400, 3600);
    auto task3 = std::make_shared<OverdueTask>(3, "Fix server issue", "Charlie", 5, 180);

    container.addTask(task1);
    container.addTask(task2);
    container.addTask(task3);

    assert(container.getAllTasks().size() == 3);

    auto aliceTasks = container.getTasksByAssignee("Alice");
    assert(aliceTasks.size() == 1);
    assert(aliceTasks[0]->getId() == 1);

    assert(container.removeTask(2) == true);
    assert(container.getAllTasks().size() == 2);

    auto remainingTask = container.getTaskById(3);
    assert(remainingTask->getId() == 3);

    container.printAll();

    std::cout << "TaskContainer tests passed!\n";
}

// === Тесты для Plan ===
void testPlan() {
    Plan plan;

    auto task1 = std::make_shared<DeadlineTask>(1, "Submit report", "Alice", 3, 120, 300);
    auto task2 = std::make_shared<PeriodicTask>(2, "Backup system", "Bob", 2, 60, 400, 3600);

    plan.addTask(task1);
    plan.addTask(task2);

    plan.printAll();

    plan.executeNext(); // Выполняется task1
    plan.executeNext(); // Выполняется task2 и переходит в следующий цикл

    auto periodicTask = std::dynamic_pointer_cast<PeriodicTask>(task2);
    assert(periodicTask->nextExecutionTime() == 400 + 3600);

    std::cout << "Plan tests passed!\n";
}

// === Тесты для Scheduler ===
void testScheduler() {
    TaskContainer container;

    auto task1 = std::make_shared<DeadlineTask>(1, "Submit report", "Alice", 3, 120, 300);
    auto task2 = std::make_shared<PeriodicTask>(2, "Backup system", "Bob", 2, 60, 400, 3600);
    auto task3 = std::make_shared<OverdueTask>(3, "Fix server issue", "Charlie", 5, 180);

    container.addTask(task1);
    container.addTask(task2);
    container.addTask(task3);

    Scheduler scheduler(container);
    Plan plan = scheduler.buildPlan();

    plan.printAll();

    plan.executeNext(); // Выполняется OverdueTask (самое срочное)
    plan.executeNext(); // Выполняется DeadlineTask
    plan.executeNext(); // Выполняется PeriodicTask и переносится на следующее выполнение

    std::cout << "Scheduler tests passed!\n";
}

// === Главная функция тестов ===
int main() {
    testDeadlineTask();
    testPeriodicTask();
    testOverdueTask();
    testTaskContainer();
    testPlan();
    testScheduler();

    std::cout << "All tests passed!\n";

        TaskContainer container;

    container.addTask(std::make_shared<DeadlineTask>(1, "Submit report", "Alice", 3, 120, 300));
    container.addTask(std::make_shared<PeriodicTask>(2, "Backup system", "Bob", 2, 60, 400, 3600));
    container.addTask(std::make_shared<OverdueTask>(3, "Fix server issue", "Charlie", 5, 180));

    Scheduler scheduler(container);
    Plan plan = scheduler.buildPlan();

    std::cout << "All tasks in the container:\n";
    container.printAll();

    std::cout << "\nExecuting tasks from the plan:\n";
    plan.executeNext();
    plan.executeNext();
    plan.executeNext();
    return 0;
}