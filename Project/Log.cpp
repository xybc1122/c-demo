#include<iostream>
#include "Log.h"

void InitLog(const char* msg) {
	Log(msg);
}


void Log(const char* msg) {
		std::cout << msg << std::endl;
}