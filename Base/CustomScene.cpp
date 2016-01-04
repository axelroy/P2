#include "CustomScene.h"
#include <QtGlobal>
#include <QTime>
#include <QtDebug>

CustomScene::CustomScene()
{

}

void CustomScene::MoveCell(double x, double y, Cell * cell)
{
    cell->moveBy(x, y);
    qsrand(QTime::currentTime().msec());

}

//peuple la Scene à l'initialisation
void CustomScene::initSettling(int nCells, Cell * refCell){
    for(int i = 0; i < nCells; i++){
        Cell * cell = new Cell(randInt(-10000, 10000),randInt(-1000, 1000), 60);

        giveProperties(cell, refCell, 10/*xzoom*/);
        addItem(cell);

    }
}

void CustomScene::collider(Cell * collidingCell){

    foreach(QGraphicsItem* s,collidingItems(collidingCell)){

        Cell * c = reinterpret_cast<Cell*>(s);


        if(collidingCell->getHealthPoint()*0.8 > c->getHealthPoint()){
            collidingCell->eat(c);
            c->hide();
            deadList.enqueue(c);
        }
        else if(collidingCell->getHealthPoint() < reinterpret_cast<Cell*>(c)->getHealthPoint()*0.8){
            c->eat(collidingCell);
            collidingCell->hide();

            CustomScene::autorizedDirection = 0b00000000;
        }else{
            //collision haut
            if(collidingCell->sceneBoundingRect().center().y() > s->sceneBoundingRect().center().y()){
                CustomScene::autorizedDirection = 0b11111110 & CustomScene::autorizedDirection;
                qDebug() << "Haut";
            }
            //bas
            if(collidingCell->sceneBoundingRect().center().y() < s->sceneBoundingRect().center().y()){
                CustomScene::autorizedDirection = 0b11111011 & CustomScene::autorizedDirection;
                qDebug() << "Haut";
            }
            //gauche
            if(collidingCell->sceneBoundingRect().center().x() > s->sceneBoundingRect().center().x()){
                CustomScene::autorizedDirection = 0b11111101 & CustomScene::autorizedDirection;
            }
            //droite
            if(collidingCell->sceneBoundingRect().center().x() < s->sceneBoundingRect().center().x()){
                CustomScene::autorizedDirection = 0b11110111 & CustomScene::autorizedDirection;

            }

            qDebug() << CustomScene::autorizedDirection;
        }
    };
}



void CustomScene::settler(Cell * refCell){

    //A mettre dans un thread, appeler successivement
    if(!deadList.isEmpty()){
        giveProperties(deadList.dequeue(), refCell, 1000/*xzoom*/);

    }
}

void CustomScene::giveProperties(Cell * cell, Cell * refCell, int minRange){

    //refaire pour pas qu'il apparaisse sur la partie visible
    cell->setPos((refCell->x())+randInt(-1000, 1000), (refCell->y())+randInt(-1000, 1000));

    CustomScene::randomCell = randInt(0, 100);
    //Risque de voir une prolifération de malusCell car le joueur va éviter de les prendre ?
    if(CustomScene::randomCell < CustomScene::ProbMalusCell){
        cell->setHealthPoint(0.2*refCell->getHealthPoint());
        cell->setBrush(Qt::red);
        cell->setBonusHealthPoint((-(double)(randInt(1, 5))/10)*refCell->getHealthPoint());
        cell->setBonusSpeed((-(double)(randInt(2, 20))/10)*refCell->getSpeed());
    }else if(CustomScene::randomCell < CustomScene::ProbBonusCell+CustomScene::ProbMalusCell){
        cell->setHealthPoint(0.2*refCell->getHealthPoint());
        cell->setBrush(Qt::green);
        cell->setBonusHealthPoint(((double)(randInt(1, 5))/10)*refCell->getHealthPoint());
        cell->setBonusSpeed(((double)(randInt(2, 20))/10)*refCell->getSpeed());
    }else {
        cell->setHealthPoint(((double)(randInt(3, 20))/10)*refCell->getHealthPoint());
        cell->setBrush(Qt::darkYellow);
    }
    cell->refreshSize();
    cell->show();

}



void CustomScene::borderguard(Cell * refCell, qreal area){
    //todo : fixer la zone active autours de la cellule de ref
    QGraphicsItem * controledCell;
    foreach (controledCell, items()) {
        if (controledCell->x() > refCell->x()+area || controledCell->x() < refCell->x()-area || controledCell->y() > refCell->y()+area || controledCell->y() < refCell->y()-area)
        {
            // ajouter un bit a la class cell pour que l'on ajout pas deux fois une cellule
            deadList.enqueue(reinterpret_cast<Cell*>(controledCell));
            qDebug() << controledCell;
        }

    };
}

int CustomScene::randInt(int low, int high)
{
    int a = qrand() % ((high + 1) - low) + low;

    //qDebug() << a << "\n";
    // Random number between low and high
    return a;

}


