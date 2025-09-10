#include "Command.h"
#include "Input.h"
#include"Menu.h"
#include <iostream>
#include <filesystem>  
#include <regex>
#include <cstdlib>

namespace fs = std::filesystem;  // �������� ��������� ��� ������������ ���� std::filesystem
using namespace std;

Command::Command()  {}
    string Command::getName() {      
            return fileName_;       
}

    void Command::setName(string name)
    {
        fileName_ = name;
    }
    

    // ---------------------------------------------- ������ � ������� ----------------------------------------------

    //-------------------------------------------------- ������� ����

void CreateFileCommand::execute() {
    string name = Input::name("�����");
    /*cout << "������� ���: ";
    cin >> name;*/
    setName(name);
    std::ofstream file(fileName_);
    if (file.is_open()) {
        std::cout << "���� ������� ������." << std::endl;
        // ��������� ���� ����� �������������
        file.close();
    }
    else {
        std::cout << "������ ��� �������� �����." << std::endl;
    }
}

//------------------------------------------------- �������� ���������� �����

void ShowFileContentCommand::execute() {
    string filename = Input::name("�����");
    ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "�� ������� ������� ����." << std::endl;
    }


}

//CreateDirCommand::CreateDirCommand() : Command() {}
void WrightFileContent::execute()
{
    string text;
    string name = Input::name("�����");
    
    // ������� ���� ��� ������ � �����������
    std::ofstream outFile(name);

    if (outFile.is_open()) {
        cout << "������� �����:\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       getline(cin, text);
        outFile << text;
        outFile.close();
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������.\n";
    }
}

void WrightFileEnd::execute()
{
    string text;
    string name = Input::name("�����");
    std::ofstream f(name, ios::app);
    if (f.is_open()) {
        cout << "������� �����:\n";
        cin >> text;
        f << text;
        f.close();
    }
    else {
        std::cerr << "�� ������� ������� ���� ��� ������.\n";
    }
}

void Rename::execute()
{
    string name, nameNew;
    cout << "����� ����/����� �������������/�����������: ";
    cin >> name;
    cout << "������� ����� ��� ��� ����: ";
    cin >> nameNew;

    // ���������� ������ � ����� ����
    fs::path oldPath = name;
    fs::path newPath = nameNew;

    try {
        fs::rename(oldPath, newPath);

        std::cout << "����/���������� ������� �������������." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� ��������������: " << e.what() << std::endl;
    }

    
}

