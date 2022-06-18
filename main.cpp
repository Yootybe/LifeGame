#include "FieldProcessor.h"
#include <iostream>

#define ESCAPE_KEY 27
#define SPACE_KEY  32
#define CTRL_D     -1

int main()
{
    FieldProcessor fp;

    short key = getchar();
    while (key != CTRL_D)
    {
        if (key == SPACE_KEY)
            fp.newGenerationProcessing();

        if (key == ESCAPE_KEY)
            fp.checkGameStatus();

        key = getchar();
    }

    fp.checkGameStatus();

    return 0;
}