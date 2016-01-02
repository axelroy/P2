#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class Cell : public QGraphicsEllipseItem
{
public:
    Cell();
    Cell(qreal x, qreal y, int healthPoint, QGraphicsItem* parent = 0);

private:
    int healthPoint;
    int armor;
    int speed;

    int bonusHealthPoint;
    int bonusSpeed;
    int bonusArmor;


public:
    //donne une cellule à manger
    void eat(Cell*);
    void refreshSize();


    //setter
    void setHealthPoint(int value){healthPoint=value;}
    void setArmor(int value){armor=value;}
    void setSpeed(int value){speed=value;}
    void setBonusHealthPoint(int value){bonusHealthPoint=value;}
    void setBonusArmor(int value){bonusSpeed=value;}
    void setBonusSpeed(int value){bonusArmor=value;}

    //getter
    int getHealthPoint(){return healthPoint;}
    int getArmor(){return armor;}
    int getSpeed(){return speed;}
    int getBonusHealthPoint(){return bonusHealthPoint;}
    int getBonusArmor(){return bonusSpeed;}
    int getBonusSpeed(){return bonusArmor;}

};

#endif // CELL_H
