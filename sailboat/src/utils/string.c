#include "string.h"
#include <string.h>

void safer_stringcopy(char* destination, u64 destinationSize, char* source)
{
    u64 sourceSize = strlen(source);
    if(sourceSize > destinationSize)
        sourceSize = destinationSize - 1;

    memmove(destination, source, sourceSize);
    destination[sourceSize] = '\0';
}