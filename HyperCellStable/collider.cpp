#include "collider.h"
#include "config.h"

/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

Collider::Collider(CustomScene* map, Cell* refCell)
{
    this->map = map;
    this->refCell = refCell;
    c = new Cell();
    area = Config::COLIDER_ACTIVE_AREA;
    autorizedDirection = Config::DIRECTION_AUTHORIZED_ALL;
    //this->map->collidingItems(this->refCell);
}

Collider::~Collider()
{
    // assure l'arret de la tâche
    this->quit();
    delete c;
}


/*============================================*/
//  THREAD RUN
/*============================================*/

//indexe les cellules proche dans une liste
void Collider::run()
{
    // ajouté un bool de sortie !! bien plus propre
    while(true)
    {
        msleep(Config::COLIDER_TIMER);
        //Pour toute les cellules de la scene
        //todo with boundingrect
        foreach(s, map->items())
        {
            if(s!=refCell)
            {
                //met celle qui sont proche dans la nearlist
                if(qSqrt(qPow(s->x()-refCell->x(), 2) + qPow(s->y()-refCell->y(), 2)) < area )
                {
                    if(!nearList.contains(s))
                    {
                        nearList.push_back(s);
                    }
                }
                else
                {
                    if(nearList.contains(s))
                    {
                        nearList.removeOne(s);
                    }
                }
            }
        }
    }
}


/*============================================*/
//  UPDATE DATA
/*============================================*/

//Detecte les collisions et
void Collider::update()
{
    collidingCells.clear();
    foreach (e, nearList)
    {
        if(refCell->collidesWithItem(e))
        {
            c = reinterpret_cast<Cell*>(e);

            if(!collidingCells.contains(c) && c->isActive())
            {
                collidingCells.push_back(c);

                if(cellEatInteraction(Config::COLIDER_TREASHOLD, *refCell, *c))
                {
                    emit collision(*refCell, *c);
                }
                else
                {
                    //collision
                    /********************/
                    //haut
                    if(refCell->sceneBoundingRect().center().y() > c->sceneBoundingRect().center().y())
                    {
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_UP & Collider::autorizedDirection;
                    }
                    //bas
                    if(refCell->sceneBoundingRect().center().y() < c->sceneBoundingRect().center().y())
                    {
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_DOWN & Collider::autorizedDirection;
                    }
                    //gauche
                    if(refCell->sceneBoundingRect().center().x() > c->sceneBoundingRect().center().x())
                    {
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_LEFT & Collider::autorizedDirection;
                    }
                    //droite
                    if(refCell->sceneBoundingRect().center().x() < c->sceneBoundingRect().center().x())
                    {
                        autorizedDirection = Config::DIRECTION_UNAUTHORIZED_RIGHT & Collider::autorizedDirection;
                    }
                }
            }
        }
    }
}


/*============================================*/
//  ASSESSOR / MUTATOR
/*============================================*/

char Collider::getAutorizedDirection() const
{
    return autorizedDirection;
}

void Collider::setAutorizedDirection(char value)
{
    autorizedDirection = value;
}


/*============================================*/
//  PUBLIC SLOTS
/*============================================*/

void Collider::on_Controller_BlockMovement(bool block)
{
    if(block)
    {
        autorizedDirection = Config::DIRECTION_AUTHORIZED_NONE;
    }
    else
    {
         autorizedDirection = Config::DIRECTION_AUTHORIZED_ALL;
    }
}


/*============================================*/
//  PRIVATE
/*============================================*/


bool Collider::cellEatInteraction(double treashold, Cell &c1, Cell &c2)
{
    return (c1.getHealthPoint() * treashold > c2.getHealthPoint()) ||
            (c2.getHealthPoint() * treashold > c1.getHealthPoint());
}


