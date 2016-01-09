#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <cell.h>
#include <QtDebug>

class CustomScene: public QGraphicsScene
{
public:
    CustomScene();

    void MoveCell(double x, double y, Cell * cell);
    void Ouaf();
};

#endif // CUSTOMSCENE_H
