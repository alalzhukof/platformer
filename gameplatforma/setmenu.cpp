#include "setmenu.hpp" // header in local directory
#include <iostream>	   // header in standard library

setMenu::setMenu()
{
	for (int i = 0; i < 5; i++)
		pusklever[i] = false;

	blv[0] = true;
	for (int i = 1; i < 5; i++)
		blv[i] = false;
}
