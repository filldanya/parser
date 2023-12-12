#include <iostream>
#include "par.h"



int main()
{
	try
	{
		iniParser pars1("test.ini");
		std::cout << pars1.getValue<float>("Section2", "var1") << std::endl << std::endl;
	}
	catch (std::runtime_error ex)
	{
		std::cout << ex.what();
	}
}

