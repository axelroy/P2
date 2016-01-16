#include <QtCore/qmath.h>

#include "borderguard.h"
#include "config.h"
#include "deadlist.h"


Borderguard::Borderguard(Cell* refCell, CustomScene* map)
{
    this->refCell = refCell;
    this->map = map;
    refreshArea();
}


//Detecte les cellules trop éloignée et les mets dans la deadlist
void Borderguard::run()
{
    QGraphicsItem* controlledCell;
    while(true){
        msleep(Config::BORDERGUARD_SLEEP);
        foreach (controlledCell, map->items())
        {

            if (controlledCell->x() > refCell->x()+area ||
                    controlledCell->x() < refCell->x()-area ||
                    controlledCell->y() > refCell->y()+area ||
                    controlledCell->y() < refCell->y()-area
                    )
            {
                Cell* c =  reinterpret_cast<Cell*>(controlledCell);
                if(c->isActive()){
                    // ajouter un bit a la class cell pour que l'on ajout pas deux fois une cellule
                    c->desactivate();
                    DeadList::addCell(c);
                }
            }
        }
        refreshArea();
    }
}

void Borderguard::setArea(double value)
{
    area = value;
}

// la taille de zone évolue en fonction de la taille de la cellule
void Borderguard::refreshArea()
{
    this->area = Config::BORDERGUARD_AREA * qSqrt(qSqrt(refCell->getHealthPoint()/Config::START_LIFE));
}

