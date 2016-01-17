#ifndef CUSTOMSCENE_H
#define CUSTOMSCENE_H

#include <QGraphicsScene>
#include <cell.h>
#include <QtDebug>

class CustomScene: public QGraphicsScene
{
public:
    CustomScene(QObject * parent = 0);

    void MoveCell(double x, double y, Cell * cell);
};

#endif // CUSTOMSCENE_H
