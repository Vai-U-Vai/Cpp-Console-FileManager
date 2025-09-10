#ifndef MENU_H
#define MENU_H
#include <iostream>
#include <map>
#include <string>
#include "Command.h"
using namespace std;
class Menu {
private:
    std::map<std::string, Command*> menuItems;

public:
    void addItem(const std::string& label, Command* command);
    void run();
};




#endif // MENU_H
