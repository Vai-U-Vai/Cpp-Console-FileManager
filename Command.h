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


// ---------------------------------------------- ������ � ������� ----------------------------------------------

//-------------------------------------------------- ������� ����
class CreateFileCommand : public Command {
public:
    void execute() override;
};


//------------------------------------------------- �������� ���������� �����
class ShowFileContentCommand : public Command {
public:
    void execute() override;
};

//------------------------------------------------- ������ � ����(����������)

class WrightFileContent : public Command {
public:
    void execute() override;
    
};
//------------------------------------------------- ������ � ����� �����

class WrightFileEnd: public Command {
public:
    void execute() override;

};

//------------------------------------------------- �������������/����������� ����
class Rename : public Command {
public:
    void execute() override;

};

//------------------------------------------------- ������� ����

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

//--------------------------------------------------- ������ � ������� ---------------------------------------------

//------------------------------------------------------ ������� ����� 

class CopyDir : public Command {
private:
   void copyDirectory(const fs::path& sourceDir, const fs::path& destinationDir);
public:
    void execute() override;
};

//------------------------------------------------------ ������� ����� 
class CreateDirCommand : public Command {
public:
    void execute() override;
};
//-------------------------------------------------- �������� ���������� �����
class ShowDirContentCommand : public Command {
public:
    void execute() override;
    
};

//-------------------------------------------------- �������� ������ �����
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





