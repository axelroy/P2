/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : Settler
 * Resumé           : peuple l'aire de jeu
 * version          : 0.0
 */

#ifndef SETTLER_H
#define SETTLER_H

#include <cell.h>
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
    void initSettle(CustomScene *map, int nbCells);
};

#endif // SETTLER_H
