#include "MySlot.h"
#include <iostream>

void MySlot::eat()
{
	std::cout << "����Ը�����..." << std::endl;
}

void MySlot::eat(std::string msg)
{
	std::cout << "����ԣ�" << msg << std::endl;
}
