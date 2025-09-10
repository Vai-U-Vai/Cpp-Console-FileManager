#include "Command.h"
#include "Input.h"
#include"Menu.h"
#include <iostream>
#include <filesystem>  
#include <regex>
#include <cstdlib>

namespace fs = std::filesystem;  // Создайте псевдоним для пространства имен std::filesystem
using namespace std;

Command::Command()  {}
    string Command::getName() {      
            return fileName_;       
}

    void Command::setName(string name)
    {
        fileName_ = name;
    }
    

    // ---------------------------------------------- РАБОТА С ФАЙЛАМИ ----------------------------------------------

    //-------------------------------------------------- Создать файл

void CreateFileCommand::execute() {
    string name = Input::name("файла");
    /*cout << "Введите имя: ";
    cin >> name;*/
    setName(name);
    std::ofstream file(fileName_);
    if (file.is_open()) {
        std::cout << "Файл успешно создан." << std::endl;
        // Закрываем файл после использования
        file.close();
    }
    else {
        std::cout << "Ошибка при создании файла." << std::endl;
    }
}

//------------------------------------------------- Показать содержимое файла

void ShowFileContentCommand::execute() {
    string filename = Input::name("файла");
    ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::cout << line << std::endl;
        }
        file.close();
    }
    else {
        std::cerr << "Не удалось открыть файл." << std::endl;
    }


}

//CreateDirCommand::CreateDirCommand() : Command() {}
void WrightFileContent::execute()
{
    string text;
    string name = Input::name("файла");
    
    // Открыть файл для записи с перезаписью
    std::ofstream outFile(name);

    if (outFile.is_open()) {
        cout << "Введите текст:\n";
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
       getline(cin, text);
        outFile << text;
        outFile.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }
}

void WrightFileEnd::execute()
{
    string text;
    string name = Input::name("файла");
    std::ofstream f(name, ios::app);
    if (f.is_open()) {
        cout << "Введите текст:\n";
        cin >> text;
        f << text;
        f.close();
    }
    else {
        std::cerr << "Не удалось открыть файл для записи.\n";
    }
}

void Rename::execute()
{
    string name, nameNew;
    cout << "Какой файл/папку переименовать/переместить: ";
    cin >> name;
    cout << "Введите новое имя или путь: ";
    cin >> nameNew;

    // Определяем старый и новый пути
    fs::path oldPath = name;
    fs::path newPath = nameNew;

    try {
        fs::rename(oldPath, newPath);

        std::cout << "Файл/директория успешно переименованы." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при переименовании: " << e.what() << std::endl;
    }

    
}

void Del::execute()
{
    fs::path filePath = Input::path("к файлу/папке для удаления");

    try {
        if (fs::is_directory(filePath)) {
            if (!fs::is_empty(filePath)) {
                // Если это директория и она не пуста, предупредите пользователя и спросите о продолжении.
                std::cout << "Директория не пуста. Вы уверены, что хотите продолжить удаление? (y/n): ";
                std::string userInput;
                std::cin >> userInput;

                if (userInput == "y") {
                    fs::remove_all(filePath);
                    std::cout << "Директория успешно удалена." << std::endl;
                }
                else {
                    std::cout << "Удаление отменено." << std::endl;
                }
            }
            else {
                fs::remove(filePath);
                std::cout << "Директория успешно удалена." << std::endl;
            }
        }
        else {
            fs::remove(filePath);
            std::cout << "Файл успешно удален." << std::endl;
        }
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при удалении: " << e.what() << std::endl;
    }
}

void SizeFile::execute()
{
    // Задайте путь к файлу, размер которого вы хотите узнать
    fs::path filePath = Input::path();

    try {
        // Получите размер файла с помощью функции file_size()
        std::uintmax_t fileSize = fs::file_size(filePath);

        std::cout << "Размер файла: " << fileSize << " байт" << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при получении размера файла: " << e.what() << std::endl;
    }
}




//--------------------------------------------------- РАБОТА С ПАПКАМИ ---------------------------------------------

//------------------------------------------------------ Создать папку 

