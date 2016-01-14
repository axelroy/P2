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
    sleep(2);
    qDebug() << iaCellCollider->nearList.count();
    target = reinterpret_cast<Cell*>(iaCellCollider->nearList.last());
    qDebug() << target;
    while(true){

        qDebug() << iaCell->x();

        int i = 0;
        //choisis la cellule à bouffer
        //init
        msleep(80);
        foreach(QGraphicsItem* s,  (iaCellCollider->nearList)){
            fetch = reinterpret_cast<Cell*>(s);

            if(fetch->getHealthPoint() < target->getHealthPoint()*1){
                //qDebug() << "fetching " << qSqrt(qPow(fetch->x()-iaCell->x(), 2) + qPow(fetch->y()-iaCell->y(), 2));
                 if((qPow(fetch->x()-iaCell->x(), 2) + qPow(fetch->y()-iaCell->y(), 2)) <
                            (qPow(target->x()-iaCell->x(), 2) + qPow(target->y()-iaCell->y(), 2))){

                        i++;
                        qDebug() << "Fetch " << i << " " << qSqrt(qPow(fetch->x()-iaCell->x(), 2) + qPow(fetch->y()-iaCell->y(), 2));
                        qDebug() << "Target " << i << " " << qSqrt(qPow(target->x()-iaCell->x(), 2) + qPow(target->y()-iaCell->y(), 2));
                        target = fetch;
                 }

            }
        }

        qDebug() << "Target attack " << i << " " << qSqrt(qPow(target->x()-iaCell->x(), 2) + qPow(target->y()-iaCell->y(), 2));
        target->setBrush(Qt::black);

        //if(sem_control.tryAcquire(1)){

            //se dirige vers la cellule

            //descendre
            if(target->y() < (iaCell->y()-10)){
                //gauche
                if(target->x() < (iaCell->x()-10)){
                    direction = Config::ACTION_DOWN_LEFT;
                }

                //droite
                else if(target->x() > (iaCell->x()+10)){
                    direction = Config::ACTION_DOWN_RIGHT;
                }

                //Juste bas
                else{
                    direction = Config::ACTION_DOWN;
                }

            }
            //monter
            else if(target->y() > (iaCell->y()+10)){
                //gauche
                if(target->x() < iaCell->x()-10){
                    direction = Config::ACTION_UP_LEFT;
                }

                //droite
                else if(target->x() > (iaCell->x()+10)){
                    direction = Config::ACTION_UP_RIGHT;
                }

                //Juste haut
                else{
                    direction = Config::ACTION_DOWN;
                }
            }
            //horizontale
            else{
                //gauche
                if(target->x() < iaCell->x()-10){
                    direction = Config::ACTION_RIGHT;
                }

                //droite
                else if(target->x() > (iaCell->x()+10)){
                    direction = Config::ACTION_LEFT;
                }
            //}
            //sem_control.release();
        }
    }
}


char Ia::getDirection() const
{
    return direction;
}

Collider *Ia::getIaCellCollider() const
{
    return iaCellCollider;
}
