#include "include/model/dbmodel.h"

#include <iostream>
#include <iomanip>
#include <string>

int main(int argc, char *argv[])
{
    std::cout << "YATTT -- Yet Another Time-Tracking Tool" << std::endl;
    std::cout << "#######################################" << std::endl << std::endl;
    if (argc < 2) {
        std::cout << "Usage: yattt.exe (add|list|stop) [<name> <description> | <id>]" << std::endl;
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

        std::cout << std::endl;
        std::cout << "Name:       " << name << std::endl;
        std::cout << "Descripion: " << description << std::endl;
        std::cout << std::endl;

        try {
            int lastId = model.addEntry(name, description);
            std::cout << "New task ID: " << lastId << std::endl;
            std::cout << "Entry added successfully!" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "ERROR occurred. Entry not added." << std::endl;
            std::cerr << "  Message: " << e.what() << std::endl;
        }
    } else if (std::string("list") == command) {
        std::cout << "YATTT -- LIST command" << std::endl;
        auto list = model.listTasks();
        if (list.size() > 0) {
            std::cout << std::left << std::setfill('-') << std::setw(7) << '+' << std::setw(20) << '+' << std::setw(50) << '+' << std::setw(30) << '+' << std::setw(30) << '+' << std::setw(20) << '+' << '+' << std::endl;
            std::cout << "| " << std::left << std::setfill(' ') << std::setw(4) << "ID";
            std::cout << " | " << std::left << std::setfill(' ') << std::setw(17) << "Name";
            std::cout << " | " << std::left << std::setfill(' ') << std::setw(47) << "Description";
            std::cout << " | " << std::left << std::setfill(' ') << std::setw(27) << "Starting time";
            std::cout << " | " << std::left << std::setfill(' ') << std::setw(27) << "Ending time";
            std::cout << " | " << std::left << std::setfill(' ') << std::setw(17) << "Status" << " |" << std::endl;
            std::cout << std::left << std::setfill('-') << std::setw(7) << '+' << std::setw(20) << '+' << std::setw(50) << '+' << std::setw(30) << '+' << std::setw(30) << '+' << std::setw(20) << '+' << '+' << std::endl;
            for(auto task : list) {
                std::cout << "| " << std::right << std::setfill('0') << std::setw(4) << task.id << ' ';
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(17) << task.name << ' ';
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(47) << task.description << ' ';
                std::time_t time = task.startingTimestamp;
                std::string timeStr = std::asctime(std::localtime(&time));
                timeStr.pop_back();
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(27) << timeStr << ' ';
                if (task.status == "FINISHED") {
                    time = task.endingTimestamp;
                    timeStr = std::asctime(std::localtime(&time));
                    timeStr.pop_back();
                } else {
                    timeStr = "";
                }
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(27) << timeStr << ' ';
                std::cout << "| " << std::left << std::setfill(' ') << std::setw(17) << task.status << ' ';
                std::cout << "|" << std::endl;
            }
            std::cout << std::left << std::setfill('-') << std::setw(7) << '+' << std::setw(20) << '+' << std::setw(50) << '+' << std::setw(30) << '+' << std::setw(30) << '+' << std::setw(20) << '+' << '+' << std::endl;
        } else {
            std::cout << "No tasks found." << std::endl;
        }
    } else if (std::string("stop") == command) {
        if (argc < 3) {
            std::cout << "STOP command usage: yattt.exe stop <id>" << std::endl;
            std::cout << " - <id> is mandatory" << std::endl;
            return EXIT_SUCCESS;
        }

        std::cout << "YATTT -- STOP command" << std::endl;

        try {
            int id = std::atoi(argv[2]);
            model.stopTask(id);
            std::cout << "Task #" << std::setfill('0') << std::setw(4) << id << " marked as 'FINISHED'." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "ERROR occurred." << std::endl;
            std::cerr << "  Message: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Unknown command: " << command << std::endl;
    }

    return EXIT_SUCCESS;
}
