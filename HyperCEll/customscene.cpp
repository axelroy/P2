#include "customscene.h"

CustomScene::CustomScene()
{

}

void CustomScene::MoveCell(double x, double y, Cell * cell)
{
    cell->moveBy(x, y);

}

void CustomScene::Ouaf()
{
    qDebug() << "Ouaf";
}
