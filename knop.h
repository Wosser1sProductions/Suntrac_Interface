#ifndef KNOP
#define KNOP
#include <string>

using namespace std;

class knop
{
    int ID;
    string button;
public:
    knop(int ID);
    knop(string button = "    ");
};

#endif // KNOP
