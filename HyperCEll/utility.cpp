#include "utility.h"

Utility::Utility()
{

}

int Utility::randInt(int low, int high)
{

    int a = qrand() % ((high + 1) - low) + low;

    //qDebug() << a << "\n";
    // Random number between low and high
    return a;

}
