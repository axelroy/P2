#include "deadlist.h"
#include <QMutex>
#include <QList>
#include <QMutexLocker>
#include <QDebug>


/*============================================*/
//  STATIC
/*============================================*/

QMutex DeadList::mutex;
QList<Cell *> DeadList::cellList;

void DeadList::addCell(Cell *c)
{
    QMutexLocker locker(&mutex);

    if(c != 0)
        cellList.append(c);
}

Cell *DeadList::getCell()
{
    QMutexLocker locker(&mutex);

    Cell *tmp  = 0;
    if(!cellList.isEmpty())
    {
        tmp = cellList.back();
        cellList.pop_back();
    }

    return tmp;
}

bool DeadList::isEmpty()
{
    QMutexLocker locker(&mutex);

    return cellList.isEmpty();
}

int DeadList::getSize()
{
    QMutexLocker locker(&mutex);

    return cellList.count();
}
