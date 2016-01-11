#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QQueue>
#include <QSemaphore>

class Cell : public QGraphicsEllipseItem
{
private:
    static QQueue<Cell*> deadList;

    int healthPoint;
    int armor;
    double speed;

    int bonusHealthPoint;
    double bonusSpeed;
    int bonusArmor;

    bool active;

public:
    Cell(QGraphicsItem* parent = 0);
    Cell(int healthPoint, QGraphicsItem* parent = 0);

    static QSemaphore sem_deadList;

    // travail sur la deadlist
    static void deadListEnqueue(Cell* c){Cell::deadList.enqueue(c);}
    static Cell* deadListDequeue(){return Cell::deadList.dequeue();}
    static bool deadListIsEmpty(){return Cell::deadList.isEmpty();}

    //donne une cellule à manger
    void eat(Cell*);
    void refreshSize();
    void activate();
    void desactivate();
    bool isActive(){return active;}

    //setter
    void setHealthPoint(int value){healthPoint=value;}
    void setArmor(int value){armor=value;}
    void setSpeed(double value){speed=value;}
    void setBonusHealthPoint(int value){bonusHealthPoint=value;}
    void setBonusArmor(int value){bonusSpeed=value;}
    void setBonusSpeed(int value){bonusArmor=value;}

    //getter
    int getHealthPoint(){return healthPoint;}
    int getArmor(){return armor;}
    double getSpeed(){return speed;}
    int getBonusHealthPoint(){return bonusHealthPoint;}
    int getBonusArmor(){return bonusSpeed;}
    double getBonusSpeed(){return bonusArmor;}

};

#endif // CELL_H
