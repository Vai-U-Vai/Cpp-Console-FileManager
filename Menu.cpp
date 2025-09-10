#include"Menu.h"
#include<iostream>
#include<vector>


//Menu::Menu(const std::string& label) : Command(label) {}

void Menu::addItem(const std::string& label, Command* command) {
    menuItems[label] = command;
}

void Menu::run() {
    while (true) {
        std::cout << "\n�������: ";
        for (const auto& item : menuItems) {
            std::cout << item.first << ",";
        }
        std::cout << "\n�������� ��������: ";
        std::string choice;
        std::cin >> choice;
        if (menuItems.find(choice) != menuItems.end()) {
            menuItems[choice]->execute();
        }
        else {
            std::cout << "�������� �����. ���������� �����." << std::endl;
        }
    }
}



