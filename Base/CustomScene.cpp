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

        Cell * c = reinterpret_cast<Cell*>(s);


        if(collidingCell->getHealthPoint() > c->getHealthPoint()*0.8){
            collidingCell->eat(c);
            c->hide();
            deadList.push_back(c);
        }
        else if(collidingCell->getHealthPoint()*0.8 < reinterpret_cast<Cell*>(c)->getHealthPoint()){
            collidingCell->hide();
            c->eat(collidingCell);
            //Fin du jeu
        }
    };
}

void CustomScene::settler(Cell * refCell){
    foreach (Cell* s, deadList) {
        //refaire pour pas qu'il apparaisse sur la partie visible
        s->setPos(randInt(-1000, 1000), randInt(-1000, 1000));
        s->setHealthPoint(randInt(0.5, 2)*refCell->getHealthPoint());
    }
}

void CustomScene::borderguard(){
}

int CustomScene::randInt(int low, int high)
{
    // Random number between low and high
    return qrand() % ((high + 1) - low) + low;
}

