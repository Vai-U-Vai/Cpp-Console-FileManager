
#include "Command.h"
//����� ������������ ��� ���������� ������, �� � ������ ��������� ��,������, �� �����. ��� ������� ��������� Menu.
class CommandExecutor {
private:
    Command* command;
   
public:
    CommandExecutor();
    void setCommand(Command* cmd);
    void executeCommand();
};


