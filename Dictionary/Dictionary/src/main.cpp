#include "Dictionary/Corrector.h"
#include <cstring>

#define PRINT_ERROR(printer, message) \
    (printer).setMessage(message); \
    std::cout << (printer).getOutput(); \
    return -1;

int main(int argc, char* argv[])
{
    puza::Corrector corr;
    puza::Informer info(16);

    bool data_loading = true;
    for (int i = 1; i < argc; i++)
    {
        info.clearText();
        info.appendWord(argv[i]);

        if ((argv[i][0] == '-') && data_loading)
        {
            if (i == 1)
            {
                PRINT_ERROR(info, "Files for the dictionary are required");
            }

            if (strlen(argv[i]) > 2)
            {
                PRINT_ERROR(info, "Wrong mode");
            }

            switch(argv[i][1])
            {
            case '\0':
                corr.setMode(puza::Corrector::NO_OUTPUT);
                break;
            case 'o':
                corr.setMode(puza::Corrector::WITH_OUTPUT);
                break;
            case 's':
                corr.setMode(puza::Corrector::NO_CORRECTION);
                break;
            default:
                PRINT_ERROR(info, "Wrong mode");
            }

            data_loading = false;
        }
        else if (data_loading)
        {
            if (!corr.load(argv[i]))
            {
                PRINT_ERROR(info, "File not found");
            }
        }
        else
        {
            if (!corr.process(argv[i]))
            {
                PRINT_ERROR(info, "File not found");
            }
        }
    }

    return 0;
}