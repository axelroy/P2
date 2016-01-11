#include "ia.h"


ia::ia(CustomScene* map, Cell* iaCell)
{
    this->iaCell = iaCell;
    this->map = map;
    iaCellCollider = new Collider(map, iaCell);
    iaCellCollider->start();

}


void ia::run()
{
    /*hile(true){
        msleep(10);
        //choisis la cellule à bouffer
        //init
        target = iaCell;
        foreach(fetch, iaCellCollider->nearList){
            if(fetch->getHealthPoint() < target->getHealthPoint()<*0.8){
                if(target == iaCell){
                    target = fetch;
                }
                else if(qSqrt(qPow(fetch->x()-iaCell->x(), 2) + fetch(s->y()-iaCell->y(), 2)) < qSqrt(qPow(target->x()-iaCell->x(), 2) + target(s->y()-iaCell->y(), 2))){
                    target = fetch;
            }
            }
        }

        //se dirige vers la cellule
        if(target->x() < iaCell->x() && target->y < iaCell->y()){
            if(target->y < iaCell->y())
        }
    }*/
}

void ia::move()
{
    map->MoveCell(nextX, nextY, iaCell);
}
