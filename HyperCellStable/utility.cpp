#include "utility.h"
#include <QtGlobal>

/*============================================*/
//  STATIC
/*============================================*/

int Utility::randInt(int low, int high)
{
    return qrand() % ((high + 1) - low) + low;
}
