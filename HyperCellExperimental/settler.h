#ifndef SETTLER_H
#define SETTLER_H

#include <cell.h>
#include <bot.h>
#include <utility.h>
#include <QtCore/qmath.h>

#include "config.h"

class CustomScene;

class Settler
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
    void initSettle(CustomScene *map, int nbCells, QList<Bot*> &bots, int nbBots);
};

#endif // SETTLER_H
