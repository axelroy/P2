#include "collider.h"

Collider::Collider(CustomScene* map, Cell* refCell)
{
    this->map = map;
    this->refCell = refCell;
    c = new Cell();
    area = 1200;
    qDebug() << "mirobolan";
    //this->map->collidingItems(this->refCell);
}

void Collider::run()
{
    qDebug() << "mirobolan au carre";
    map->Ouaf();
    while(true){
        msleep(50);
        foreach(s, map->items()){
            if(s!=refCell){
                if(qSqrt(qPow(s->x()-refCell->x(), 2) + qPow(s->y()-refCell->y(), 2)) < area){
                    if(!nearList.contains(s)){
                        nearList.push_back(s);
                    }
                }
                else{
                    if(nearList.contains(s)){
                        nearList.removeOne(s);
                    }
                }
            }
            }
        }
    }


void Collider::update()
{
    collidingCells.clear();
    //if(Cell::sem_deadList.tryAcquire(1)){

        foreach (e, nearList) {
            if(refCell->collidesWithItem(e)){
                c = reinterpret_cast<Cell*>(e);

                if(!collidingCells.contains(c) && c->active==true){
                    collidingCells.push_back(c);


                    if(refCell->getHealthPoint()*0.8 > c->getHealthPoint()){
                        refCell->eat(c);
                        c->hide();
                        c->active=false;
                        Cell::deadList.enqueue(c);
                    }
                    else if(refCell->getHealthPoint() < reinterpret_cast<Cell*>(c)->getHealthPoint()*0.8){
                        c->eat(refCell);
                        refCell->hide();

                        Collider::autorizedDirection = 0b00000000;
                    }else{

                        //collision haut
                        if(refCell->sceneBoundingRect().center().y() > c->sceneBoundingRect().center().y()){
                            Collider::autorizedDirection = 0b11111110 & Collider::autorizedDirection;

                        }
                        //bas
                        if(refCell->sceneBoundingRect().center().y() < c->sceneBoundingRect().center().y()){
                            Collider::autorizedDirection = 0b11111011 & Collider::autorizedDirection;

                        }
                        //gauche
                        if(refCell->sceneBoundingRect().center().x() > c->sceneBoundingRect().center().x()){
                            Collider::autorizedDirection = 0b11111101 & Collider::autorizedDirection;
                        }
                        //droite
                        if(refCell->sceneBoundingRect().center().x() < c->sceneBoundingRect().center().x()){
                            Collider::autorizedDirection = 0b11110111 & Collider::autorizedDirection;

                        }


                    }
                }
            }
        //}
    }
}


