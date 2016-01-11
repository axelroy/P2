#include "ia.h"


Ia::Ia(CustomScene* map, Cell* iaCell)
{
    this->iaCell = iaCell;
    this->map = map;
    iaCellCollider = new Collider(map, iaCell);
    iaCellCollider->start();

}


void Ia::run()
{
    while(true){
        sleep(2);
        //choisis la cellule à bouffer
        //init
        target = iaCell;
        foreach(QGraphicsItem* s,  (iaCellCollider->nearList)){
            fetch = reinterpret_cast<Cell*>(s);
            if(fetch->getHealthPoint() < target->getHealthPoint()*0.8){
                if(target == iaCell){
                    target = fetch;
                    qDebug() << "Target focused";
                }
                else if(qSqrt(qPow(fetch->x()-iaCell->x(), 2) + qPow(fetch->y()-iaCell->y(), 2)) <
                        qSqrt(qPow(target->x()-iaCell->x(), 2) + qPow(target->y()-iaCell->y(), 2))){
                    target = fetch;
                }

            }
        }

        //se dirige vers la cellule
        //descendre
        if(target->x() < iaCell->x()-5){
            //gauche
            if(target->y() < iaCell->y()-5){
                nextX = iaCell->x()-iaCell->getSpeed()*0.707;
                nextY = iaCell->y()-iaCell->getSpeed()*0.707;

            }

            //droite
            else if(target->y() > iaCell->y()+5){
                nextX = iaCell->x()+iaCell->getSpeed()*0.707;
                nextY = iaCell->y()-iaCell->getSpeed()*0.707;
            }

            //Juste bas
            else{
                nextX = iaCell->x();
                nextY = iaCell->y()-iaCell->getSpeed();
            }

        }
        //monter
        else if(target->x() > iaCell->x()+5){
            //gauche
            if(target->y() < iaCell->y()-5){
                nextX = iaCell->x()-iaCell->getSpeed()*0.707;
                nextY = iaCell->y()+iaCell->getSpeed()*0.707;
            }

            //droite
            else if(target->y() > iaCell->y()+5){
                nextX = iaCell->x()+iaCell->getSpeed()*0.707;
                nextY = iaCell->y()+iaCell->getSpeed()*0.707;
            }

            //Juste haut
            else{
                nextX = iaCell->x();
                nextY = iaCell->y()+iaCell->getSpeed();
            }
        }

        qDebug() << "vert " << iaCell->x() - nextX;
        qDebug() << "hori " << iaCell->y() - nextY;
    }
}

void Ia::move()
{
    map->MoveCell(nextX, nextY, iaCell);
}
