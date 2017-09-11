#include "include/model/task.h"

Task::Task(int id, const std::string &name, const std::string &description, const std::string &status, int startingTimestamp, int endingTimestamp)
    : id(id), name(name), description(description), status(status), startingTimestamp(startingTimestamp), endingTimestamp(endingTimestamp)
{
}
