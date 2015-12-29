#include "CustomScene.h"
#include <QtGlobal>
#include <QTime>

CustomScene::CustomScene()
{

}

void CustomScene::MoveCell(double x, double y, Cell * cell)
{
    cell->moveBy(x, y);
    qsrand(QTime::currentTime().msec());

}

//peuple la Scene à l'initialisation
void CustomScene::initSettling(int nCells){
    for(int i = 0; i < nCells; i++){
        Cell * cell = new Cell(randInt(-10000, 10000),randInt(-1000, 1000), 60);
        addItem(cell);
    }
}

void CustomScene::collider(Cell * collidingCell){

    foreach(QGraphicsItem* s,collidingItems(collidingCell)){
       deadList.push_back(reinterpret_cast<Cell*>(s));
    };
}

void CustomScene::settler(){
    foreach (Cell* s, deadList) {
        //s->
    }
}

void CustomScene::borderguard(){
}

int CustomScene::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

