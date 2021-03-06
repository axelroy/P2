#include "collider.h"
#include "config.h"


Collider::Collider(CustomScene* map, Cell* refCell)
{
    this->map = map;
    this->refCell = refCell;
    c = new Cell();
    area = Config::COLIDER_ACTIVE_AREA;
    autorizedDirection = Config::DIRECTION_AUTHORIZED_ALL;
    //this->map->collidingItems(this->refCell);
}


//indexe les cellules proche dans une liste
void Collider::run()
{
    // ajouté un bool de sortie !! bien plus propre
    while(true){
        msleep(Config::COLIDER_TIMER);
        qDebug() << "collider" << "5";
        //Pour toute les cellules de la scene
        //todo with boundingrect
        mutex_nearlist.lock();
        foreach(s, map->items()){
            if(s!=refCell){
                //met celle qui sont proche dans la nearlist
                //qDebug() << "collider" << "6";

                if(qSqrt(qPow(s->x()-refCell->x(), 2) + qPow(s->y()-refCell->y(), 2)) < area && reinterpret_cast<Cell*>(s)->isActive()){
                    if(!nearList.contains(s)){
                        qDebug() << "collider" << "7";
                        nearList.push_back(s);
                    }
                }
                else{
                    if(nearList.contains(s)){
                        qDebug() << "collider" << "8";
                        nearList.removeOne(s);
                    }
                }

            }

        }
        mutex_nearlist.unlock();
    }
}



//Detecte les collisions et
void Collider::update()
{
    collidingCells.clear();
    //if(Cell::sem_deadList.tryAcquire(1)){
    mutex_nearlist.lock();
    qDebug() << "collider" << "9";
    foreach (e, nearList) {
        if(refCell->collidesWithItem(e)){
            c = reinterpret_cast<Cell*>(e);
            qDebug() << "collider" << "10";
            if(!collidingCells.contains(c) && c->isActive()){
                collidingCells.push_back(c);

                if(cellEatInteraction(Config::COLIDER_TREASHOLD, *refCell, *c))
                {
                    emit collision(*refCell, *c);
                }
                else
                {
                    qDebug() << "collider" << "11";
                    //collision haut
                    if(refCell->sceneBoundingRect().center().y() > c->sceneBoundingRect().center().y()){

                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_UP & Collider::autorizedDirection;
                    }
                    //bas
                    if(refCell->sceneBoundingRect().center().y() < c->sceneBoundingRect().center().y()){
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_DOWN & Collider::autorizedDirection;

                    }
                    //gauche
                    if(refCell->sceneBoundingRect().center().x() > c->sceneBoundingRect().center().x()){

                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_LEFT & Collider::autorizedDirection;
                    }
                    //droite
                    if(refCell->sceneBoundingRect().center().x() < c->sceneBoundingRect().center().x()){
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_RIGHT & Collider::autorizedDirection;

                    }


                }
            }
        }

    }
    mutex_nearlist.unlock();
}

char Collider::getAutorizedDirection() const
{
    qDebug() << "collider" << "13";
    return autorizedDirection;
}

void Collider::setAutorizedDirection(char value)
{
    qDebug() << "collider" << "14";
    autorizedDirection = value;
}

void Collider::on_Controller_BlockMovement()
{
    qDebug() << "collider" << "15";
    autorizedDirection = Config::DIRECTION_AUTHORIZED_NONE;
}

bool Collider::cellEatInteraction(double treashold, Cell &c1, Cell &c2)
{
    qDebug() << "collider" << "16";
    return (c1.getHealthPoint() * treashold > c2.getHealthPoint()) ||
            (c2.getHealthPoint() * treashold > c1.getHealthPoint());
}


