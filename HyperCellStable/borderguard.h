/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : Borderguard
 * Resumé           : gère les cellules qui sont trop loin du joueur
 * version          : 0.0
 */

#ifndef BORDERGUARD_H
#define BORDERGUARD_H


#include <QThread>
#include "cell.h"
#include "customscene.h"


class Borderguard : public QThread
{
public:
    Borderguard(Cell* refCell, CustomScene* map);
    ~Borderguard();
    void run();
    void setArea(double value);


private:
    double area;
    Cell* refCell;
    CustomScene* map;
    void refreshArea();
    double scaledArea;
};


#endif // BORDERGUARD_H
