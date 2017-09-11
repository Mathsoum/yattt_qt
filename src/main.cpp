#include "include/model/dbmodel.h"

#include <iostream>
#include <string>

int main(int argc, char *argv[])
{
    std::cout << "YATTT -- Yet Another Time-Tracking Tool" << std::endl;
    std::cout << "#######################################" << std::endl << std::endl;
    if (argc < 2) {
        std::cout << "Usage: yattt.exe (add|list) [<name> <description>]" << std::endl;
        return EXIT_SUCCESS;
    }

    if (std::string("add") == argv[1]) {
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
            DBModel model;
            model.addEntry(name, description);
            std::cout << "Entry added successfully!";
        } catch (const std::exception& e) {
            std::cerr << "ERROR occurred. Entry not added." << std::endl;
            std::cerr << "  Message: " << e.what() << std::endl;
        }
    } else {
        std::cout << "Unknown command: " << argv[1] << std::endl;
    }

    return EXIT_SUCCESS;
}
