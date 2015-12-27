#include <iostream>
#include <display.h>
#include <string.h>

using namespace std;

display::display(int karakters)
	:karakters(karakters)
{

}

void display::printkarakters()
{
	printf("%3d", this->karakters);
}
