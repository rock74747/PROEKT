
#include "File.h"


uintmax_t File::delete_D(const std::string& name)
{
    try {
        std::uintmax_t n = std::filesystem::remove(name);
        return n;
    }
    catch (std::filesystem::filesystem_error e) {
        std::cout << "Code: " << e.code()
            << "\nError: " << e.what() << std::endl;
    }
}
