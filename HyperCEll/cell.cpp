#include "Cell.h"
#include <QtMath>

Cell::Cell(QGraphicsItem* parent) : QGraphicsEllipseItem(parent)
{}
Cell::Cell(int healthPoint, QGraphicsItem* parent) : QGraphicsEllipseItem(parent)
{

    this->healthPoint = healthPoint;
    armor = 0;
    speed = 0;
    bonusHealthPoint = healthPoint;
    bonusSpeed = 0;
    bonusArmor = 0;
    refreshSize();

    active = false;

}

void Cell::refreshSize()
{
    qreal radius = 0;
    radius = 2*sqrt(healthPoint/M_PI);
    this->setRect(this->rect().x(), this->rect().y(), radius, radius);
}

void Cell::eat(Cell * c)
{
    this->healthPoint += c->getBonusHealthPoint();
    if(this->healthPoint <= 0){
        //Fin du jeu;
        this->hide();
    }
    this->speed += c->getBonusSpeed();
    this->armor += c->getBonusArmor();

    this->refreshSize();
}
