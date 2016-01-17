#include "customscene.h"

CustomScene::CustomScene(QObject *parent) : QGraphicsScene(parent)
{

}

void CustomScene::MoveCell(double x, double y, Cell * cell)
{
    cell->moveBy(x, y);
}
