#pragma once

#ifndef DISK_H
#define DISK_H
#include <iostream>
#include <vector> 
#include <string> 
#include <filesystem> 
#include <algorithm>
#include "Const.h"
#include "Path.h"
#include <system_error>

class Directory : public Manager
{

public:
    static void read_directory(const std::string& name, stringvec& v);

    struct path_leaf_string
    {
        std::string operator()(const std::filesystem::directory_entry& entry) const;

    };
    static uintmax_t delete_D(const std::string& name);
    static void create_directory(const std::string& name);
    static void open_directory(stringvec& v);
    
private:
    

};


#endif DISK_H
















