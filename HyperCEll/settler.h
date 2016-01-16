#ifndef SETTLER_H
#define SETTLER_H

#include <QGraphicsScene>

#include <cell.h>
#include <ia.h>
#include <utility.h>
#include <QDebug>
#include <QtCore/qmath.h>

#include "config.h"

class Settler
{
private:
    double rangeMin;
    double rangeMax;
    Cell* refCell;
    Cell* cellTreated;
    int randomTypeCell;

    Ia* iaiaiaia;

public:
    Settler(double rangeMin, double rangeMax, Cell* refCell);
    ~Settler();
    void settle();

    static int ProbMalusCell;
    static int ProbBonusCell;

};

#endif // SETTLER_H
