#include "utility.h"
#include <QtGlobal>

#include <QDebug>

/*============================================*/
//  STATIC
/*============================================*/

int Utility::randInt(int low, int high)
{
    if((((high + 1) - low) + low) != 0)
        return qrand() % ((high + 1) - low) + low;
    else{
        qDebug() << "sale erreur";
        return 0;
    }
}

int Utility::polarizedRandInt(int low, int high)
{
    if(randInt(0,1) == 0){
        return randInt(low, high);
    }
    else
        return -randInt(low, high);
}
