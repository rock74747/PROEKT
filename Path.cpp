
#include "Path.h"



void Manager::showMenu(stringvec& v, stringvec& s) {
    v.clear();
    s.clear();
    int n;
    std::string dl;
    DWORD dr = GetLogicalDrives(); // функция возвращает битовую маску

    for (int x = 0; x < 26; x++) // проходимся циклом по битам
    {
        n = ((dr >> x) & 1); // узнаём значение текущего бита
        if (n) // если единица - диск с номером x есть
        {
            dl = ((char)(65 + x)); // получаем литеру диска
            std::cout << "Диск " + dl + "\n";
             v.push_back(dl+":"+"\\"); // пишем в вектор
        }
    }
}

std::string Manager::directory_name(stringvec& v, int& a)
{
    std::string name = v.at(a);
    return name;
}

void Manager::gotoxy(short x, short y)
{
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { x,y });
}

void Manager::dirfileinfo (stringvec& v, int& activeMenuItem, stringvec& s)
{
        std::filesystem::path sistems{ Manager::directory_name(v, activeMenuItem) };
        if (s.size() == 0) {
            std::filesystem::space_info root = std::filesystem::space(sistems);
            std::cout << "Общий размер файловой системы: " << root.capacity << " байт" << "\n"
                << "Количество свободного места: " << root.free << " байт" <<"\n"
                << "Доступно: " << root.available << " байт" << std::endl;
        }
        else 
        if (is_directory(sistems)) {
            
            try {
                std::cout << "Имя директории: "<< sistems.stem() << '\n';
                std::vector<std::filesystem::path> files_and_folders { std::filesystem::recursive_directory_iterator(sistems),
                        std::filesystem::recursive_directory_iterator() };
                size_t folder_size = 0;
                int a = 0;
                int b = 0;
                for (const auto& path : files_and_folders)
                {
                    folder_size += std::filesystem::file_size(path);
                    if (is_directory(path))
                        a++;
                    else
                        b++;
                }
                std::cout << "Размер директории: " << folder_size << " bytes" << '\n'
                    << "Количество папок: " << a << '\n'
                    << "Количество файлов: " << b << std::endl;
                files_and_folders.clear();
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
        else {
            
            try {
                std::cout << "Имя файла: " << sistems.stem() << '\n'
                << "Разрешение файла: " << sistems.extension() << '\n';
                std::uintmax_t fileSize = std::filesystem::file_size(sistems);
                std::cout << "Размер файла: " << fileSize << " bytes" << std::endl;
            }
            catch (const std::filesystem::filesystem_error& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
            std::cout << "-------------------" << std::endl;
            std::cout << INFORM;
}
    



