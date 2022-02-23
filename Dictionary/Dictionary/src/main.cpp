#include "Dictionary/Dictionary.h"

#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        puza::Dictionary dict;
        dict.load(argv[1]);
        dict.parse(argv[2]);
    }

    return 0;
}