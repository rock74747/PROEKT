
#include "Disk.h"



void Directory:: read_directory(const std::string& name, stringvec& v)
{
    try {
        v.clear();
        std::filesystem::path p(name);
        std::filesystem::directory_iterator start(p);
        std::filesystem::directory_iterator end;
        std::transform(start, end, std::back_inserter(v), path_leaf_string());
    }
    catch (std::filesystem::filesystem_error e) {
        std::cout << "Code: " << e.code()
            << "\nError: " << e.what() << std::endl;
    }
}

uintmax_t Directory::delete_D(const std::string& name)
{
    try {
        std::uintmax_t n = std::filesystem::remove_all(name);
        return n;
    }
    catch (std::filesystem::filesystem_error e) {
        std::cout << "Code: " << e.code()
            << "\nError: " << e.what() << std::endl;
    }
}

void Directory::create_directory(const std::string& name) {
    if (std::filesystem::exists(name))
    {
        std::cout << "Директория с таким именем уже существует" << std::endl;
    }
    else
        try {
        if (std::filesystem::create_directory(name))
            std::cout << "Директория создана" << std::endl;;
        }
        catch (std::filesystem::filesystem_error ec) {
            std::cout << "Code: " << ec.code()
                << "\nError: " << ec.what() << std::endl;
        }
}
        
void Directory::open_directory(stringvec& v) {
    if (v.size() > 0) {
        for (int i = 0; i < v.size(); i++) {
            std::filesystem::path pathToDisplay{ v[i] };
            std::cout << pathToDisplay.filename().string () << std::endl;
        }
    }
    else
        std::cout << "Пустая директория" << std::endl;
}

std::string Directory::path_leaf_string::operator()(const std::filesystem::directory_entry& entry) const
{
    return entry.path().string();
}


