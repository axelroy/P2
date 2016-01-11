#include "borderguard.h"

Borderguard::Borderguard(double area, Cell* refCell, CustomScene* map)
{
    this->area = area;
    this->refCell = refCell;
    this->map = map;
}

void Borderguard::run()
{
    while(true){
        msleep(600);
        //qDebug() << "Borderguard " << Cell::sem_deadList.available();
            foreach (controlledCell, map->items()) {
                if (controlledCell->x() > refCell->x()+area || controlledCell->x() < refCell->x()-area || controlledCell->y() > refCell->y()+area || controlledCell->y() < refCell->y()-area)
                {
                    Cell* c =  reinterpret_cast<Cell*>(controlledCell);
                    if(c->active==true){
                        qDebug() << "Mexicain abbatu";
                        // ajouter un bit a la class cell pour que l'on ajout pas deux fois une cellule
                        if(Cell::sem_deadList.tryAcquire(1)){
                            qDebug() << "Mexicain en enfer";
                            Cell::deadList.enqueue(reinterpret_cast<Cell*>(controlledCell));
                            c->active=false;
                            Cell::sem_deadList.release(1);
                            }

                    }
                }

        }

    }

}
