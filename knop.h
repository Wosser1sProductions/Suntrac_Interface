#ifndef KNOP
#define KNOP
#include "display.h"
#include <string>
#include <list>

using namespace std;

class knop
{
	public:
		knop(int ID);
		knop(string button);

		int ID						= -1;
		string button				= "    ";
		list<display*> *karakters	= nullptr;
};

#endif // KNOP
