#ifndef IA_H
#define IA_H

#include "cell.h"
#include "collider.h"
#include "customscene.h"
#include <QtCore/qmath.h>


class Ia : public QThread
{
public:
    Ia(CustomScene* map,Cell* iaCell);
    void run();
    void move();



protected:
    Cell* iaCell;
    Cell* target;
    Cell* fetch;
    Collider* iaCellCollider;
    double nextX;
    double nextY;
    CustomScene* map;

    Cell* selectTarget(Cell* proTarget);


};

#endif // IA_H
