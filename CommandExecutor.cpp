#include "CommandExecutor.h"

// Конструктор по умолчанию
CommandExecutor::CommandExecutor() {}

void CommandExecutor::setCommand(Command* cmd) {
    command = cmd;
}

void CommandExecutor::executeCommand() {
    command->execute();
}
