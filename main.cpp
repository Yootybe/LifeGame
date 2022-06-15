#include "FieldProcessor.h"

#define ESCAPE_KEY 27
#define SPACE_KEY  32

int main()
{
    FieldProcessor fp;

    short key = getchar();
    while (key != ESCAPE_KEY)
    {
        if (key == SPACE_KEY)
        {
            fp.newGenerationProcessing();
        }
        key = getchar();
    }

    return 0;
}