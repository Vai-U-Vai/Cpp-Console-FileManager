/*Файловый менеджер должен иметь такие возможности:
■ показывать содержимое дисков; +
■ создавать папки/файлы; +
■ удалять папки/файлы;   +
■ переименовывать папки/файлы; +
■ копировать/переносить папки/файлы; +
■ вычислять размер папки/файла; 
■ производить поиск по маске (с поиском по подпапкам) и так далее.*/

#include <iostream>
#include <windows.h>
#include"Menu.h"
#include <string>
#include "Command.h"
#include "CommandExecutor.h"

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    // Создаем объекты для работы с файлами и списком файлов
    Menu mainMenu;
    CreateFileCommand createFileCommand;
    WrightFileContent wrightFileContent;
    ShowDirContentCommand showDirContentCommand;
    ShowFileContentCommand showFileContentCommand;
    CreateDirCommand createDirCommand;
    WrightFileEnd wrightFileEnd;
    SizeFile sizeFile;
    Rename renameFile;
    Del del;
    CopyF copyF;
    SizeDir sizeDir;
    CopyDir copyDir;
    SearchWithMask searchWithMask;
    ExitCommand exitCommand; 
    Help helpCommand;
    mainMenu.addItem("exit", &exitCommand);
    mainMenu.addItem("crf", &createFileCommand);
    mainMenu.addItem("wr", &wrightFileContent);
    mainMenu.addItem("ren", &renameFile);
    mainMenu.addItem("wrend", &wrightFileEnd);
    mainMenu.addItem("crd", &createDirCommand);
    mainMenu.addItem("shd", &showDirContentCommand);
    mainMenu.addItem("shf", &showFileContentCommand);
    mainMenu.addItem("sizef", &sizeFile);
    mainMenu.addItem("del", &del);
    mainMenu.addItem("copyf", &copyF);
    mainMenu.addItem("sized", &sizeDir);
    mainMenu.addItem("copyd", &copyDir);
    mainMenu.addItem("sch", &searchWithMask);
    mainMenu.addItem("help", &helpCommand);
    mainMenu.run();
    
}

