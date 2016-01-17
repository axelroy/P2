#include "bot.h"

Bot::Bot(CustomScene* map)
{
    this->map = map;
    botCollider = new Collider(map, this);
    botCollider->start(QThread::LowPriority);
    this->start(QThread::LowPriority);
    this->setSpeed(Config::START_SPEED);
    direction = Config::INIT_KEYS_STATMENT;
}

void Bot::run()
{
    qDebug() << "bot" << "1";
    botCollider->mutex_nearlist.lock();
    targetTargeted = false;
    if(this->isActive()){
        if(!botCollider->nearList.isEmpty()){
            //Pour tout les éléments proches

            foreach(QGraphicsItem* s, botCollider->nearList){
                fetch = qgraphicsitem_cast<Cell*>(s);

                //Si la cellule est mangeable
                if(fetch->getHealthPoint() < getHealthPoint()*Config::COLIDER_TREASHOLD){
                    if(!targetTargeted){
                        target=fetch;
                        targetTargeted=true;
                    }
                    //Si la cellules est plus proche
                    else if((qPow((fetch->x() + fetch->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) +
                             qPow((fetch->y() + fetch->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2)) <
                            (qPow((target->x() + target->sceneBoundingRect().width()/2)-(x() + sceneBoundingRect().width()/2), 2) +
                             qPow((target->y() + target->sceneBoundingRect().height()/2)-(y() + sceneBoundingRect().height()/2), 2))){
                        target=fetch;
                    }
                }
            }

            mutex_direction.lock();
            if(targetTargeted){
                calcDirection();
            }
            else{
                direction=Config::INIT_KEYS_STATMENT;
            }
            mutex_direction.unlock();

        }
    }
    botCollider->mutex_nearlist.unlock();
}

char Bot::getDirection() const
{
    qDebug() << "bot" << "3";
    return direction;
}

Collider *Bot::getBotCollider() const
{
    qDebug() << "bot" << "4";
    return botCollider;
}

void Bot::calcDirection()
{
    qDebug() << "bot" << "2";
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

