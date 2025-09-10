#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
namespace fs = std::filesystem;
//ListFiles& lf, string& fn, const std::string& label

class Command {
public:
    Command();
    virtual void execute() = 0;
    string getName();
    void setName(string name);
protected:
    string fileName_;
};


// ---------------------------------------------- РАБОТА С ФАЙЛАМИ ----------------------------------------------

//-------------------------------------------------- Создать файл
class CreateFileCommand : public Command {
public:
    void execute() override;
};


//------------------------------------------------- Показать содержимое файла
class ShowFileContentCommand : public Command {
public:
    void execute() override;
};

//------------------------------------------------- Запись в файл(перезапись)

class WrightFileContent : public Command {
public:
    void execute() override;
    
};
//------------------------------------------------- Запись в конец файла

class WrightFileEnd: public Command {
public:
    void execute() override;

};

//------------------------------------------------- Переименовать/переместить файл
class Rename : public Command {
public:
    void execute() override;

};

//------------------------------------------------- Удалить файл

class Del: public Command {
public:
    void execute() override;

};

class CopyF : public Command{
public:
    void execute() override;
};

class SizeFile : public Command {
public:
    void execute() override;
};

class SearchWithMask : public Command {
private:
    bool matchMask(const std::string& filename, const std::string& mask);
public:
    void execute() override;
};

//--------------------------------------------------- РАБОТА С ПАПКАМИ ---------------------------------------------

//------------------------------------------------------ Создать папку 

class CopyDir : public Command {
private:
   void copyDirectory(const fs::path& sourceDir, const fs::path& destinationDir);
public:
    void execute() override;
};

//------------------------------------------------------ Создать папку 
class CreateDirCommand : public Command {
public:
    void execute() override;
};
//-------------------------------------------------- Показать содержимое папки
class ShowDirContentCommand : public Command {
public:
    void execute() override;
    
};

//-------------------------------------------------- Показать размер папки
class SizeDir : public Command {
private:
    std::uintmax_t calculateDirectorySize(const fs::path& dirPath);
public:
    void execute() override;
};

class ExitCommand : public Command {
public:
    void execute() override;
};

class Help : public Command {
public:
    void execute() override;
};





