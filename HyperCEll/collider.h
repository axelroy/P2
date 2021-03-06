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



    void update();
    QList<QGraphicsItem*> nearList;

    char getAutorizedDirection() const;
    void setAutorizedDirection(char value);

private:
    QList<Cell*> collidingCells;
    CustomScene* map;
    Cell* refCell;
    Cell * c;
    QGraphicsItem* e;
    QGraphicsItem* s;
    qreal area;
    char autorizedDirection;

};

#endif // COLLIDER_H
