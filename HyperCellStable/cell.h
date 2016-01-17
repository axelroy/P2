/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : Cell
 * Resumé           : classe data pour implémenter une cellule
 * version          : 0.0
 */

#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>

class QMutex;

class Cell : public QGraphicsEllipseItem
{
public:
    //Canonical form just for fun
    Cell(QGraphicsItem* parent = 0);
    Cell(int healthPoint, QGraphicsItem* parent = 0);
    Cell(int healthPoint, int bonusHealthPoint, QGraphicsItem* parent = 0);
    Cell(Cell &c);
    Cell &operator=(Cell c);
    virtual ~Cell();

    //update data
    void refreshSize();

    //setter
    void activate();
    void desactivate();
    void setIsPlayer(bool value);
    void setHealthPoint(int value);
    void setArmor(int value);
    void setSpeed(double value);
    void setBonusHealthPoint(int value);
    void setBonusArmor(int value);
    void setBonusSpeed(int value);

    //getter
    bool isActive() const;
    bool isPlayer() const;
    int getHealthPoint() const;
    int getArmor() const;
    double getSpeed() const;
    int getBonusHealthPoint() const;
    int getBonusArmor() const;
    double getBonusSpeed() const;

private:
    //Base statistics
    int healthPoint;
    int armor;
    double speed;

    //Bonus
    int bonusHealthPoint;
    double bonusSpeed;
    int bonusArmor;

    //
    bool active;
    bool player;

    static QMutex mutex;
};

#endif // CELL_H
