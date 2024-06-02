
#include <iostream>
#include <windows.h>
#include <string>
#include <conio.h>
#include <Stdio.h>
#include <vector> 
#include <filesystem> 

#include "Disk.h"
#include "Const.h"
#include "Path.h"
#include "File.h"


stringvec v;
stringvec s;

int main()
{
    system("chcp 1251>null");

label1:
    system("cls");
    const int NUM_MENU_ITEMS = 10000;
    int activeMenuItem = 0;
    int ch = 0;
    bool exit = false;
    Manager::showMenu(v, s);

    while (!exit)
    {
        Manager::gotoxy(0, activeMenuItem);
        // получение кода нажатой клавиши
        // при нажатии клавиш стрелок сначала идет код 224 и только потом код клавиши стрелю ch = _getch(); if (ch = 224)
        ch = _getch();
        if (ch == 224)
            ch = _getch();
        switch (ch)
        {
        case 27:	system("cls"); return 0;
        case 59:	exit = true;	break;
        case 72:	activeMenuItem--; break;	//	стрелка	вверх
        case 80:	activeMenuItem++; break;	//	стрелка	вниз 
        case 67:    system("cls");              // инструкция к программе
            Manager::gotoxy(0, 0);
            std::cout << COMMAND; break;
        case 68:    system("cls");              // информация о файле или директории
            Manager::gotoxy(0, 0);
            if (activeMenuItem >= 0) {
                Manager::dirfileinfo(v, activeMenuItem, s);
            }
            break;
        case 60:                                // создание директории
            if (activeMenuItem >= 0) {
                system("cls");
                Manager::gotoxy(0, 0);
                if (v.size() > 0) {
                    std::filesystem::path p{ Manager::directory_name(v, activeMenuItem) };
                    std::string Name = p.parent_path().string(); 
                    std::string input;
                    std::cout << "Введите имя каталога" << std::endl;
                    std::getline(std::cin, input);
                    Directory::create_directory(Name + "//" + input);
                }
                else
                {
                    std::filesystem::path p { s.at(s.size() - 1) };// создание директории в пустой директории
                    std::string Name = p.string();  
                    std::string input;
                    std::cout << "Введите имя каталога" << std::endl;
                    std::getline(std::cin, input);
                    Directory::create_directory(Name + "//" + input);
                }
                std::cout << "-------------------" << std::endl;
                std::cout << INFORM;
            }
            break;
        case 77:                               // следующая директория (итерация по директориям)
            if (activeMenuItem >= 0) {
                std::string Name = Manager::directory_name(v, activeMenuItem); // Получаем путь из вектора
                std::filesystem::path Directory{ Name };
                std::filesystem::file_status status = std::filesystem::status(Directory);
                if (is_directory(status)) {          // если директория
                    Directory::read_directory(Name, v); // Пишем в вектор открытую директорию
                    s.push_back(Name); // пишем полное имя пути в вектор для использования в функции "Назад"
                    system("cls");
                    Manager::gotoxy(0, activeMenuItem = 0);
                    Directory::open_directory(v);
                }
                else {
                    system("cls");
                    std::cout << "Не является директорией" << std::endl;
                    std::cout << "-------------------" << std::endl;
                    std::cout << INFORM;
                }
            } break;
        case 8:   system("cls");                            // Назад 
            if (s.size() > 0) {
                std::string Name = s.at(s.size() - 1);
                Directory::read_directory(Name, v);
                Directory::open_directory(v);
            }
            else
            {
                exit = true;
            }
            break;
        case 75:   system("cls");  // Назад в директорию (итерация по директориям)
            if (s.size() > 0) {
                s.pop_back();
            }
            if (s.size() > 0) {
                std::string Name = s.at(s.size() - 1);
                Manager::gotoxy(0, activeMenuItem = 0);
                Directory::read_directory(Name, v);
                Directory::open_directory(v);

            }
            else
            {
                exit = true;
            }
            break;
        case 83:                                          // удаление файла или директории
            if (activeMenuItem >= 0) {
                std::string Name = Manager::directory_name(v, activeMenuItem);
                system("cls");
                Manager::gotoxy(0, activeMenuItem = 0);
                std::filesystem::path Directory{ Name };
                std::filesystem::file_status status = std::filesystem::status(Directory);
                if (is_directory(status)) {  // если директория
                    std::cout << "Deleted " << Directory::delete_D(Name)
                        << " files or directories" << std::endl;
                    std::cout << "-------------------" << std::endl;
                    std::cout << INFORM;
                }
                else
                {
                    std::cout << "Deleted " << File::delete_D(Name)
                        << " files or directories" << std::endl;
                    std::cout << "-------------------" << std::endl;
                    std::cout << INFORM;
                }
            }break;
        }
        if (activeMenuItem < 0) activeMenuItem = 0;
    }
    goto label1;
}

