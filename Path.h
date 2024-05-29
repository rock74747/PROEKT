#pragma once

#ifndef PATCH_H
#define PATCH_H
#include <iostream>
#include <windows.h>
#include <string>
#include <vector> 
#include <filesystem> 

#include "Const.h"






class Manager {
public:
	virtual uintmax_t delete_D() = 0;
	static void gotoxy(short x, short y);
	static void dirfileinfo(stringvec& v, int &activeMenuItem, stringvec& s);
	static void showMenu(stringvec& v, stringvec& s);
	static std::string directory_name(stringvec& v, int& a);
};


#endif PATCH_H


