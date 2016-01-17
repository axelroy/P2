#include "utility.h"
#include <QtGlobal>

/*============================================*/
//  STATIC
/*============================================*/

int Utility::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}

int Utility::polarizedRandInt(int low, int high)
{
    if(randInt(0,1) == 0){
        return randInt(low, high);
    }
    else
        return -randInt(low, high);
}
