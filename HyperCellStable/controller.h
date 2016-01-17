/* Auteurs          : Ramseyer Sylvain, Roy Axel, Ruedin Cyril
 * Date de modif.   : 17.01.2016
 * Classe           : Controller
 * Resumé           : Contrôle l'application
 * version          : 0.0
 */
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QWidget>

class Cell;
class CustomScene;
class View;
class Collider;
class Settler;
class Borderguard;

class Controller : public QWidget
{
    Q_OBJECT
public:
    explicit Controller(QWidget *parent = 0);
    virtual ~Controller();

public slots:
    void on_collider_collision(Cell &c1, Cell &c2);

signals :
    void blockMovement(bool block);

protected:
    void timerEvent(QTimerEvent* e);

private:
    double bestSize;
    CustomScene* map;
    View* camera;
    Cell *mainCell;
    Collider* mainCollider;
    Borderguard *borderguard;
    Settler* settler;

    void initialisation();
    void manageDeadCell(Cell &c);
    //void scaleView();
    void eat(Cell &c1, Cell &c2);
    void newGame();
    void refreshBestSize();
    void showMsgBEndGame();
};

#endif // CONTROLLER_H
