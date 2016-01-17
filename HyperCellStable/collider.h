/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : Collider
 * Resumé           : Gère les collisions entre les cellules
 * version          : 0.0
 */

#ifndef COLLIDER_H
#define COLLIDER_H

#include "customscene.h"
#include <QThread>
#include <QGraphicsScene>
#include "cell.h"
#include <QtGlobal>
#include <QtCore/qmath.h>

class Collider : public QThread
{
    Q_OBJECT

public:
    Collider(CustomScene* map, Cell* refCell);
    ~Collider();

    void run();

    void update();
    QList<QGraphicsItem*> nearList;

    char getAutorizedDirection() const;
    void setAutorizedDirection(char value);


public slots:
    void on_Controller_BlockMovement(bool block);

signals:
    void collision(Cell &c1, Cell &c2);



private:
    QList<Cell*> collidingCells;
    CustomScene* map;
    Cell* refCell;
    Cell * c;
    QGraphicsItem* e;
    QGraphicsItem* s;
    qreal area;
    char autorizedDirection;

    bool cellEatInteraction(double treashold, Cell &c1, Cell &c2);
};

#endif // COLLIDER_H
