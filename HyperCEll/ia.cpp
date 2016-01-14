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
        int i = 0;

        //choisis la cellule à bouffer
        //init
        //if(i<1){
        msleep(80);
        foreach(QGraphicsItem* s,  (iaCellCollider->nearList)){
            fetch = reinterpret_cast<Cell*>(s);


            if(fetch->getHealthPoint() < iaCell->getHealthPoint()*1){

                //qDebug() << "fetching " << qSqrt(qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2));
                 if((qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2)) <
                            (qPow((target->x() + target->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2))){

                        i++;
                        qDebug() << "Fetch " << i << " " << qSqrt(qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2));
                        qDebug() << "Target " << i << " " << qSqrt(qPow((target->x() + target->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2));
                        target = fetch;
                 }

            }
        }

        qDebug() << "Target attack " << i << " " << qSqrt(qPow((target->x() + target->sceneBoundingRect().width()/2)-(iaCell->x() + iaCell->sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(iaCell->y() + iaCell->sceneBoundingRect().height()/2), 2));
        qDebug() << "Target x : " << (target->x() + target->sceneBoundingRect().width()/2);
        qDebug() << "Target y : " << (target->y() + target->sceneBoundingRect().height()/2);

        qDebug() << "Ia x " << (iaCell->x() + iaCell->sceneBoundingRect().width()/2);
        qDebug() << "Ia y " << (iaCell->y() + iaCell->sceneBoundingRect().height()/2);


        target->setBrush(Qt::black);
        target->sceneBoundingRect().width()/2;

        //if(sem_control.tryAcquire(1)){

            //se dirige vers la cellule

            //descendre
            if((target->y() + target->sceneBoundingRect().height()/2) > ((iaCell->y() + iaCell->sceneBoundingRect().height()/2)-0)){
                //gauche
                if((target->x() + target->sceneBoundingRect().width()/2) < ((iaCell->x() + iaCell->sceneBoundingRect().width()/2)-0)){
                    direction = Config::ACTION_DOWN_LEFT;
                }

                //droite
                else if((target->x() + target->sceneBoundingRect().width()/2) > ((iaCell->x() + iaCell->sceneBoundingRect().width()/2)+0)){
                    direction = Config::ACTION_DOWN_RIGHT;
                }

                //Juste bas
                else{
                    direction = Config::ACTION_DOWN;
                }

            }
            //monter
            else if((target->y() + target->sceneBoundingRect().height()/2) < ((iaCell->y() + iaCell->sceneBoundingRect().height()/2)+0)){
                //gauche
                if((target->x() + target->sceneBoundingRect().width()/2) < (iaCell->x() + iaCell->sceneBoundingRect().width()/2)-0){
                    direction = Config::ACTION_UP_LEFT;
                }

                //droite
                else if((target->x() + target->sceneBoundingRect().width()/2) > ((iaCell->x() + iaCell->sceneBoundingRect().width()/2)+0)){
                    direction = Config::ACTION_UP_RIGHT;
                }

                //Juste haut
                else{
                    direction = Config::ACTION_UP;
                }
            }
            //horizontale

            //gauche
            else if((target->x() + target->sceneBoundingRect().width()/2) < (iaCell->x() + iaCell->sceneBoundingRect().width()/2)-0){
                direction = Config::ACTION_RIGHT;
            }

            //droite
            else if((target->x() + target->sceneBoundingRect().width()/2) > ((iaCell->x() + iaCell->sceneBoundingRect().width()/2)+0)){
                direction = Config::ACTION_LEFT;
            }

            //ne fait rien
            else{
                direction = Config::INIT_KEYS_STATMENT;

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
