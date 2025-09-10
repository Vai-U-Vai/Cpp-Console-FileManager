
#include "Command.h"
//Класс предназначен для выполнения команд, но в данной прогпамме он,похоже, не нужен. Его функцию выполняет Menu.
class CommandExecutor {
private:
    Command* command;
   
public:
    CommandExecutor();
    void setCommand(Command* cmd);
    void executeCommand();
};


