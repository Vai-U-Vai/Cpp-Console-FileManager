#include "CommandExecutor.h"

// ����������� �� ���������
CommandExecutor::CommandExecutor() {}

void CommandExecutor::setCommand(Command* cmd) {
    command = cmd;
}

void CommandExecutor::executeCommand() {
    command->execute();
}
