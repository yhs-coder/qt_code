#include "MySlot.h"
#include <iostream>

void MySlot::eat()
{
	std::cout << "ÇëÄã³Ô¸öÅÝÃæ..." << std::endl;
}

void MySlot::eat(std::string msg)
{
	std::cout << "ÇëÄã³Ô£º" << msg << std::endl;
}
