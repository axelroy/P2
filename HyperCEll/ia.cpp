#include "ia.h"


Ia::Ia(CustomScene* map, Cell* iaCell)
{
    this->iaCell = iaCell;
    this->map = map;
    iaCellCollider = new Collider(map, iaCell);
    iaCellCollider->start();
    sem_control.release();

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

        if(sem_control.tryAcquire(1)){
            //se dirige vers la cellule

            //descendre
            if(target->x() < iaCell->x()-5){
                //gauche
                if(target->y() < iaCell->y()-5){
                    direction = Config::ACTION_DOWN_LEFT;
                }

                //droite
                else if(target->y() > iaCell->y()+5){
                    direction = Config::ACTION_DOWN_RIGHT;
                }

                //Juste bas
                else{
                    direction = Config::ACTION_DOWN;
                }

            }
            //monter
            else if(target->x() > iaCell->x()+5){
                //gauche
                if(target->y() < iaCell->y()-5){
                    direction = Config::ACTION_UP_LEFT;
                }

                //droite
                else if(target->y() > iaCell->y()+5){
                    direction = Config::ACTION_UP_RIGHT;
                }

                //Juste haut
                else{
                    direction = Config::ACTION_DOWN;
                }
            }
            sem_control.release();
        }
    }
}

char Ia::getDirection() const
{
    return direction;
}
