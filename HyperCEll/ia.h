#ifndef IA_H
#define IA_H

#include "cell.h"
#include "collider.h"
#include "customscene.h"
#include "config.h"
#include <QtCore/qmath.h>
#include "QSemaphore"


class Ia : public QThread
{
public:
    Ia(CustomScene* map,Cell* iaCell);
    void run();
    void move();
    QSemaphore sem_control;



    char getDirection() const;

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
