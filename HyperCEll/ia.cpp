#include "ia.h"


Ia::Ia(CustomScene* map)
{

    this->map = map;
    iaCellCollider = new Collider(map, this);
    iaCellCollider->start(QThread::LowPriority);
    sem_control.release();
    this->start(QThread::LowPriority);
    this->setSpeed(Config::BASE_SPEED_CELL);
}


void Ia::run()
{
    //qDebug() << "olol";

    //qDebug() << iaCellCollider->nearList.count();
    target = reinterpret_cast<Cell*>(iaCellCollider->nearList.last());
    //qDebug() << target;


    while(true){
        if(active){

            msleep(Config::IA_TIMER);

            int i = 0;

            //choisis la cellule à bouffer
            //init
            //if(i<1){
            msleep(80);
            foreach(QGraphicsItem* s,  (iaCellCollider->nearList)){
                fetch = reinterpret_cast<Cell*>(s);


                if(fetch->getHealthPoint() < getHealthPoint()*1){

                    //qDebug() << "fetching " << qSqrt(qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2));
                    if((qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2)) <
                            (qPow((target->x() + target->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2))){

                        i++;
                        //qDebug() << "Fetch " << i << " " << qSqrt(qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2));
                        //qDebug() << "Target " << i << " " << qSqrt(qPow((target->x() + target->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2));
                        target = fetch;
                    }

                }
            }

            /*
        //qDebug() << "Target attack " << i << " " << qSqrt(qPow((target->x() + target->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) + qPow((target->y() + target->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2));
        //qDebug() << "Target x : " << (target->x() + target->sceneBoundingRect().width()/2);
        //qDebug() << "Target y : " << (target->y() + target->sceneBoundingRect().height()/2);

        //qDebug() << "Ia x " << (x() + sceneBoundingRect().width()/2);
        //qDebug() << "Ia y " << (y() + sceneBoundingRect().height()/2);
        */

            //if(sem_control.tryAcquire(1)){

            //se dirige vers la cellule

            //descendre
            if((target->y() + target->sceneBoundingRect().height()/2) > ((y() + sceneBoundingRect().height()/2)+20)){
                //gauche
                if((target->x() + target->sceneBoundingRect().width()/2) < ((x() + sceneBoundingRect().width()/2)-20)){
                    direction = Config::ACTION_DOWN_LEFT;
                }

                //droite
                else if((target->x() + target->sceneBoundingRect().width()/2) > ((x() + sceneBoundingRect().width()/2)+20)){
                    direction = Config::ACTION_DOWN_RIGHT;
                }

                //Juste bas
                else{
                    direction = Config::ACTION_DOWN;
                }

            }
            //monter
            else if((target->y() + target->sceneBoundingRect().height()/2) < ((y() + sceneBoundingRect().height()/2)-20)){
                //gauche
                if((target->x() + target->sceneBoundingRect().width()/2) < (x() + sceneBoundingRect().width()/2)-20){
                    direction = Config::ACTION_UP_LEFT;
                }

                //droite
                else if((target->x() + target->sceneBoundingRect().width()/2) > ((x() + sceneBoundingRect().width()/2)+20)){
                    direction = Config::ACTION_UP_RIGHT;
                }

                //Juste haut
                else{
                    direction = Config::ACTION_UP;
                }
            }
            //horizontale

            //gauche
            else if((target->x() + target->sceneBoundingRect().width()/2) < ((x() + sceneBoundingRect().width()/2))){
                direction = Config::ACTION_LEFT;
            }

            //droite
            else if((target->x() + target->sceneBoundingRect().width()/2) > ((x() + sceneBoundingRect().width()/2))){
                direction = Config::ACTION_RIGHT;
            }

            //ne fait rien
            else{
                direction = Config::INIT_KEYS_STATMENT;

                //}
                //sem_control.release();
            }
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

void Ia::activate()
{
    setBrush(Qt::black);
    show();
    active=true;

}


