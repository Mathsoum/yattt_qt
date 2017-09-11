#include "include/model/task.h"

Task::Task(const std::string &name, const std::string &description, const std::string &status)
    : name(name), description(description), status(status)
{
}
