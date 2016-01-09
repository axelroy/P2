#ifndef BORDERGUARD_H
#define BORDERGUARD_H


#include <QThread>
#include "cell.h"
#include "customscene.h"


class Borderguard : public QThread
{
public:
    Borderguard(double area, Cell* refCell, CustomScene* map);
    void run();


private:
    double area;
    Cell* refCell;
    QGraphicsItem * controlledCell;
    CustomScene* map;
};


#endif // BORDERGUARD_H
