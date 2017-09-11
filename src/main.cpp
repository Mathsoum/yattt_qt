#include "include/model/dbmodel.h"

#include <iostream>
#include <iomanip>
#include <string>

int main(int argc, char *argv[])
{
    std::cout << "YATTT -- Yet Another Time-Tracking Tool" << std::endl;
    std::cout << "#######################################" << std::endl << std::endl;
    if (argc < 2) {
        std::cout << "Usage: yattt.exe (add|list) [<name> <description>]" << std::endl;
        return EXIT_SUCCESS;
    }

    DBModel model;
    std::string command = argv[1];

    if (std::string("add") == command) {
        if (argc < 4) {
            std::cout << "ADD command usage: yattt.exe add <name> <description>" << std::endl;
            std::cout << " - <name> and <description> are mandatory" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << "YATTT -- ADD command" << std::endl;

        std::string name = argv[2];
        std::string description = argv[3];

        std::cout << "Name:       " << name << std::endl;
        std::cout << "Descripion: " << description << std::endl;

        try {
            model.addEntry(name, description);
            std::cout << "Entry added successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "ERROR occurred. Entry not added." << std::endl;
            std::cerr << "  Message: " << e.what() << std::endl;
        }
    } else if (std::string("list") == command) {
        std::cout << "YATTT -- LIST command" << std::endl;
        auto list = model.listTasks();
        if (list.size() > 0) {
            std::cout << std::left << std::setfill('-') << std::setw(20) << '+' << std::setw(50) << '+' << std::setw(30) << '+' << std::setw(30) << '+' << std::setw(20) << '+' << '+' << std::endl;
            for(auto task : list) {
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(18) << task.name;
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(48) << task.description;
                std::time_t time = task.startingTimestamp;
                std::string timeStr = std::asctime(std::localtime(&time));
                timeStr.pop_back();
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(28) << timeStr;
                time = task.endingTimestamp;
                timeStr = std::asctime(std::localtime(&time));
                timeStr.pop_back();
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(28) << timeStr;
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(18) << task.status;
                std::cout << "|" << std::endl;
            }
            std::cout << std::left << std::setfill('-') << std::setw(20) << '+' << std::setw(50) << '+' << std::setw(30) << '+' << std::setw(30) << '+' << std::setw(20) << '+' << '+' << std::endl;
        } else {
            std::cout << "No tasks found." << std::endl;
        }
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }

    return EXIT_SUCCESS;
}
