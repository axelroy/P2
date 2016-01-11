#ifndef COLLIDER_H
#define COLLIDER_H

#include "customscene.h"
#include <QThread>
#include <QGraphicsScene>
#include "cell.h"
#include <QDebug>
#include <QtGlobal>
#include <QtCore/qmath.h>


class Collider : public QThread
{
public:
    Collider(CustomScene* map, Cell* refCell);
    void run();

    static char autorizedDirection;
    QList<Cell*> collidingCells;
    void update();
    QList<QGraphicsItem*> nearList;

private:
    CustomScene* map;
    Cell* refCell;
    Cell * c;
    QGraphicsItem* e;
    QGraphicsItem* s;
    qreal area;



};

#endif // COLLIDER_H
