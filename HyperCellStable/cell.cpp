#include "cell.h"
#include <QtMath>
#include <QDebug>
#include "config.h"
#include <QMutexLocker>

/*============================================*/
//  CONSTRUCTOR / DESTRUCTOR
/*============================================*/

Cell::Cell(QGraphicsItem* parent) :
    Cell(10, parent)
{
    //nothing
}

Cell::Cell(int healthPoint, QGraphicsItem* parent) :
    Cell(healthPoint, healthPoint, parent)
{
    //nothing
}

Cell::Cell(int healthPoint, int bonusHealthPoint, QGraphicsItem* parent) :
    QGraphicsEllipseItem(parent)
{
    this->healthPoint = healthPoint;
    this->bonusHealthPoint = bonusHealthPoint;
    this->armor = Config::START_ARMOR;
    this->speed = Config::START_SPEED;
    this->bonusSpeed = Config::START_SPEED;
    this->bonusArmor = Config::START_ARMOR;
    this->active = false;
    this->player = false;

    refreshSize();
}

Cell::Cell(Cell &c)
{
    this->healthPoint = c.healthPoint;
    this->armor = c.armor;
    this->speed = c.speed;
    this->bonusHealthPoint = c.bonusHealthPoint;
    this->bonusArmor = c.bonusArmor;
    this->bonusSpeed = c.bonusSpeed;
}

Cell &Cell::operator=(Cell c)
{
    std::swap(this->healthPoint, c.healthPoint);
    std::swap(this->armor, c.armor);
    std::swap(this->speed, c.speed);
    std::swap(this->bonusHealthPoint, c.bonusHealthPoint);
    std::swap(this->bonusArmor, c.bonusArmor);
    std::swap(this->bonusSpeed, c.bonusSpeed);

    return *this;
}

Cell::~Cell()
{
    //nothing
}


/*============================================*/
//  THREAD SAFE
/*============================================*/

QMutex Cell::mutex;


/*============================================*/
//  UPDATE DATA
/*============================================*/

void Cell::refreshSize()
{
    QMutexLocker locker(&mutex);
    qreal radius = 0;
    radius = 2*sqrt(healthPoint/M_PI);
    this->setRect(this->rect().x(), this->rect().y(), radius, radius);
}


/*============================================*/
//  ASSESSOR / MUTATOR
/*============================================*/

void Cell::activate()
{
    QMutexLocker locker(&mutex);
    this->show();
    active=true;
}

void Cell::desactivate()
{
    QMutexLocker locker(&mutex);
    this->hide();
    active=false;
}

void Cell::setIsPlayer(bool value)
{
    QMutexLocker locker(&mutex);
    player = value;
}

void Cell::setHealthPoint(int value)
{
    QMutexLocker locker(&mutex);
    healthPoint=value;
}

void Cell::setArmor(int value)
{
    QMutexLocker locker(&mutex);
    armor=value;
}

void Cell::setSpeed(double value)
{
    QMutexLocker locker(&mutex);
    speed=value;
}

void Cell::setBonusHealthPoint(int value)
{
    QMutexLocker locker(&mutex);
    bonusHealthPoint=value;
}

void Cell::setBonusArmor(int value)
{
    QMutexLocker locker(&mutex);
    bonusSpeed=value;
}

void Cell::setBonusSpeed(int value)
{
    QMutexLocker locker(&mutex);
    bonusArmor=value;
}

bool Cell::isActive() const
{
    QMutexLocker locker(&mutex);
    return active;
}

bool Cell::isPlayer() const
{
    QMutexLocker locker(&mutex);
    return player;
}

int Cell::getHealthPoint() const
{
    QMutexLocker locker(&mutex);
    return healthPoint;
}

int Cell::getArmor() const
{
    QMutexLocker locker(&mutex);
    return armor;
}

double Cell::getSpeed() const
{
    QMutexLocker locker(&mutex);
    return speed;
}

int Cell::getBonusHealthPoint() const
{
    QMutexLocker locker(&mutex);
    return bonusHealthPoint;
}

int Cell::getBonusArmor() const
{
    QMutexLocker locker(&mutex);
    return bonusSpeed;
}

double Cell::getBonusSpeed() const
{
    QMutexLocker locker(&mutex);
    return bonusArmor;
}


