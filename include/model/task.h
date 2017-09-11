#ifndef TASK_H
#define TASK_H

#include <string>

struct Task
{
    Task(const std::string& name, const std::string& description, const std::string& status);

    std::string name;
    std::string description;
    std::string status;
};

#endif // TASK_H