void Del::execute()
{
    fs::path filePath = Input::path("� �����/����� ��� ��������");

    try {
        if (fs::is_directory(filePath)) {
            if (!fs::is_empty(filePath)) {
                // ���� ��� ���������� � ��� �� �����, ������������ ������������ � �������� � �����������.
                std::cout << "���������� �� �����. �� �������, ��� ������ ���������� ��������? (y/n): ";
                std::string userInput;
                std::cin >> userInput;

                if (userInput == "y") {
                    fs::remove_all(filePath);
                    std::cout << "���������� ������� �������." << std::endl;
                }
                else {
                    std::cout << "�������� ��������." << std::endl;
                }
            }
            else {
                fs::remove(filePath);
                std::cout << "���������� ������� �������." << std::endl;
            }
        }
        else {
            fs::remove(filePath);
            std::cout << "���� ������� ������." << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� ��������: " << e.what() << std::endl;
    }
}

void SizeFile::execute()
{
    // ������� ���� � �����, ������ �������� �� ������ ������
    fs::path filePath = Input::path();

    try {
        // �������� ������ ����� � ������� ������� file_size()
        std::uintmax_t fileSize = fs::file_size(filePath);

        std::cout << "������ �����: " << fileSize << " ����" << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� ��������� ������� �����: " << e.what() << std::endl;
    }
}




//--------------------------------------------------- ������ � ������� ---------------------------------------------

//------------------------------------------------------ ������� ����� 

void CreateDirCommand::execute() {
    string dirName = Input::name("�����");
    setName(dirName);
    if (fs::create_directory(dirName)) {  
        cout << "���������� ������� �������." << std::endl;
    }
    else {
        cout << "������ ��� �������� ����������." << std::endl;
    }
}

//-------------------------------------------------- �������� ���������� �����


void ShowDirContentCommand::execute()
{
    std::filesystem::path pathToDirectory = Input::path();
        // In::path(); /*"D:/���������/������� VS/FileManager"*/;
    if (std::filesystem::is_directory(pathToDirectory)) {
        for (const auto& entry : std::filesystem::directory_iterator(pathToDirectory)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    else {
        std::cerr << "��������� ���������� �� ����������." << std::endl;
    }
    
}

void CopyF::execute()
{
    fs::path sourcePath = Input::path("� ��������� �����/�����");

    // ������� ����, ���� �� ������ �����������
    fs::path destinationPath = Input::path("� �������� �����/�����");

    try {
        // �������� ������� copy()
        fs::copy(sourcePath, destinationPath);

        std::cout << "���� ��� ���������� ������� �����������." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� �����������: " << e.what() << std::endl;
    }
}



void CopyDir::copyDirectory(const fs::path& sourceDir, const fs::path& destinationDir)
{
    fs::create_directory(destinationDir); // ������� ������� ����������

    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        fs::path currentPath = entry.path();
        fs::path destinationPath = destinationDir / currentPath.filename();

        if (fs::is_directory(currentPath)) {
            // ���� ��� ����������, ���������� ���������� �
            copyDirectory(currentPath, destinationPath);
        }
        else if (fs::is_regular_file(currentPath)) {
            // ���� ��� ����, ���������� ���
            fs::copy(currentPath, destinationPath);
        }
    }
}

void CopyDir::execute()
{
    string destinationDir = Input::path(" ���� �������� �����");
    string sourceDir = Input::path(" ������ �������� �����");

    try {
        copyDirectory(sourceDir, destinationDir);
        std::cout << "���������� ������� �����������." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� �����������: " << e.what() << std::endl;
    }
}

std::uintmax_t SizeDir::calculateDirectorySize(const fs::path& dirPath)
{
    std::uintmax_t totalSize = 0;

    for (const auto& entry : fs::recursive_directory_iterator(dirPath)) {
        if (fs::is_regular_file(entry)) {
            totalSize += fs::file_size(entry);
        }
    }

    return totalSize;
}

void SizeDir::execute()
{
    fs::path directoryPath = Input::path();

    try {
        std::uintmax_t size = calculateDirectorySize(directoryPath);
        std::cout << "������ ����������: " << size << " ����" << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "������ ��� ����������� ������� ����������: " << e.what() << std::endl;
    }

}

bool SearchWithMask::matchMask(const std::string& filename, const std::string& mask)
{
    std::string regexPattern = "^" + mask; // �������� � ������ ������
    regexPattern = std::regex_replace(regexPattern, std::regex("\\."), "\\."); // ���������� �����
    regexPattern = std::regex_replace(regexPattern, std::regex("\\*"), ".*"); // �������� * �� .* (���� ��� ����� ��������)
    regexPattern = std::regex_replace(regexPattern, std::regex("\\?"), "."); // �������� ? �� . (���� ������)

    // �������� ����������� ������ $ � �������� ������ regex
    regexPattern += "$";
    std::regex pattern(regexPattern);

    // ������������ ��� ����� � ������
    return std::regex_match(filename, pattern);
}

void SearchWithMask::execute()
{
    string directoty = Input::path();
    string mask = Input::mask();
    for (const auto& entry : fs::recursive_directory_iterator(directoty)) {
        if (entry.is_regular_file()) {
            std::string filename = entry.path().filename().string();
            if (matchMask(filename, mask)) {
                std::cout << entry.path() << std::endl;
            }
        }
    }
}

void ExitCommand::execute()
{
    cout << "\n����� �� ���������." << std::endl;
    exit(0);
}

void Help::execute()
{
    cout << "\n������ ������:\n";
    cout << "crf - ������� ����\n";
    cout << "wr - �������� � ���� � �����������\n";
    cout << "wrend - �������� � ����� ����� \n";
    cout << "shf - �������� ���������� �����\n";
    cout << "sizef - ������ �����\n";
    cout << "del - ������� ����/�����\n";
    cout << "ren - �������������/����������� ����/�����\n";
    cout << "copyf - ����������� ����\n";
    cout << "sch - ����� ����/�����\n";
    cout << "crd - ������� �����\n";
    cout << "shd - �������� ���������� �����\n";
    cout << "sized - ������ �����\n";
    cout << "copyd - ����������� �����\n";
    cout << "help - �������� ������ ������ � ������������\n";
    cout << "exit - �����\n";
}
