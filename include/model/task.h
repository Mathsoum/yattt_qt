#ifndef TASK_H
#define TASK_H

#include <string>

struct Task
{
    Task(int id,
         const std::string& name,
         const std::string& description,
         const std::string& status,
         int startingTimestamp,
         int endingTimestamp);

    int id;
    std::string name;
    std::string description;
    std::string status;
    int startingTimestamp;
    int endingTimestamp;
};

#endif // TASK_H
