#include "Dictionary/Corrector.h"

int main(int, char* argv[])
{
    puza::Corrector corr;
    corr.load(argv[1]);
    corr.parse(argv[2]);

    return 0;
}