void CreateDirCommand::execute() {
    string dirName = Input::name("папки");
    setName(dirName);
    if (fs::create_directory(dirName)) {  
        cout << "Директория успешно создана." << std::endl;
    }
    else {
        cout << "Ошибка при создании директории." << std::endl;
    }
}

//-------------------------------------------------- Показать содержимое папки


void ShowDirContentCommand::execute()
{
    std::filesystem::path pathToDirectory = Input::path();
        // In::path(); /*"D:/Программы/Проекты VS/FileManager"*/;
    if (std::filesystem::is_directory(pathToDirectory)) {
        for (const auto& entry : std::filesystem::directory_iterator(pathToDirectory)) {
            std::cout << entry.path().filename() << std::endl;
        }
    }
    else {
        std::cerr << "Указанная директория не существует." << std::endl;
    }
    
}

void CopyF::execute()
{
    fs::path sourcePath = Input::path("к исходному файлу/папке");

    // Задайте путь, куда вы хотите скопировать
    fs::path destinationPath = Input::path("к целевому файлу/папке");

    try {
        // Вызовите функцию copy()
        fs::copy(sourcePath, destinationPath);

        std::cout << "Файл или директория успешно скопированы." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при копировании: " << e.what() << std::endl;
    }
}



void CopyDir::copyDirectory(const fs::path& sourceDir, const fs::path& destinationDir)
{
    fs::create_directory(destinationDir); // Создать целевую директорию

    for (const auto& entry : fs::directory_iterator(sourceDir)) {
        fs::path currentPath = entry.path();
        fs::path destinationPath = destinationDir / currentPath.filename();

        if (fs::is_directory(currentPath)) {
            // Если это директория, рекурсивно скопируйте её
            copyDirectory(currentPath, destinationPath);
        }
        else if (fs::is_regular_file(currentPath)) {
            // Если это файл, скопируйте его
            fs::copy(currentPath, destinationPath);
        }
    }
}

void CopyDir::execute()
{
    string destinationDir = Input::path(" куда копируем папку");
    string sourceDir = Input::path(" откуда копируем папку");

    try {
        copyDirectory(sourceDir, destinationDir);
        std::cout << "Директория успешно скопирована." << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при копировании: " << e.what() << std::endl;
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
        std::cout << "Размер директории: " << size << " байт" << std::endl;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << "Ошибка при определении размера директории: " << e.what() << std::endl;
    }

}

bool SearchWithMask::matchMask(const std::string& filename, const std::string& mask)
{
    std::string regexPattern = "^" + mask; // Начинаем с начала строки
    regexPattern = std::regex_replace(regexPattern, std::regex("\\."), "\\."); // Экранируем точки
    regexPattern = std::regex_replace(regexPattern, std::regex("\\*"), ".*"); // Заменяем * на .* (ноль или более символов)
    regexPattern = std::regex_replace(regexPattern, std::regex("\\?"), "."); // Заменяем ? на . (один символ)

    // Добавьте завершающий символ $ и создайте объект regex
    regexPattern += "$";
    std::regex pattern(regexPattern);

    // Сопоставляем имя файла с маской
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
    cout << "\nВыход из программы." << std::endl;
    exit(0);
}

void Help::execute()
{
    cout << "\nСписок команд:\n";
    cout << "crf - Создать файл\n";
    cout << "wr - Записать в файл с перезаписью\n";
    cout << "wrend - Записать в конец файла \n";
    cout << "shf - Показать содержимое файла\n";
    cout << "sizef - Размер файла\n";
    cout << "del - Удалить файл/папку\n";
    cout << "ren - Переименовать/переместить файл/папку\n";
    cout << "copyf - Скопировать файл\n";
    cout << "sch - Найти файл/папку\n";
    cout << "crd - Создать папку\n";
    cout << "shd - Показать содержммое папки\n";
    cout << "sized - Размер папки\n";
    cout << "copyd - Скопировать папку\n";
    cout << "help - Показать список команд с расшифровкой\n";
    cout << "exit - Выход\n";
}
