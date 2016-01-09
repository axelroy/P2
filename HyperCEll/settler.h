#ifndef SETTLER_H
#define SETTLER_H

#include <QThread>
#include <QGraphicsScene>

#include <cell.h>
#include <utility.h>
#include <QDebug>
#include <QtCore/qmath.h>

class Settler : public QThread
{
private:
    double rangeMin;
    double rangeMax;
    Cell* refCell;
    Cell* cellTreated;
    int randomTypeCell;

public:
    Settler(double rangeMin, double rangeMax, Cell* refCell);
    ~Settler();
    void settle();

    static int ProbMalusCell;
    static int ProbBonusCell;

};

#endif // SETTLER_H
