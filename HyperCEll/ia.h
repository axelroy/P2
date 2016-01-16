#ifndef IA_H
#define IA_H

#include <QAtomicPointer>

#include "cell.h"
#include "collider.h"
#include "customscene.h"
#include "config.h"
#include <QtCore/qmath.h>
#include "QSemaphore"


class Ia : public QThread, public Cell
{
public:
    Ia(CustomScene* map);
    void run();
    QSemaphore sem_control;

    char getDirection() const;

    Collider *getIaCellCollider() const;

    void activate();
private:
    Cell* iaCell;
    Cell* target;
    Cell* fetch;
    Collider* iaCellCollider;
    double nextX;
    double nextY;
    CustomScene* map;
    char direction;

    Cell* selectTarget(Cell* proTarget);


};

#endif // IA_H
