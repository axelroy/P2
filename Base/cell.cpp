#include "Cell.h"
#include <QtMath>

Cell::Cell()
{

}

Cell::Cell(qreal x, qreal y, int healthPoint, QGraphicsItem* parent) : QGraphicsEllipseItem(x, y, 0., 0., parent)
{
    this->healthPoint = healthPoint;
    armor = 0;
    speed = 0;
    bonusHealthPoint = healthPoint;
    bonusSpeed = 0;
    bonusArmor = 0;
    refreshSize();

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
    this->speed += c->getBonusSpeed();
    this->armor += c->getBonusArmor();

    this->refreshSize();
}
